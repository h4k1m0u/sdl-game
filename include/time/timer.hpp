#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>

class Timer {
public:
  Timer();
  float get_ticks();
  bool is_paused() const;
  void toggle();

private:
  Uint32 m_ticks;
  Uint32 m_ticks_paused;
  bool m_paused;
};

#endif // TIMER_HPP
