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
#include "../include/log.hpp"

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
    /* Separate MUSIC from  CHUNK */
        audio_music = Mix_LoadMUS(audio_path.c_str());

        if (!audio_music) {
        /* Verifys if music is not an null object */
            WARN(("Audio error %s", Mix_GetError()));
            exit(1);

            return false;
        }

        else {
            DEBUG("Music successfully loaded");
        }
    }

    else if (m_audio_type == CHUNK) {
    /* Separate CHUNK from  MUSIC*/
        audio_chunk = Mix_LoadWAV(audio_path.c_str());

        if (!audio_chunk) {
        /* Verifys if chuck is not an null object */
            WARN(("Audio error %s", Mix_GetError()));
            exit(1);

            return false;
        }
        else {
            DEBUG("Chunk successfully loaded");
        }
    }

    else {
    /* In case of there is no audio type called MUSIC or CHUCK it will be dispared and hadle the error */
        WARN(("Error loading the audio in this path: %s",
        audio_path.c_str()));

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
    /* SDL function to delete music and chunk */
    Mix_FreeMusic(audio_music);
    Mix_FreeChunk(audio_chunk);

    /* Poiting music and chuck to NULL */
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
    /* Stores the time of song */
    time += timer->time_elapsed() - aux_time;
    aux_time = timer->time_elapsed();

    if (audio_chunk != NULL) {
    /* Validates audio chuck */
        if (time >= effect_duration) {
        /* Effect will only be stoped when time is bigger than the effect duration */
            playing = false;
            time = 0;
        }

        else {
            /*Do nothing*/
        }

        if (!playing) {
        /* Plays the sound effect */
            time = 0;
            playing = true;

            /* Apply volume and play with random chanel */
            Mix_VolumeChunk(audio_chunk, volume);
            Mix_PlayChannel(audio_chanel, audio_chunk, audio_repeat);
        }

        else {
            /*Do nothing*/
        }
    }

    else {
        /*Do nothing*/
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
    /* Validates audio chuck */
        is_active();

        if (Mix_PlayingMusic() == 0) {
        /* Verification to know if will play or resume music */
            Mix_PlayMusic(audio_music, 0 );
            DEBUG("Music is being played");
        }

        else if (Mix_PlayingMusic() == 1) {
        /* Verification to know if will play or resume music */
            Mix_ResumeMusic();
            DEBUG("Music is being resumed");
        }

        else {
            /*Do nothing*/
        }
    }

    else {
        /*Do nothing*/
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
    /* Case is a music and is playing it, it can be paused here */
        Mix_PauseMusic();
        DEBUG("Music is being paused");
    }

    else {
        /*Do nothing*/
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
    /* Validates if music is not a null object */
        audio_repeat = repeat;
        //load();
    }

    else {
        /*Do nothing*/
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
    effect_duration = 0;
    effect_duration = duration * 1000;
    DEBUG(("Function: %s - effect_duration: %f", __func__, effect_duration));
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
    /* Validates if chuck is not a null object */
        Mix_VolumeChunk(audio_chunk, 0);
        DEBUG("Audio effect stopped");
    }

    else {
        /*Do nothing*/
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
    /* Limits volume to be in a rate of 0 to 128 */
        volume = _volume;
        DEBUG(("Sound effect volume set to %d", _volume));
    }

    else {
        WARN("The volume must be between 0 and 128");
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
        /* Limits volume to be in a rate of 0 to 128 */
            Mix_VolumeMusic(_volume);
            DEBUG(("Music volume set to %d", _volume));
        }

        else {
            WARN("The volume must be between 0 and 128");
        }
    }
}
