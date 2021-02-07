#ifndef TEXTURE_CIRCLE_HPP
#define TEXTURE_CIRCLE_HPP

#include <textures/texture.hpp>
#include <surfaces/circle.hpp>

class TextureCircle : public Texture {
public:
  TextureCircle(SDL_Renderer* renderer, const Circle& circle);
  void render(const SDL_Point& position);
};

#endif // TEXTURE_CIRCLE_HPP
