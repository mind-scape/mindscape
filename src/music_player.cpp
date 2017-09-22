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
#include <stdlib.h>

using namespace mindscape;

/**
 * @brief Updates the state of the music player
 *
 * Responsible for managing which music will play and when.
 *
 * @return void
 */
void MusicPlayer::update_state() {
	//Search and play the song of main_menu
	if (get_audio_by_name("music_menu")) {
		play_song("music_menu");
		//search and play the songs of level_1
	} else if (get_audio_by_name("intro_level_1")) {
		time += timer->time_elapsed() - time_aux;
		time_aux = timer->time_elapsed();

		set_music_volume("intro_level_1", 30);
		set_music_volume("loop_level_1", 30);

		if (time < 25850) {
			play_song("intro_level_1");
		} else if (sub_position_x < 14000) {
			free_music("intro_level_1");
			play_song("loop_level_1");
		} else if (sub_position_x > 14000) {
			free_music("loop_level_1");
			play_song("loop_palhaco");
		}

		//search and play the songs of level_2
	} else if (get_audio_by_name("loop_level_2")) {
		set_music_volume("loop_level_2", 30);
		play_song("loop_level_2");

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
	std::string event_name = game_event.game_event_name;

	if (event_name == "MOVE_LEFT") {
		if (sub_position_x > 0) {
			sub_position_x -= 10;
		} else {
			sub_position_x = 0;
		}
	} else if (event_name == "MOVE_RIGHT") {
		sub_position_x += 10;
	}

}
