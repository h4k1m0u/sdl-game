#include <textures/texture_circle.hpp>
#include <SDL2/SDL2_gfxPrimitives.h>

TextureCircle::TextureCircle(SDL_Renderer* renderer, const Circle& circle):
  Texture(renderer, circle)
{
}

void TextureCircle::render(const SDL_Point& position) {
  // draw circle with sdl2-gfx (color in ABGR format)
  filledCircleColor(m_renderer, position.x, position.y, get_width() / 2, 0xFFFF0000);
}
