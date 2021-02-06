#include <textures/texture_rectangle.hpp>

TextureRectangle::TextureRectangle(SDL_Renderer* renderer, const SDL_Point& dimensions):
  Texture(renderer)
{
  // draw rectangle into surface
  SDL_Surface* surface = SDL_CreateRGBSurface(0, dimensions.x, dimensions.y, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xff, 0x00, 0x00));
  set_texture(surface);
}
