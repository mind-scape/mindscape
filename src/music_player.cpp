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
#include <assert.h>

using namespace mindscape;

/**
 * @brief Updates the state of the music player
 *
 * Responsible for managing which music will play and when.
 *
 * @return void
 */
void MusicPlayer::update_state() {

    const int volumn_music = 30;

    if (get_audio_by_name("music_menu")) {
  	    /* Search and play the song of main_menu */
  	    play_song("music_menu");
  	}
  	else if (get_audio_by_name("intro_level_1")) {
        /* search and play the songs of level_1 */
        time += timer->time_elapsed() - time_aux;
        time_aux = timer->time_elapsed();

        /* Set the music volumn of the intro song in 30. */
        set_music_volume("intro_level_1", volumn_music);

        /* Set the music volumn of the loop level 1 in 30. */
        set_music_volume("loop_level_1", volumn_music);

        const int fade_time = 500;
        const int delay = 100;

        const int initial_time = 25850;
        const int limit_in_clown_field = 13500;
        const int limit_out_clown_field = 13500;

        if (time < initial_time) {
            /* Play intro level 1 song. */
            play_song("intro_level_1");
        }
        else if (sub_position_x < limit_out_clown_field) {
            /* Frees the last song and starts the loop level 1 song. */

            /* Verifies if the girl passed of the Clown battlefield. */
            if (passed) {
                /* Stops the clown music with a fade out. */
                stop_song("loop_palhaco");

                /* Turn boolean false representing that the girl is out of
                the clown battlefield. */
                passed = false;
            }
            else {
                /* Frees the intro music. */
                free_music("intro_level_1");
            }

            /* Plays the level 1 song with a fade in. */
            play_song("loop_level_1");
        }
        else if (sub_position_x > limit_in_clown_field) {
            /* Frees the last song and starts the loop palhaço song. */

            /* Verifies if the girl not passed yet of the Clown battlefield. */
            if (!passed) {
                /* Stops the level 1 song with a fade out. */
                stop_song("loop_level_1");
            }
            else {
                /* The girl just passed to the Clown battlefield. */
            }

            /* Plays the clown song with a fade in. */
            play_song("loop_palhaco");

            /* Turn boolean true representing that the girl has passed to the
            clown battlefield. */
            passed = true;
        }
        else {
            INFO("The sub position is on limit of introduction and clown songs.");
        }
  	}
  	else if (get_audio_by_name("loop_level_2")) {
  	    /* search and play the songs of level_2 */
  		set_music_volume("loop_level_2", volumn_music);
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
 * @return void.
 */
void MusicPlayer::on_event(GameEvent game_event) {
    std::string event_name = "";
    event_name = game_event.game_event_name;

    assert(event_name != "");

    const int minimal_position = 0;
    const int displacement = 10;

    if (event_name == "MOVE_LEFT") {
        /* On left movement */
        if (sub_position_x > minimal_position) {
            /* If not on the corner of the screen */
            sub_position_x -= displacement; /* Pushes to the left */
        }
        else {
            /* If on the corner of the screen */
            sub_position_x = minimal_position; /* Keep on the corner */
        }
    }
    else if (event_name == "MOVE_RIGHT") {
        /* On right movement */
        sub_position_x += displacement;
    }
    else {
        /* The Event name is not found. */
    }
}
