#include <textures/texture_text.hpp>

TextureText::TextureText(SDL_Renderer* renderer, const std::string& text, TTF_Font* font):
  Texture(renderer),
  m_font(font)
{
  update_text(text);
}

void TextureText::update_text(const std::string& text) {
  // texture from given text
  SDL_Surface* surface = TTF_RenderText_Shaded(m_font, text.c_str(), {0xff, 0xff, 0xff}, {0x00, 0x00, 0x00});
  set_texture(surface);
}
