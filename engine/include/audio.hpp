#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include "time.hpp"
#include <string>

namespace engine{
  class Audio: public Component{
    public:
      typedef enum {
        MUSIC, CHUNK
      } AudioType;

    private:
      std::string audio_path;
      AudioType m_audio_type;
      int audio_repeat = 0;
      int audio_chanel;
      bool playing = false;
      int volume = 50;

      Time * timer;
      float time=0;
      float aux_time=0;
      float effect_duration=0;

      Mix_Music *audio_music;
      Mix_Chunk *audio_chunk;

      int audio_cont = 0;

    public:
      Audio(
        std::string p_name,
        std::string path,
        AudioType m_type,
        int repeat = 0,
        int chanel = -1);

      ~Audio(){}

      bool load();
      void free();
      void set_repetitions(int repeat);
      void set_duration(float duration);
      void play_effect();
      void play_music_type();
      void draw(int x, int y);
      void pause_music();
      void stop_effect();
      void set_effect_volume(int _volume);
      void set_music_volume(int _volume);
  };
}

#endif
