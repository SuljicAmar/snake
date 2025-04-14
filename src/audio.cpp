#include "../include/audio.h"

Audio::Audio() {};

void Audio::close() {
  Mix_FreeChunk(eat_sound_effect);
  eat_sound_effect = nullptr;

  Mix_FreeChunk(game_over_sound_effect);
  game_over_sound_effect = nullptr;

  Mix_FreeMusic(music);
  music = nullptr;

  Mix_CloseAudio();

  SDL_CloseAudioDevice(audio_device_id);
  audio_device_id = 0;
};

void Audio::create_audio_objects() {
  audio_spec = {.format = SDL_AUDIO_F32, .channels = 2, .freq = 44100};
  audio_device_id =
      SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio_spec);
  if (audio_device_id != 0) {
    Mix_OpenAudio(audio_device_id, nullptr);
  }
};

void Audio::set_eat_sound(const char *path) {
  eat_sound_effect = Mix_LoadWAV(path);
};

void Audio::play_eat_sound_effect() {
  Mix_PlayChannel(1, eat_sound_effect, 0);
};

void Audio::set_music(const char *path) {
  music = Mix_LoadMUS(path);
  Mix_VolumeMusic(64);
};

void Audio::play_music() { Mix_PlayMusic(music, -1); };

void Audio::pause_music() {
  if (Mix_PausedMusic() == 0) {
    Mix_PauseMusic();
  };
};

void Audio::unpause_music() {
  if (Mix_PausedMusic() == 1) {
    Mix_ResumeMusic();
  };
};

void Audio::set_game_over_sound(const char *path) {
  game_over_sound_effect = Mix_LoadWAV(path);
};

void Audio::play_game_over_sound() {
  Mix_PlayChannel(1, game_over_sound_effect, 0);
};
