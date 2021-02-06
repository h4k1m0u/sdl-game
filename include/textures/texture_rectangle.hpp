#ifndef TEXTURE_RECTANGLE_HPP
#define TEXTURE_RECTANGLE_HPP

#include <textures/texture.hpp>

class TextureRectangle : public Texture {
public:
  TextureRectangle(SDL_Renderer* renderer, const SDL_Point& dimensions);
};

#endif // TEXTURE_RECTANGLE_HPP
