#ifndef SPRITE_RECTANGLE_HPP
#define SPRITE_RECTANGLE_HPP

#include <sprites/sprite.hpp>
#include <textures/texture_rectangle.hpp>

class SpriteRectangle : public Sprite {
public:
  SpriteRectangle(SDL_Renderer* renderer, const SDL_Rect& rect);
  bool limits_reached(const SDL_Point& canvas);
  void check_collision(const SDL_Point& canvas, const SDL_Rect& rect_wall);
  void render();

private:
  TextureRectangle m_texture;
};

#endif // SPRITE_RECTANGLE_HPP
