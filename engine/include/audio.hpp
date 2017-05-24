#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>

namespace engine{

    class Audio: public Component{

    public:
    //private:
        enum class audio_type {music, chunk};
        std::string audio_path;
        audio_type m_audio_type;
        int audio_repeat;
        int audio_chanel;
        bool playing;

        Mix_Music *audio_music;
        Mix_Chunk *audio_chunk;


        Audio(std::string path, audio_type m_type = audio_type::music, int repeat = 0, int chanel = -1)
                 : audio_path(path), m_audio_type(m_type), audio_repeat(repeat), audio_chanel(chanel), audio_music(NULL), audio_chunk(NULL) {}

        ~Audio(){}

        bool load();
        void free();
        void draw(int x, int y);
        void play_chunk();
        void play_music();
        void pause_music();


    };

}

#endif