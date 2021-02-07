#include <sprites/sprite_circle.hpp>
#include <surfaces/circle.hpp>
#include <iostream>

SpriteCircle::SpriteCircle(SDL_Renderer* renderer, const SDL_Point& center, int radius):
  Sprite(center),
  m_texture(TextureCircle(renderer, Circle(radius))) 
{
}

void SpriteCircle::render() {
  m_texture.render(m_position);
}

void SpriteCircle::check_collision(const SDL_Point& size_canvas) {
  // prevent sprite from leaving screen
  int radius = m_texture.get_width() / 2;
  confine({radius, radius, size_canvas.x - radius, size_canvas.y - radius});
}
