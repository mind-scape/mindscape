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
#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;

/**
 * @brief Load the animation and its duration.
 *
 *	This method was implemented to load the animation time based on the duration
 * of animation and total of sprites that the animation has.
 *
 * @return The return is true if the animation was successfully created.
 */
bool Animation::load(){
		time_of_sprite =
		 (int) std::ceil(double(duration_of_animation) / double(total_sprites));

		aux_time = 0;

		Image::load();

		if (in_loop) {
				time->init_timer();
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
void Animation::activate(){
		Component::activate();

		if (!in_loop) {
				time->init_timer();
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
void Animation::draw(int x, int y){
		is_finished = false;
		playing_duration_of_animation += time->get_elapsed_time() - aux_time;
		aux_time = time->get_elapsed_time();

		if (playing_duration_of_animation >= duration_of_animation) {
				is_finished = true;

				if (in_loop) {
						playing_duration_of_animation =
						 playing_duration_of_animation - duration_of_animation;
				}

				else {
						if (is_a_final_animation) {
								deactivate();
								game_object->deactivate();
						}

						else {
								playing_duration_of_animation = duration_of_animation;
						}
				}
		}

		if (time_of_sprite == 0.0) {
				time_of_sprite = 1.0;
		}


		actual_sprite =
		 (playing_duration_of_animation / time_of_sprite) + first_sprite;
		actual_line = 0;
		actual_column = abs(actual_sprite % sprite_columns);
		coordinatesOnTexture.first =
		 sprites_order[actual_column] * dimensionOnTexture.first;
		coordinatesOnTexture.second = actual_line * dimensionOnTexture.second;

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
		if (direction == "LEFT") {
				int reverse_index = total_sprites - 1;

				for (int i = 0; i < total_sprites; ++i) {
						sprites_order[i] = reverse_index;
						reverse_index--;
				}
		}

		else if (direction == "RIGHT") {
				for (int j = 0; j < total_sprites; ++j) {
						sprites_order[j] = j;
				}
		}
}

/**
 * @brief Creates and set a new game object.
 *
 * @param obj The object that will be created.
 * @return void.
 */
void Animation::set_game_object(GameObject *obj) {
		game_object = obj;
}
