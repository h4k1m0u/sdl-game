#ifndef SPRITE_CIRCLE_HPP
#define SPRITE_CIRCLE_HPP

#include <sprites/sprite.hpp>
#include <sprites/sprite_rectangle.hpp>
#include <textures/texture_circle.hpp>
#include <navigation/camera.hpp>

class SpriteCircle : public Sprite {
public:
  SpriteCircle(SDL_Renderer* renderer, const SDL_Point& center, int radius);
  void render();
  void render(const Camera& camera);
  void check_collision(const SDL_Point& size_canvas);
  void check_collision(const SpriteCircle& sprite_circle);
  void check_collision(const SpriteRectangle& sprite_rect);
  int get_radius() const;
  SDL_Point get_center() const;

private:
  TextureCircle m_texture;
  int m_radius;
  SDL_Point m_center;
};

#endif // SPRITE_CIRCLE_HPP
