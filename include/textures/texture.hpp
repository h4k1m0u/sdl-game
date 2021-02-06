#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL.h>

class Texture {
public:
  Texture(SDL_Renderer* renderer);
  ~Texture();
  void render(int x, int y, SDL_Rect* rect_src=NULL);
  int get_width() const;
  int get_height() const;
  void set_texture(SDL_Surface* surface);

protected:
  SDL_Renderer* m_renderer;

private:
  SDL_Texture* m_texture;
  int m_width;
  int m_height;
};

#endif // TEXTURE_HPP
