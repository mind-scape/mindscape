/**
 * @file music_player.cpp
 * @brief Purpose: Contains the methods for music_player class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/music_player.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/log.hpp"
#include <stdlib.h>

using namespace mindscape;

bool passed = false;

/**
 * @brief Updates the state of the music player
 *
 * Responsible for managing which music will play and when.
 *
 * @return void
 */
void MusicPlayer::update_state() {
    if (get_audio_by_name("music_menu")) {
  	    /* Search and play the song of main_menu */
  	    play_song("music_menu");
  	}
  	else if (get_audio_by_name("intro_level_1")) {
        /* search and play the songs of level_1 */
        time += timer->time_elapsed() - time_aux;
        time_aux = timer->time_elapsed();

        /* Set the music volumn of the intro song in 30. */
        set_music_volume("intro_level_1", 30);

        /* Set the music volumn of the loop level 1 in 30. */
        set_music_volume("loop_level_1", 30);

        if (time < 25850) {
            /* Play intro level 1 song. */
            play_song("intro_level_1");
        }
        else if (sub_position_x < 13700) {
            /* Frees the last song and starts the loop level 1 song. */

            if (passed) {
                while(!Mix_FadeOutMusic(500) && Mix_PlayingMusic()) {
                    SDL_Delay(100);
                }
                
                passed = false;
            }
            else {
                free_music("intro_level_1");
            }

            play_song("loop_level_1");
        }
        else if (sub_position_x > 14000) {
            /* Frees the last song and starts the loop palhaço song. */

            if (!passed) {
                while(!Mix_FadeOutMusic(1000) && Mix_PlayingMusic()) {
                    SDL_Delay(100);
                }
            }

            play_song("loop_palhaco");

            passed = true;
        }
        else {
            INFO("The sub position is on limit of introduction and clown songs.");
        }
  	}
  	else if (get_audio_by_name("loop_level_2")) {
  	    /* search and play the songs of level_2 */
  		set_music_volume("loop_level_2", 30);
  		play_song("loop_level_2");
  	}
    else {
        /* Close the game if the song is not found. */
        ERROR("Song was not found.");
    }
}

/**
 * @brief Receives and process game events
 *
 * Responsible for receiving and processing expected events.
 *
 * @param game_event Tha event to be received
 *
 * @return void
 */
void MusicPlayer::on_event(GameEvent game_event) {
    std::string event_name = "";
    event_name = game_event.game_event_name;

    if (event_name == "MOVE_LEFT") {
        /* On left movement */
        if (sub_position_x > 0) {
            /* If not on the corner of the screen */
            sub_position_x -= 10; /* Pushes to the left */
        }
        else {
            /* If on the corner of the screen */
            sub_position_x = 0; /* Keep on the corner */
        }
    }
    else if (event_name == "MOVE_RIGHT") {
        /* On right movement */
        sub_position_x += 10;
    }
    else {
        /* The Event name is not found. */
    }
}
