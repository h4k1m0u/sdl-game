#ifndef TEXTURE_IMAGE_HPP
#define TEXTURE_IMAGE_HPP

#include <textures/texture.hpp>
#include <string>

class TextureImage : public Texture {
public:
  TextureImage(SDL_Renderer* renderer, const std::string& path);
};

#endif // TEXTURE_IMAGE_HPP
