#include <textures/texture.hpp>
#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const Surface& surface):
  m_renderer(renderer),
  m_texture(NULL),
  m_size(surface.size)
{
  // convert surface to texture
  m_texture = SDL_CreateTextureFromSurface(m_renderer, surface.surf);
}

void Texture::free() {
  // called from texture owner (sprite or particle emitter)
  SDL_DestroyTexture(m_texture);
  m_texture = NULL;
}

void Texture::update(const Surface& surface) {
  // used to update timer text
  m_texture = SDL_CreateTextureFromSurface(m_renderer, surface.surf);
}

void Texture::render(const SDL_Point& position, SDL_Rect* rect_src, Uint8 transparency) const {
  // render texture at position (upper-left corner given)
  SDL_Rect rect_dst {position.x, position.y, get_width(), get_height()};

  // rectangle used to crop texture
  if (rect_src != NULL) {
    rect_dst.w = rect_src->w;
    rect_dst.h = rect_src->h;
  }

  // apply transparency
  SDL_SetTextureAlphaMod(m_texture, transparency);
  SDL_RenderCopy(m_renderer, m_texture, rect_src, &rect_dst);
}

int Texture::get_width() const {
  return m_size.x;
}

int Texture::get_height() const {
  return m_size.y;
}
