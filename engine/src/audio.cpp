/**
 * @file audio.cpp
 * @brief Purpose: Contains methods to load, free, play and draw audio.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/audio.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace engine;

Audio::Audio(
    std::string p_name,
    std::string path,
    AudioType m_type,
    int repeat,
    int chanel)

    :audio_path(path),
    m_audio_type(m_type),
    audio_repeat(repeat),
    audio_chanel(chanel),
    audio_music(NULL),
    audio_chunk(NULL),
    Component(p_name, std::make_pair(0, 0), true, 1) {}

/**
 * @brief This method load the audio.
 *
 * It is important to load and activate the audio, music or chunk, at the game.
 * True to load is OK and false its not OK.
 *
 * @return true or false based in its situation.
 */
bool Audio::load() {
    timer->init();

    if (m_audio_type == MUSIC) {
        audio_music = Mix_LoadMUS(audio_path.c_str());

        if (!audio_music) {
            printf("\nAudio error %s\n", Mix_GetError());
            exit(1);

            return false;
        }
    }
    else if (m_audio_type == CHUNK) {
        audio_chunk = Mix_LoadWAV(audio_path.c_str());

        if (!audio_chunk) {
            printf("\nAudio error %s\n", Mix_GetError());
            exit(1);

            return false;
        }
    }
    else {
        printf("\nError loading the audio in this path: %s\n",
                audio_path.c_str());

        return false;
    }
    activate();

    return true;
}

/**
 * @brief Stop the audio of the game.
 *
 * It is important to free audio, chunk and free memory, when program was closed.
 *
 * @return void.
 */
void Audio::free() {
    Mix_FreeMusic(audio_music);
    Mix_FreeChunk(audio_chunk);

    audio_music = NULL;
    audio_chunk = NULL;
}

/**
 * @brief This method play effects.
 *
 * It is important to play a effect based in the time and in the scene wheres player is.
 *
 * @return void.
 */
void Audio::play_effect() {
    time += timer->time_elapsed() - aux_time;
    aux_time = timer->time_elapsed();

    if (audio_chunk != NULL) {
        if (time >= effect_duration) {
            playing = false;
            time = 0;
        }

        if (!playing) {
            time = 0;
            playing = true;

            Mix_VolumeChunk(audio_chunk, volume);
            Mix_PlayChannel(audio_chanel, audio_chunk, audio_repeat);
        }
    }
}

void Audio::draw(int x, int y) {
  // if(m_audio_type == MUSIC){
  //   is_active();
  //   if( Mix_PlayingMusic() == 0 )
  //     {
  //       //Play the music
  //       Mix_PlayMusic(audio_music, -1 );
  //     }
  //     if(Mix_PlayingMusic() == 1){
  //       Mix_ResumeMusic();
  //     }
  //   }
}

/**
 * @brief This method play music type.
 *
 * It is important to play music based in the theme and to ambientize the player at the game.
 * That is a validation to know if resume or play the music.
 *
 * @return void.
 */
void Audio::play_music_type() {
    if (audio_music != NULL) {
        is_active();
        if (Mix_PlayingMusic() == 0) {
            //Play the music
            Mix_PlayMusic(audio_music, 0 );
        }

        if (Mix_PlayingMusic() == 1) {
            Mix_ResumeMusic();
        }
    }
}

/**
 * @brief This method pause the music of the game.
 *
 * It is important to pause a music when the player think it is necessary.
 *
 * @return void.
 */
void Audio::pause_music() {
    if (m_audio_type == MUSIC && Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

/**
 * @brief This method set the quantity of repetitions of the music.
 *
 * That is a condition to set the repeat.
 *
 * @param integer to know how many times is to repeat the music.
 * @return void.
 */
void Audio::set_repetitions(int repeat) {
    if (audio_music != NULL) {
        audio_repeat = repeat;
        //load();
    }
}

/**
 * @brief This method set the duration of the effect.
 *
 * It is important for the effect of the audio to last longer.
 *
 * @param integer to know how the duration of the effect.
 * @return void.
 */
void Audio::set_duration(float duration) {
    effect_duration = duration * 1000;
}

/**
 * @brief This method stop the effect.
 *
 * It is important to aplly this method to stop the effect after finish the duration/action.
 *
 * @return void.
 */
void Audio::stop_effect() {
    if (audio_chunk != NULL) {
        Mix_VolumeChunk(audio_chunk, 0);
    }
}

/**
 * @brief This method set the volume of the effect.
 *
 * It is important to dont pass the limit of the volume.
 * That is a condition to validate the limit.
 *
 * @param integer to identify the nivel of the effect volume.
 * @return void.
 */
void Audio::set_effect_volume(int _volume) {
    if (_volume > -1 && volume < 129) {
        volume = _volume;
    }
    else {
        printf("\nThe volume must be between 0 and 128");
    }
}

/**
 * @brief This method set the volume of the music.
 *
 * It is important to dont pass the limit of the volume.
 * That is a validate to increase and to decrease volume of the music.
 *
 * @param integer to identify the nivel of the music volume.
 * @return void.
 */
void Audio::set_music_volume(int _volume) {
    if (audio_music != NULL) {
        if (_volume > -1 && volume < 129) {
            Mix_VolumeMusic(_volume);
        }
        else {
            printf("\nThe volume must be between 0 and 128");
        }
    }
}
