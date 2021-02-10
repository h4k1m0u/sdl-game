#include <navigation/camera.hpp>

Camera::Camera(const SDL_Rect& rectangle):
  x(rectangle.x),
  y(rectangle.y),
  w(rectangle.w),
  h(rectangle.h)
{
}

SDL_Rect Camera::rect() {
  return {x, y, w, h};
}

void Camera::track(const Sprite& sprite, const SDL_Point& size_level) {
  // camera tracks mobile sprites within confines of level
  SDL_Point position_sprite = sprite.get_position();    
  x = position_sprite.x - w / 2;
  y = position_sprite.y - h / 2;

  if (x < 0) {
    x = 0;
  } else if (x > size_level.x - w) {
    x = size_level.x - w;
  }

  if (y < 0) {
    y = 0;
  } else if (y > size_level.y - h) {
    y = size_level.y - h;
  }
}
