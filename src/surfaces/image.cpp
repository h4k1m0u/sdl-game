#include <surfaces/image.hpp>
#include <SDL_image.h>

Image::Image(const std::string& path) {
  // load image & set transparent color
  surf = IMG_Load(path.c_str());
  SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0x00, 0xff, 0xff));
  size = {surf->w, surf->h};
}
