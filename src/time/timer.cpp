#include <time/timer.hpp>
#include <iostream>

Timer::Timer():
  m_ticks(0),
  m_ticks_paused(0),
  m_paused(false)
{
}

float Timer::get_ticks() {
  // consider accumulated times spent counting & pausing
  if (!m_paused) {
    m_ticks = SDL_GetTicks() - m_ticks_paused;
  } else {
    m_ticks_paused = SDL_GetTicks() - m_ticks;
  }

  // use float to avoid div by 0 at start
  return m_ticks / 1000.0f;
}

bool Timer::is_paused() const {
  return m_paused;
}

void Timer::toggle() {
  m_paused = !m_paused;
}
