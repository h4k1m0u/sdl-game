#include <particles/particle.hpp>
#include <cstdlib>
#include <iostream>

Particle::Particle(const SDL_Point& position, const Texture& texture, const Texture& texture_shine):
  m_position(position),
  m_texture(texture),
  m_texture_shine(texture_shine),
  m_age(rand() % LIFETIME)
{
}

void Particle::render() {
  // render at random adjacent position
  SDL_Point offset {rand() % 25, rand() % 25};
  SDL_Point position {m_position.x + offset.x, m_position.y + offset.y};
  m_texture.render(position, NULL, 127);

  // shine particle every other frame
  if (m_age % 2 == 0) {
    m_texture_shine.render(position, NULL, 127);
  }

  ++m_age;
}

bool Particle::is_dead() {
  return m_age == LIFETIME;
}
