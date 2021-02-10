#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL.h>
#include <sprites/sprite.hpp>

struct Camera {
  Camera(const SDL_Rect& rectangle);
  SDL_Rect rect();
  void track(const Sprite& sprite, const SDL_Point& size_level);

  int x;
  int y;
  int w;
  int h;
};

#endif // CAMERA_HPP
