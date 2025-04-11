#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL_timer.h>

class Timer {
public:
  Timer();

  void start();

  void delay();

private:
  Uint64 frame_start_time;
  const Uint64 ns_per_frame = 1000000000 / 30;
  Uint64 frame_time;
};

#endif
