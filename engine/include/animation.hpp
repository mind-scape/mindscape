/**
 * @file animation.hpp
 * @brief Purpose: Contains classes to animation methods' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <map>
#include "game_object.hpp"
#include "image.hpp"
#include "time.hpp"
#include "timer.hpp"

namespace engine{

	class GameObject;

	/**
	 * @brief A Animation class.
	 *
	 * Creates and describe a new animation into a game.
	 */
	class Animation : public Image{

		private:
			/* Construtor de image */
			std::pair<int, int> displacement; /**< Pair. Position to animation object. */
			int render_priority; /**< Integer. Priority of layers to render the animations. */
			GameObject* game_object; /**< Object GameObject. Reference to the father object. */

			/* Atributos of animatiion */
			int first_sprite; /**< Integer. Stores which block starts the sprite. */
			int final_sprite; /**< Integer. Stores which block ends the sprite. */
			int time_of_sprite; /**< Integer. Stores the time to change betwen sprite. */
			int playing_duration_of_animation = 0; /**< Integer. Stores the time since the start of animatin. */

			/* Atributes for timer */
			Timer * time; /**< Object Timer. Stores function to handle time. */
			int aux_time; /**< Integer. Variable to store past times. */
			
			/* Atributes of sprite */
			std::vector<std::pair<int,int> > sprites_sizes; /**< Vector of Integers. Store the size of sprite. */
			bool use_default_image_size = true; /**< Boolean. Store the size of sprite. */
			std::string direction; /**< String. Direction of objects. */
			std::map<int,int> sprites_order; /**< Map of Integers. Orders of sprites to been changed. */

		public:

			void set_sprites_order(int, std::string);
			Animation(SDL_Renderer* p_renderer,
			std::string path,
			bool is_active,
			std::pair<int, int> displacement,
			int priority,
			unsigned int p_sprite_lines=1,
			unsigned int p_sprite_columns=1,
			double p_duration_of_animation =1.0,
			bool p_in_loop = true,
			std::string p_direction="RIGHT",
			bool p_use_default_image_size = true)

			:Image(
				p_renderer,
				path,
				is_active,
				displacement,
				priority
			),
			sprite_lines(p_sprite_lines),
			sprite_columns(p_sprite_columns),
			duration_of_animation(p_duration_of_animation*1000),
			in_loop(p_in_loop),
			total_sprites(p_sprite_lines * p_sprite_columns),
			first_sprite(0),
			final_sprite(total_sprites-1),
			actual_sprite(first_sprite),
			is_finished(false),
			use_default_image_size(p_use_default_image_size),
			direction(p_direction) {
			time = new Timer();
			set_sprites_order(total_sprites,direction);
			}

			virtual ~Animation() {
			}

			int actual_line; /**< Integer. Store the actual line on sprite block, this means Y axe. */
			int actual_column; /**< Integer. Store the actual column on sprite block, this means X axe. */
			int actual_sprite; /**< Integer. Store the actual sprite. */
			int total_sprites; /**< Integer. Store the sprites passed. */
			int duration_of_animation; /**< Integer. Store the duration to pass sprites. */
			int sprite_columns; /**< Integer. Size of the sprite on X. */
			int sprite_lines; /**< Integer. Size of the sprite on Y. */
			bool in_loop; /**< Bollean. Shows if sprite is running. */
			bool is_finished; /**< Bollean. Shows if sprite is finished. */
			bool is_a_final_animation = false; /**< Bollean. Shows if sprite is the final animation. */

			bool load();
			bool set_frame_time();
			void set_game_object(GameObject*);
			void draw(int, int);
			void activate();
			void set_sprite_sizes(std::vector<std::pair<int,int> >);
  };
}

#endif
