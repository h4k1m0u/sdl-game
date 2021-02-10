#include <sprites/sprite_circle.hpp>
#include <cmath>
#include <iostream>

SpriteCircle::SpriteCircle(SDL_Renderer* renderer, const SDL_Point& center, int radius):
  Sprite(center),
  m_texture(TextureCircle(renderer, Circle(radius))),
  m_radius(radius),
  m_center(center)
{
}

void SpriteCircle::render() {
  m_texture.render(m_position);
}

void SpriteCircle::render(const Camera& camera) {
  // rendering relatively to camera coordinates (keeps sprite centered)
  m_texture.render({m_position.x - camera.x, m_position.y - camera.y});
}

int SpriteCircle::get_radius() const {
  return m_radius;
}

SDL_Point SpriteCircle::get_center() const {
  return m_center;
}

void SpriteCircle::check_collision(const SDL_Point& size_canvas) {
  // prevent sprite from leaving screen
  confine({m_radius, m_radius, size_canvas.x - m_radius, size_canvas.y - m_radius});
}

void SpriteCircle::check_collision(const SpriteCircle& sprite_circle) {
  // circle to check collision against
  SDL_Point center = sprite_circle.get_center();
  int radius = sprite_circle.get_radius();

  // calculate distance between two centers
  int distance_sq = std::pow(m_position.x - center.x, 2) + std::pow(m_position.y - center.y, 2);
  int sum_radiuses_sq = std::pow(radius + m_radius, 2);

  // collision when distance smaller than sum of two radiuses
  if (distance_sq < sum_radiuses_sq) {
    m_position.x -= m_velocity.x;
    m_position.y -= m_velocity.y;
    set_direction(Direction::NONE);
  }
}

void SpriteCircle::check_collision(const SpriteRectangle& sprite_rect) {
  // rectangle to check collision against
  SDL_Point position = sprite_rect.get_position();
  SDL_Point size = {sprite_rect.get_width(), sprite_rect.get_height()};

  // find closest rectangle point to circle by projection
  SDL_Point projection;
  if (m_position.x < position.x) {
    projection.x = position.x;
  } else if (m_position.x < position.x + size.x) {
    projection.x = m_position.x;
  } else {
    projection.x = position.x + size.x;
  }

  if (m_position.y < position.y) {
    projection.y = position.y;
  } else if (m_position.y < position.y + size.y) {
    projection.y = m_position.y;
  } else {
    projection.y = position.y + size.y;
  }

  // calculate distance between projection & circle center
  int distance_sq = std::pow(m_position.x - projection.x, 2) + std::pow(m_position.y - projection.y, 2);
  int sum_radiuses_sq = std::pow(m_radius, 2);

  // collision when distance smaller than sum of two radiuses
  if (distance_sq < sum_radiuses_sq) {
    m_position.x -= m_velocity.x;
    m_position.y -= m_velocity.y;
    set_direction(Direction::NONE);
  }
}
