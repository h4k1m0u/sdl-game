#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

#include <SDL.h>
#include <vector>
#include <particles/particle.hpp>

class ParticleEmitter {
public:
  ParticleEmitter(const SDL_Point& position, const std::vector<Texture>& textures, const Texture& texture_shine);
  ~ParticleEmitter();
  void render(const SDL_Point& position);

private:
  std::vector<Texture> m_textures; 
  Texture m_texture_shine;
  std::vector<Particle> m_particles; 
  static const Uint8 N_PARTICLES = 20;

  Particle create_particle(const SDL_Point& position);
};

#endif // PARTICLE_EMITTER_HPP
