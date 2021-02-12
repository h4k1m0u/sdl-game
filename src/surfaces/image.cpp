#include <surfaces/image.hpp>
#include <SDL_image.h>
#include <iostream>

Image::Image(const std::string& path) {
  // load image & set transparent color
  surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    std::cout << "Image: " << path << " couldn't be opened" << std::endl;
    return;
  }

  SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0x00, 0xff, 0xff));
  size = {surf->w, surf->h};
}
