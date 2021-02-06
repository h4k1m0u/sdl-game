#ifndef TEXTURE_CIRCLE_HPP
#define TEXTURE_CIRCLE_HPP

#include <textures/texture.hpp>

class TextureCircle : public Texture {
public:
  TextureCircle(SDL_Renderer* renderer, int radius);
  void render(int x, int y);

private:
  int m_radius;
};

#endif // TEXTURE_CIRCLE_HPP
