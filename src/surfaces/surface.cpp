#include <surfaces/surface.hpp>

Surface::Surface():
  surf(NULL),
  size({0, 0})
{
}

Surface::~Surface() {
  SDL_FreeSurface(surf);
  surf = NULL;
}
