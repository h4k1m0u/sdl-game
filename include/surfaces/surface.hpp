#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <SDL.h>

struct Surface {
  Surface();
  ~Surface();

  SDL_Surface* surf;
  SDL_Point size;
};

#endif // SURFACE_HPP
