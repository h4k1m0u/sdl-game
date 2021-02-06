#ifndef TEXTURE_TEXT_HPP
#define TEXTURE_TEXT_HPP

#include <textures/texture.hpp>
#include <string>
#include <SDL_ttf.h>

class TextureText : public Texture {
public:
  TextureText(SDL_Renderer* renderer, const std::string& text, TTF_Font* font);
  void update_text(const std::string& text);

private:
  TTF_Font* m_font;
};

#endif // TEXTURE_TEXT_HPP
