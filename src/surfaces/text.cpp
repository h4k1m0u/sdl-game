#include <surfaces/text.hpp>

Text::Text(const std::string& text, TTF_Font* font) {
  surf = TTF_RenderText_Shaded(font, text.c_str(), {0xff, 0xff, 0xff}, {0x00, 0x00, 0x00});
  size = {surf->w, surf->h};
}
