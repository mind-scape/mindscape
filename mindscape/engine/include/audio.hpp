#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>

namespace engine{

    class Audio: public Component{

    public:
    //private:

        std::string audio_path;
        std::string audio_type;
        int audio_repeat;
        int audio_chanel;

        Mix_Music *audio_music;
        Mix_Chunk *audio_chunk;


        Audio(std::string path, std::string type, int repeat = 0, int chanel = -1)
                 : audio_path(path), audio_type(type), audio_repeat(repeat), audio_chanel(chanel), audio_music(NULL), audio_chunk(NULL) {}

        ~Audio(){}

        bool load();
        void free();
        void draw(int x, int y);

    };

}

#endif