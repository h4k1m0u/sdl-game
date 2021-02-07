#ifndef SPRITE_RECTANGLE_HPP
#define SPRITE_RECTANGLE_HPP

#include <sprites/sprite.hpp>
#include <textures/texture.hpp>

class SpriteRectangle : public Sprite {
public:
  SpriteRectangle(SDL_Renderer* renderer, const SDL_Rect& rect);
  void render();
  void check_collision(const SDL_Point& size_canvas);
  void check_collision(const SDL_Rect& rect_wall);

private:
  Texture m_texture;
};

#endif // SPRITE_RECTANGLE_HPP
