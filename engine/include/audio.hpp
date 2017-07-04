#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2basics.hpp"
#include "component.hpp"
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
      int audio_repeat;
      int audio_chanel;
      bool playing;

      Mix_Music *audio_music;
      Mix_Chunk *audio_chunk;


    public:
      Audio(
        std::string path,
        AudioType m_type = MUSIC,
        int repeat = 0,
        int chanel = -1)
        :audio_path(path),
        m_audio_type(m_type),
        audio_repeat(repeat),
        audio_chanel(chanel),
        audio_music(NULL),
        audio_chunk(NULL) {}

    ~Audio(){}

    bool load();
    void free();
    void set_repetitions(int repeat);
    void play_chunk();
    void play_music();
    void pause_music();
  };
}

#endif
