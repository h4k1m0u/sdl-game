#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <textures/texture.hpp>
#include <sprites/direction.hpp>

class Sprite {
public:
  Sprite(const SDL_Point& p);
  void move();
  int get_x() const;
  int get_y() const;
  void set_direction(Direction direction);

protected:
  int m_x;
  int m_y;
  int m_velocity_x;
  int m_velocity_y;

private:
  Direction m_direction;
  const int VELOCITY = 5;
};

#endif // SPRITE_HPP
