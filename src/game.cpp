#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <time/timer.hpp>
#include <textures/texture.hpp>
#include <textures/texture_image.hpp>
#include <textures/texture_text.hpp>
#include <textures/texture_rectangle.hpp>
#include <textures/texture_circle.hpp>
#include <sprites/direction.hpp>
#include <sprites/sprite_rectangle.hpp>
#include <sprites/sprite_circle.hpp>

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

  // create window
  const SDL_Point CANVAS {800, 600};
  SDL_Window* window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CANVAS.x, CANVAS.y, 0);
  SDL_Surface* surface_window = SDL_GetWindowSurface(window);
  if (window == NULL || surface_window == NULL) {
    std::cout << "Error while creating window or when retrieving its surface" << std::endl;
    return 1;
  }

  // renderer used for textures (fps = monitor refresh rate)
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // load images inside textures
  TextureImage background(renderer, "assets/images/background.png");

  // timer texture
  TextureText timer_text(renderer, "Timer: 0s", font);
  Timer timer;

  // fps texture
  int n_frames = 0;
  TextureText fps_text(renderer, "FPS: 0", font);
  Timer fps_timer;

  // red ball
  TextureImage ball_red(renderer, "assets/images/ball.png");
  int x_ball = -100;
  int y_ball = -100;

  // human character
  TextureImage character(renderer, "assets/images/character.png");
  std::vector<SDL_Rect> rects_src {
    {0,   0, 64,  205},
    {64,  0, 64, 205},
    {128, 0, 64, 205},
    {192, 0, 64, 205},
  };
  unsigned char frame_character = 0;

  // sprites for rectangle & circle
  SpriteRectangle rect_sprite(renderer, {0, 0, 100, 100});
  SpriteCircle circle_sprite(renderer, {CANVAS.x / 3, CANVAS.y / 3}, 50);

  // wall
  SDL_Rect rect_wall {200, 200, CANVAS.x - 400, 25};

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
            rect_sprite.set_direction(Direction::UP);
            break;
          case SDLK_DOWN:
            rect_sprite.set_direction(Direction::DOWN);
            break;
          case SDLK_LEFT:
            rect_sprite.set_direction(Direction::LEFT);
            break;
          case SDLK_RIGHT:
            rect_sprite.set_direction(Direction::RIGHT);
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
       if (event.button.button == SDL_BUTTON_LEFT) {
          x_ball = event.button.x - (ball_red.get_width() / 4);
          y_ball = event.button.y - (ball_red.get_height() / 4);
          Mix_PlayChannel(-1, effect, 0);
        }
      }
    }

    // clear screen in white
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff ,0xff);
    SDL_RenderClear(renderer);

    // render background & text
    SDL_Rect rect_src_bg {0, 0, CANVAS.x, CANVAS.y};
    background.render(0, 0, &rect_src_bg);

    // show time in text texture
    std::stringstream timer_str;
    timer_str << "Timer: " << static_cast<int>(timer.get_ticks()) << "s";
    timer_text.update_text(timer_str.str());
    timer_text.render(0, CANVAS.y - timer_text.get_height());

    // show FPS in text texture
    ++n_frames;
    int fps = n_frames / fps_timer.get_ticks();
    std::stringstream fps_str;
    fps_str << "FPS: " << fps;
    fps_text.update_text(fps_str.str());
    fps_text.render(CANVAS.x - fps_text.get_width(), CANVAS.y - fps_text.get_height());

    // draw red ball at mouse click location
    SDL_Rect rect_src_ball {0, 0, 100, 100};
    ball_red.render(x_ball, y_ball, &rect_src_ball);

    // draw movable red rectangle
    rect_sprite.move();
    rect_sprite.check_collision(CANVAS, rect_wall);
    rect_sprite.render();

    // draw green circle
    circle_sprite.render();

    // draw horizontal wall
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00,0xff);
    SDL_RenderFillRect(renderer, &rect_wall);

    // render character frames
    character.render(CANVAS.x / 2, CANVAS.y / 2, &rects_src[frame_character / 4]);
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
