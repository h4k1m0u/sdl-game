#include <sprites/sprite.hpp>
#include <algorithm>

Sprite::Sprite(const SDL_Point& p):
  m_x(p.x),
  m_y(p.y),
  m_velocity_x(0),
  m_velocity_y(0),
  m_direction(Direction::NONE)
{
}

void Sprite::set_direction(Direction direction) {
  m_direction = direction;
}

void Sprite::move() {
  // restrict direction to either horizontal or vertical
  switch (m_direction) {
    case Direction::NONE:
      m_velocity_x = 0;
      m_velocity_y = 0;
      break;
    case Direction::UP:
      m_velocity_y = -VELOCITY;
      m_velocity_x = 0;
      break;
    case Direction::DOWN:
      m_velocity_y = VELOCITY;
      m_velocity_x = 0;
      break;
    case Direction::LEFT:
      m_velocity_x = -VELOCITY;
      m_velocity_y = 0;
      break;
    case Direction::RIGHT:
      m_velocity_x = VELOCITY;
      m_velocity_y = 0;
      break;
  }

  // move accord. to velocity
  m_x += m_velocity_x;
  m_y += m_velocity_y;
}

int Sprite::get_x() const {
  return m_x;
}

int Sprite::get_y() const {
  return m_y;
}
