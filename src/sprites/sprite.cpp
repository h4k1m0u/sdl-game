#include <sprites/sprite.hpp>
#include <iostream>

Sprite::Sprite(const SDL_Point& position):
  m_position(position),
  m_velocity {0, 0},
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
      m_velocity = {0, 0};
      break;
    case Direction::UP:
      m_velocity = {0, -VELOCITY};
      break;
    case Direction::DOWN:
      m_velocity = {0, VELOCITY};
      break;
    case Direction::LEFT:
      m_velocity = {-VELOCITY, 0};
      break;
    case Direction::RIGHT:
      m_velocity = {VELOCITY, 0};
      break;
  }

  // move accord. to velocity
  m_position.x += m_velocity.x;
  m_position.y += m_velocity.y;
}

int Sprite::get_x() const {
  return m_position.x;
}

int Sprite::get_y() const {
  return m_position.y;
}

void Sprite::confine(const SDL_Rect& canvas) {
  // confine position to range of coords (x to w, y to h)
  if (m_position.x < canvas.x || m_position.x > canvas.w ||
      m_position.y < canvas.y || m_position.y > canvas.h) {
    m_position.x -= m_velocity.x;
    m_position.y -= m_velocity.y;
    set_direction(Direction::NONE);
  }
}
