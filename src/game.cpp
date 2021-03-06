#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

#include <time/timer.hpp>
#include <surfaces/image.hpp>
#include <surfaces/text.hpp>
#include <surfaces/rectangle.hpp>
#include <textures/texture.hpp>
#include <textures/texture_circle.hpp>
#include <sprites/direction.hpp>
#include <sprites/sprite_rectangle.hpp>
#include <sprites/sprite_circle.hpp>
#include <navigation/camera.hpp>
#include <particles/particle_emitter.hpp>

int main() {
  // initialize SDL & its extensions
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << "Error while initializing SDL" << std::endl;
    return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cout << "Error while initializing SDL-image" << std::endl;
    return 1;
  }

  if (TTF_Init() == -1) {
    std::cout << "Error while initializing SDL-ttf" << std::endl;
    return 1;
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
    std::cout << "Error while initializing SDL-mixer" << std::endl;
    return 1;
  }

  // open font
  TTF_Font* font = TTF_OpenFont("assets/fonts/Roboto.ttf", 32);
  if (font == NULL) {
    std::cout << "Error while loading font" << std::endl;
    return 1;
  }

  // load audio sounds & play music
  Mix_Chunk* effect = Mix_LoadWAV("assets/sounds/effect.wav");
  Mix_Music* music = Mix_LoadMUS("assets/sounds/music.wav");
  // Mix_PlayMusic(music, -1);

  // camera (same size as screen) scrolling inside level
  const SDL_Point LEVEL {1280, 960};
  const SDL_Point SCREEN {640, 480};
  Camera camera({0, 0, SCREEN.x, SCREEN.y});

  // create window
  SDL_Window* window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN.x, SCREEN.y, 0);
  SDL_Surface* surface_window = SDL_GetWindowSurface(window);
  if (window == NULL || surface_window == NULL) {
    std::cout << "Error while creating window or when retrieving its surface" << std::endl;
    return 1;
  }

  // renderer used for textures (fps = monitor refresh rate)
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // load images inside textures
  Texture background(renderer, Image("assets/images/background.png"));

  // timer texture
  Texture timer_text(renderer, Text("Timer: 0s", font));
  Timer timer;

  // fps texture
  int n_frames = 0;
  Texture fps_text(renderer, Text("FPS: 0", font));
  Timer fps_timer;

  // red ball
  Texture ball_red(renderer, Image("assets/images/ball.png"));
  int x_ball = -100;
  int y_ball = -100;

  // human character
  Texture character(renderer, Image("assets/images/character.png"));
  std::vector<SDL_Rect> rects_src {
    {0,   0, 64,  205},
    {64,  0, 64, 205},
    {128, 0, 64, 205},
    {192, 0, 64, 205},
  };
  unsigned char frame_character = 0;

  // props non-movable sprites
  SpriteRectangle sprite_prop(renderer, {200, 200, SCREEN.x - 400, 25});

  // sprites for movable rectangle
  SpriteRectangle sprite(renderer, {SCREEN.x / 2, SCREEN.y / 2, 100, 100});

  // scrolling clouds
  Texture clouds(renderer, Image("assets/images/clouds.png"));
  int offset_clouds = 0;

  // particles emitter
  SDL_Point position_sprite(sprite.get_position());
  ParticleEmitter particle_emitter(position_sprite, {
    Texture(renderer, Image("assets/images/particles/blue.bmp")),
    Texture(renderer, Image("assets/images/particles/green.bmp")),
    Texture(renderer, Image("assets/images/particles/red.bmp"))
  }, Texture(renderer, Image("assets/images/particles/shine.bmp")));

  // main loop
  SDL_Event event;
  bool is_quit = false;

  while (!is_quit) {
    // listen for events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            is_quit = true;
            break;
          case SDLK_SPACE:
            timer.toggle();
            break;

          // move blue ball with directional arrows
          case SDLK_UP:
            sprite.set_direction(Direction::UP);
            break;
          case SDLK_DOWN:
            sprite.set_direction(Direction::DOWN);
            break;
          case SDLK_LEFT:
            sprite.set_direction(Direction::LEFT);
            break;
          case SDLK_RIGHT:
            sprite.set_direction(Direction::RIGHT);
            break;
        }
      } else if (event.type == SDL_KEYUP) {
        sprite.set_direction(Direction::NONE);
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
       if (event.button.button == SDL_BUTTON_LEFT) {
          x_ball = event.button.x - (ball_red.get_width() / 4);
          y_ball = event.button.y - (ball_red.get_height() / 4);
          Mix_PlayChannel(-1, effect, 0);
        }
      }
    }

    // update coordinates of mobile sprites & camera accordingly
    sprite.move();
    camera.track(sprite, LEVEL);

    // clear screen in white
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff ,0xff);
    SDL_RenderClear(renderer);

    // render background & text
    SDL_Rect rect_camera = camera.rect();
    background.render({0, 0}, &rect_camera);

    // render moving clouds twice (right-to-left scrolling)
    clouds.render({offset_clouds, 0});
    clouds.render({offset_clouds + clouds.get_width(), 0});
    --offset_clouds;
    if (offset_clouds < -clouds.get_width()) {
      offset_clouds = 0;
    }

    // show time in text texture
    std::stringstream timer_str;
    timer_str << "Timer: " << static_cast<int>(timer.get_ticks()) << "s";
    timer_text.update(Text(timer_str.str(), font));
    timer_text.render({0, SCREEN.y - timer_text.get_height()});

    // show FPS in text texture
    ++n_frames;
    int fps = n_frames / fps_timer.get_ticks();
    std::stringstream fps_str;
    fps_str << "FPS: " << fps;
    fps_text.update(Text(fps_str.str(), font));
    fps_text.render({SCREEN.x - fps_text.get_width(), SCREEN.y - fps_text.get_height()});

    // draw red ball at mouse click location
    SDL_Rect rect_src_ball {0, 0, 100, 100};
    ball_red.render({x_ball - camera.x, y_ball - camera.y}, &rect_src_ball);

    // draw props sprites
    sprite_prop.render(camera);

    // draw movable sprite rectangle (relative to camera) & check for its collision
    sprite.check_collision(LEVEL);
    sprite.check_collision(sprite_prop);
    sprite.render(camera);

    // render particles using emitter
    position_sprite = {sprite.get_position()};
    particle_emitter.render({position_sprite.x - camera.x, position_sprite.y - camera.y});

    // render character frames
    character.render({SCREEN.x / 2 - camera.x, SCREEN.y / 2 - camera.y}, &rects_src[frame_character / 4]);
    ++frame_character;
    if (frame_character == 16) {
      frame_character = 0;
    }

    // update screen
    SDL_RenderPresent(renderer);
  }

  // free font
  TTF_CloseFont(font);
  font = NULL;

  // destroy renderer (and its textures) & window
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  surface_window = NULL;

  // destroy audio sounds
  Mix_FreeChunk(effect);
  effect = NULL;
  Mix_FreeMusic(music);
  music = NULL;

  // clean-up extensions & SDL
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}
