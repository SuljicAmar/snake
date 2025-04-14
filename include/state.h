#ifndef STATE_H
#define STATE_H

enum Activity { null, menu, playing, game_over };

struct State {
  bool init;
  bool running;
  Activity activity;
};

#endif
