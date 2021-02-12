#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SDL.h>
#include <vector>
#include <textures/texture.hpp>

class Particle {
public:
  Particle(const SDL_Point& position, const Texture& texture, const Texture& texture_shine);
  void render();
  bool is_dead();

private:
  SDL_Point m_position;
  Texture m_texture;
  Texture m_texture_shine;
  Uint8 m_age;
  static const Uint8 LIFETIME = 20;
};

#endif // PARTICLE_HPP
