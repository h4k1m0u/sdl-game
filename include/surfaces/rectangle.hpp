#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <surfaces/surface.hpp>
#include <SDL.h>
#include <string>

struct Rectangle : public Surface {
  Rectangle(const SDL_Point& dimensions, const SDL_Color& color);
};

#endif // RECTANGLE_HPP
