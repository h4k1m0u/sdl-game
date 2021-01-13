#include <SDL.h>
#include <stdio.h>

int main() {
  // initialize sdl
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error while initializing SDL");
    return 1;
  }

  // create window
  const int WIDTH_WINDOW = 640;
  const int HEIGHT_WINDOW = 480;
  SDL_Window* window = SDL_CreateWindow("My SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH_WINDOW, HEIGHT_WINDOW, 0) ;
  if (window == NULL) {
    printf("Error while creating window");
    return 1;
  }

  // change window color
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 255));
  SDL_UpdateWindowSurface(window);

  // sleep for 2s
  SDL_Delay(3000);

  // destroy window & clean up sdl
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
