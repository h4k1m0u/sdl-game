#include <sprites/sprite_rectangle.hpp>
#include <surfaces/rectangle.hpp>
#include <algorithm>

SpriteRectangle::SpriteRectangle(SDL_Renderer* renderer, const SDL_Rect& rect):
  Sprite({rect.x, rect.y}),
  m_texture(Texture(renderer, Rectangle({rect.w, rect.h}, {0xff, 0x00, 0x00})))
{
}

void SpriteRectangle::render() {
  m_texture.render(m_position);
}

void SpriteRectangle::check_collision(const SDL_Point& size_canvas) {
  // prevent sprite from leaving screen
  int width = m_texture.get_width();
  int height = m_texture.get_height();
  confine({0, 0, size_canvas.x - width, size_canvas.y - height});
}

void SpriteRectangle::check_collision(const SDL_Rect& rect_wall) {
  // two extremities of sprite bounding box
  SDL_Point p1(m_position);
  SDL_Point p2 {m_position.x + m_texture.get_width(), m_position.y + m_texture.get_height()};

  // two extremities of wall bounding box
  SDL_Point p3 {rect_wall.x, rect_wall.y};
  SDL_Point p4 {rect_wall.x + rect_wall.w, rect_wall.y + rect_wall.h};

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
