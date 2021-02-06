#include <sprites/sprite_circle.hpp>
#include <algorithm>

SpriteCircle::SpriteCircle(SDL_Renderer* renderer, const SDL_Point& center, int radius):
  Sprite(center),
  m_texture(TextureCircle(renderer, radius))
{
}

void SpriteCircle::render() {
  m_texture.render(m_x, m_y);
}
