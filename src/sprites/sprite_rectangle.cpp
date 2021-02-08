#include <sprites/sprite_rectangle.hpp>
#include <surfaces/rectangle.hpp>
#include <algorithm>

SpriteRectangle::SpriteRectangle(SDL_Renderer* renderer, const SDL_Rect& rect):
  Sprite({rect.x, rect.y}),
  m_texture(Texture(renderer, Rectangle({rect.w, rect.h}, {0xff, 0x00, 0x00}))),
  m_width(m_texture.get_width()),
  m_height(m_texture.get_height())
{
}

void SpriteRectangle::render() {
  m_texture.render(m_position);
}

void SpriteRectangle::check_collision(const SDL_Point& size_canvas) {
  // prevent sprite from leaving screen
  confine({0, 0, size_canvas.x - m_width, size_canvas.y - m_height});
}

void SpriteRectangle::check_collision(const SpriteRectangle& sprite_rect) {
  // two extremities of sprite bounding box
  SDL_Point p1(m_position);
  SDL_Point p2 {m_position.x + m_width, m_position.y + m_height};

  // two extremities of rectangle to collide with
  SDL_Point position = sprite_rect.get_position();
  SDL_Point size = {sprite_rect.get_width(), sprite_rect.get_height()};
  SDL_Point p3 {position.x, position.y};
  SDL_Point p4 {position.x + size.x, position.y + size.y};

  // calculate intersection rectangle: https://stackoverflow.com/a/19754915/2228912
  SDL_Point p5 {std::max(p1.x, p3.x), std::max(p1.y, p3.y)};
  SDL_Point p6 {std::min(p2.x, p4.x), std::min(p2.y, p4.y)};

  // stop sprite on bboxes intersection
  if (p5.x < p6.x && p5.y < p6.y) {
    m_position.x -= m_velocity.x;
    m_position.y -= m_velocity.y;
    set_direction(Direction::NONE);
  }
}

int SpriteRectangle::get_width() const {
  return m_width;
}

int SpriteRectangle::get_height() const {
  return m_height;
}
