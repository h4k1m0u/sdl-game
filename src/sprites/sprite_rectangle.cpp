#include <sprites/sprite_rectangle.hpp>
#include <algorithm>

SpriteRectangle::SpriteRectangle(SDL_Renderer* renderer, const SDL_Rect& rect):
  Sprite({rect.x, rect.y}),
  m_texture(TextureRectangle(renderer, {rect.w, rect.h}))
{
}

void SpriteRectangle::render() {
  m_texture.render(m_x, m_y);
}

bool SpriteRectangle::limits_reached(const SDL_Point& canvas) {
  if (m_x < 0 || m_x > canvas.x - m_texture.get_width() || m_y < 0 || m_y > canvas.y - m_texture.get_height()) {
    return true;
  }
  return false;
}

void SpriteRectangle::check_collision(const SDL_Point& canvas, const SDL_Rect& rect_wall) {
  // confine sprite to canvas limits & stop it from moving once outside
  if (limits_reached(canvas)) {
    m_x -= m_velocity_x;
    m_y -= m_velocity_y;
    set_direction(Direction::NONE);
    return;
  }

  // two extremities of sprite bounding box
  SDL_Point p1 {m_x, m_y};
  SDL_Point p2 {m_x + m_texture.get_width(), m_y + m_texture.get_height()};

  // two extremities of wall bounding box
  SDL_Point p3 {rect_wall.x, rect_wall.y};
  SDL_Point p4 {rect_wall.x + rect_wall.w, rect_wall.y + rect_wall.h};

  // calculate intersection rectangle: https://stackoverflow.com/a/19754915/2228912
  SDL_Point p5 {std::max(p1.x, p3.x), std::max(p1.y, p3.y)};
  SDL_Point p6 {std::min(p2.x, p4.x), std::min(p2.y, p4.y)};

  // stop sprite on bboxes intersection
  if (p5.x < p6.x && p5.y < p6.y) {
    m_x -= m_velocity_x;
    m_y -= m_velocity_y;
    set_direction(Direction::NONE);
  }
}
