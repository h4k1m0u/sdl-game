#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <sprites/direction.hpp>

class Sprite {
public:
  Sprite(const SDL_Point& position);
  void move();
  void set_direction(Direction direction);
  SDL_Point get_position() const;

protected:
  SDL_Point m_position;
  SDL_Point m_velocity;

  void confine(const SDL_Rect& canvas);

private:
  Direction m_direction;
  const int VELOCITY = 5;
};

#endif // SPRITE_HPP
