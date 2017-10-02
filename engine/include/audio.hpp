/**
 * @file audio.hpp
 * @brief Purpose: Contains attributes and methods for audio class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include "time.hpp"
#include <string>

namespace engine {

    /**
     * @brief A audio class.
     *
     * This class is a model that contains all specifications of the audio.
     * The audio it is divided in music and chunk. That is used in different situations.
     */
    class Audio: public Component {
        public:
            typedef enum {
                MUSIC, CHUNK

        } AudioType;

        private:
            std::string audio_path; /**< String. path to folder where the audio is. */
            AudioType m_audio_type; /**< Object AudioType. type of audio, it can be effect or music. */
            int audio_repeat = 0; /**< Integer. Store the number of repetitions of a song. */
            int audio_chanel; /**< Integer. Store witch chanel the audio will be played. */
            bool playing = false; /**< Boolean. Store the current status of the song. */
            int volume = 50; /**< Integer. Store the volume, it goes to one scale of 0 to 100. */

            Time * timer; /**< Object Time. Used to cronometer the time of songs. */
            float time=0; /**< Float. Set current time of component song. */
            float aux_time=0; /**< Float. Auxiliary time to store que last time when time was reset. */
            float effect_duration=0; /**< Float. Duration of component song. */

            Mix_Music *audio_music; /**< Object Mix_Music. SDL object to randle music. 
                                    It contains functions to play stop and delete musics...
                                    Music is an audio with long duration. */
            Mix_Chunk *audio_chunk; /**< Object Mix_Chunk. SDL object to randle sound effects. 
                                    It contains functions to play stop and delete effects...
                                    Sound effects is an audio with short duration. */

            int audio_cont = 0; /**< Integer. Store the numberm of audio the game contains. */

        public:
            Audio(
                std::string p_name,
                std::string path,
                AudioType m_type,
                int repeat = 0,
                int chanel = -1);

            ~Audio() {}

            bool load();
            void free();

            void play_effect();
            void play_music_type();
            void draw(int x, int y);

            void pause_music();
            void stop_effect();

            void set_repetitions(int repeat);
            void set_duration(float duration);
            void set_effect_volume(int _volume);
            void set_music_volume(int _volume);

    };

}

#endif
