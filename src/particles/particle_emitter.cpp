#include <particles/particle_emitter.hpp>
#include <cstdlib>
#include <iostream>

ParticleEmitter::ParticleEmitter(const SDL_Point& position, const std::vector<Texture>& textures, const Texture& texture_shine):
  m_textures(textures),
  m_texture_shine(texture_shine)
{
  // random texture & lifetime for each particle
  for (size_t i_particle = 0; i_particle < N_PARTICLES; ++i_particle) {
    m_particles.push_back(create_particle(position));
  }
}

void ParticleEmitter::render(const SDL_Point& position) {
  for (size_t i_particle = 0; i_particle < N_PARTICLES; ++i_particle) {
    // replace dead particles at new position
    if (m_particles[i_particle].is_dead()) {
      m_particles[i_particle] = create_particle(position);
    }

    // render each particle at initial position for at most LIFETIME frames
    m_particles[i_particle].render();
  }
}

Particle ParticleEmitter::create_particle(const SDL_Point& position) {
  // generate particle with random texture at position
  Texture texture(m_textures[rand() % m_textures.size()]);

  return Particle(position, texture, m_texture_shine);
}

ParticleEmitter::~ParticleEmitter() {
  // free particle textures
  m_texture_shine.free();
  for (Texture& texture : m_textures) {
    texture.free();
  }
}
