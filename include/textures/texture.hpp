#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL.h>
#include <surfaces/surface.hpp>

class Texture {
public:
  Texture(SDL_Renderer* renderer, const Surface& surface);
  void free();
  void update(const Surface& surface);
  void render(const SDL_Point& position, SDL_Rect* rect_src=NULL, Uint8 transparency=0xff) const;
  int get_width() const;
  int get_height() const;
  void set_texture(SDL_Surface* surface);

protected:
  SDL_Renderer* m_renderer;

private:
  SDL_Texture* m_texture;
  SDL_Point m_size;
};

#endif // TEXTURE_HPP
