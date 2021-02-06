#ifndef SPRITE_CIRCLE_HPP
#define SPRITE_CIRCLE_HPP

#include <sprites/sprite.hpp>
#include <textures/texture_circle.hpp>

class SpriteCircle : public Sprite {
public:
  SpriteCircle(SDL_Renderer* renderer, const SDL_Point& center, int radius);
  void render();

private:
  TextureCircle m_texture;
};

#endif // SPRITE_CIRCLE_HPP
