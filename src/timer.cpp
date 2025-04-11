#include "../include/timer.h"

Timer::Timer() {};

void Timer::start() { frame_start_time = SDL_GetTicksNS(); };

void Timer::delay() {
  frame_time = SDL_GetTicksNS() - frame_start_time;
  if (frame_time < ns_per_frame) {
    SDL_DelayNS(ns_per_frame - frame_time);
  }
};
