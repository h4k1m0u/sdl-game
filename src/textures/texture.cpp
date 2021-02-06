#include <textures/texture.hpp>

Texture::Texture(SDL_Renderer* renderer):
  m_renderer(renderer),
  m_texture(NULL),
  m_width(0),
  m_height(0)
{
}

void Texture::set_texture(SDL_Surface* surface) {
  // convert to texture & free surface
  m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  m_width = surface->w;
  m_height = surface->h;
  SDL_FreeSurface(surface);
  surface = NULL;
}

void Texture::render(int x, int y, SDL_Rect* rect_src) {
  // render texture at position (upper-left corner given)
  SDL_Rect rect_dst {x, y, m_width, m_height};

  // rectangle used to crop texture
  if (rect_src != NULL) {
    rect_dst.w = rect_src->w;
    rect_dst.h = rect_src->h;
  }

  SDL_RenderCopy(m_renderer, m_texture, rect_src, &rect_dst);
}

Texture::~Texture() {
  SDL_DestroyTexture(m_texture);
  m_texture = NULL;
}

int Texture::get_width() const {
  return m_width;
}

int Texture::get_height() const {
  return m_height;
}
