#ifndef AUDIO_H
#define AUDIO_H

#include <SDL3_mixer/SDL_mixer.h>

class Audio {
public:
  Audio();

  void close();

  void create_audio_objects();

  void set_eat_sound(const char *path);

  void set_music(const char *path);

  void set_game_over_sound(const char *path);

  void play_music();

  void pause_music();

  void unpause_music();

  void play_eat_sound_effect();

  void play_game_over_sound();

private:
  Mix_Music *music{nullptr};
  Mix_Chunk *eat_sound_effect{nullptr};
  Mix_Chunk *game_over_sound_effect{nullptr};
  SDL_AudioSpec audio_spec;
  SDL_AudioDeviceID audio_device_id;
};

#endif
