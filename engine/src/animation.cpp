/**
 * @file animation.cpp
 * @brief Purpose: Contains methods creating game animations.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include <cmath>
#include <include/log.hpp>
#include <assert.h>
#include "../include/animation.hpp"

using namespace engine;

/**
 * @brief Load the animation and its duration.
 *
 *	This method was implemented to load the animation time based on the duration
 * of animation and total of sprites that the animation has.
 *
 * @return The return is true if the animation was successfully created.
 */
bool Animation::load() {
	/* Log */
	INFO("Loading animation " + this->get_name());

	/* Main logic */
	time_of_sprite =
			(int) std::ceil(double(duration_of_animation) / double(total_sprites));
	assert(time_of_sprite > 0);

	aux_time = 0;
	Image::load();

	if(in_loop) {
		/* In case the game is running */
		time->init_timer();
	}
	else {
		/* Do nothing */
	}

	return true;
}

/**
 * @brief Active the animation.
 *
 * This method active the animation into the game.
 *
 * @return void.
 */
void Animation::activate() {
	/* Log */
	INFO("Activating " + this->get_name());

	/* Main logic */
	Component::activate();

	if(!in_loop) {
		/* In case the game is not running */
		time->init_timer();
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Draws the animation on the screen based in it duration and type.
 *
 * The method draws the animation based in it time that it started and differs
 * the type of the animation that should will be showed.
 *
 * @param x X axis that animation will be loaded.
 * @param y Y axis that animation will be loaded.
 * @return void.
 */
void Animation::draw(int x, int y) {
	/* Main logic */
	is_finished = false;
	playing_duration_of_animation += time->get_elapsed_time() - aux_time;
	aux_time = time->get_elapsed_time();

	if(playing_duration_of_animation >= duration_of_animation) {
		/* Animations is running */
		is_finished = true;

		if(in_loop) {
			/*  Is running animation*/
			playing_duration_of_animation =
					playing_duration_of_animation - duration_of_animation;
		}
		else {
			/* Animation has end */
			if(is_a_final_animation) {
				/* Final frame of animation */
				game_object->deactivate();
			}
			else {
				/* Has blocks to run animation */
				playing_duration_of_animation = duration_of_animation;
			}
		}
	}
	else {
		/* Do nothing */
	}

	if(time_of_sprite == 0.0) {
		time_of_sprite = static_cast<int>(1.0);
	}
	else {
		/* Do nothing */
	}


	/* Set the animation and sprite bounds and blocks */
	actual_sprite =
			(playing_duration_of_animation / time_of_sprite) + first_sprite;
	actual_line = 0;
	actual_column = abs(actual_sprite % sprite_columns);
	coordinatesOnTexture.first =
			sprites_order[actual_column] * dimensionOnTexture.first;
	coordinatesOnTexture.second = actual_line * dimensionOnTexture.second;

	/* Show image on screen */
	Image::draw(x, y);
}

/**
 * @brief Set the sprites order based in its direction.
 *
 * Depending on the direction of the animation, the sprites should be loaded differently
 *
 * @param total_sprites Quantity of sprites that will be loaded.
 * @param direction Direction of sprites to know the order
 * @return void.
 */
void Animation::set_sprites_order(int total_sprites, std::string direction) {
	/* Log */
	INFO("Setting sprites order to " + direction + " in " + this->get_name());

	/* Parameters checking */
	assert(!direction.empty());

	/* Main logic */
	if(total_sprites <= 0) {
		ERROR("Number of sprites can't be less than zero");
	}

	if(direction == "LEFT") {
		/* Sprite is shown left to right */
		int reverse_index = 0;
		reverse_index = total_sprites - 1;

		for(int i = 0; i < total_sprites; ++i) {
			sprites_order[i] = reverse_index;
			reverse_index--;
		}
	}
	else if(direction == "RIGHT") {
		/* Sprite is shown right to left, reversed */
		for(int j = 0; j < total_sprites; ++j) {
			sprites_order[j] = j;
		}
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Creates and set a new game object.
 *
 * @param obj The object that will be created.
 * @return void.
 */
void Animation::set_game_object(GameObject *obj) {
	/* Log */
	INFO("Setting " + obj->name + " as owner for " + this->get_name());

	/* Parameters checking */
	assert(obj);

	/* Main logic */
	game_object = obj;
}
