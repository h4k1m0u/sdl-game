#include <textures/texture_image.hpp>
#include <SDL_image.h>

TextureImage::TextureImage(SDL_Renderer* renderer, const std::string& path):
  Texture(renderer)
{
  // texture from image & set transparent color
  SDL_Surface* surface = IMG_Load(path.c_str());
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0xff, 0xff));
  set_texture(surface);
}
