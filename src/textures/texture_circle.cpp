#include <textures/texture_circle.hpp>
#include <SDL2/SDL2_gfxPrimitives.h>

TextureCircle::TextureCircle(SDL_Renderer* renderer, int radius):
  Texture(renderer),
  m_radius(radius)
{
}

void TextureCircle::render(int x, int y) {
  // draw circle with sdl2-gfx (color in ABGR format)
  filledCircleColor(m_renderer, x, y, m_radius, 0xFFFF0000);
}
