#ifndef TEXT_HPP
#define TEXT_HPP

#include <surfaces/surface.hpp>
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>

struct Text : public Surface {
  Text(const std::string& text, TTF_Font* font);
};

#endif // TEXT_HPP
