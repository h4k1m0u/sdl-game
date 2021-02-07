#include <surfaces/rectangle.hpp>

Rectangle::Rectangle(const SDL_Point& dimensions, const SDL_Color& color) {
  // draw rectangle into surface
  surf = SDL_CreateRGBSurface(0, dimensions.x, dimensions.y, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, color.r, color.g, color.b));
  size = {surf->w, surf->h};
}
