/**
 * @file star.hpp
 * @brief Purpose: Contains the methods for Star class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "star.hpp"
#include "fox.hpp"

using namespace mindscape;

/**
 * @brief Constructor for Star class
 *
 * Initialize everuthing needed for running properly.
 *
 * @param name GameObject name.
 * @param position Pair of integers representing x and y position.
 * @param priority Integer representing priority on rendering.
 *
 * @return void
 */
Star::Star(
		std::string name,
		std::pair<int, int> position,
		int priority)
		:engine::GameObject(
		name,
		position,
		priority,
		{
				{engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
				{engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
		}
){
	initialize_hitboxes();
	initialize_animations();
	initialize_audio_effects();
};

/**
 * @brief Initialize hitboxes
 *
 * @return void
 */
void Star::initialize_hitboxes() {
	engine::Game& game = engine::Game::get_instance();
	engine::Hitbox* star_hitbox = new engine::Hitbox(
			"star_hitbox",
			this->get_position(),
			std::make_pair(0, 0),
			std::make_pair(40, 40),
			game.get_renderer()
	);
	add_component(star_hitbox);
}

/**
 * @brief Initialize audio effects
 *
 * @return void
 */
void Star::initialize_audio_effects() {
	engine::Audio * got_me_audio = new engine::Audio(
			"got_me",
			"../assets/audios/effects_songs/pegando_estrela.wav",
			engine::Audio::CHUNK);
	got_me_audio->set_duration(0.5);
	add_component(got_me_audio);
}

/**
 * @brief Initialize animations
 *
 * @return void
 */
void Star::initialize_animations() {
	engine::Animation* star = create_animation(
			"../assets/images/sprites/items/star/star.png",
			1, 6, 0.9, "LEFT"
	);

	engine::Animation* star_fading = create_animation(
			"../assets/images/sprites/items/star/star_caught.png",
			1, 5, 0.5, "LEFT"
	);

	star_fading->is_a_final_animation = true;
	star_fading->in_loop = false;

	add_animation("star", star);
	add_animation("star_fading", star_fading);
	star->activate();
	set_actual_animation(star);
}

/**
 * @brief Create an animation for the object
 *
 * Creates and return an animation for this specific object
 *
 * @param path File path to the sprite sheet.
 * @param sprite_lines Number of lines in the sprite sheet.
 * @param sprite_columns Number of columns in the sprite sheet.
 * @param duration Time duration of the animation.
 * @param direction Direction of the animation (left or right).
 *
 * @return The animation created.
 */
engine::Animation* Star::create_animation(std::string path,
										  int sprite_lines,
										  int sprite_columns,
										  double duration,
										  std::string direction) {

	engine::Game& game = engine::Game::get_instance();
	engine::Animation* animation = new engine::Animation(
			game.get_renderer(),
			path,                 // image path
			false,                // is_active
			std::make_pair(0, 0), // displacement
			1,                    // priority
			sprite_lines,         // sprite_lines
			sprite_columns,       // sprite_columns
			duration,             // duration
			true,                 // in_loop
			direction             // direction
	);

	animation->set_values(
			std::make_pair(40, 40),
			std::make_pair(40, 40),
			std::make_pair(0, 0)
	);

	return animation;
}

/**
 * @brief Event processos
 *
 * This method processes GameEvents received and act according to the expected.
 *
 * @param game_event The event to be processed.
 *
 * @return void
 */
void Star::on_event(GameEvent game_event) {
	std::string event_name = game_event.game_event_name;

	if(event_name == "MOVE_LEFT" &&
			!engine::GameObject::on_limit_of_level) {
		set_position_x(get_position_x() + 10);
	}

	else if(event_name == "MOVE_RIGHT" &&
			!engine::GameObject::on_limit_of_level) {
		set_position_x(get_position_x() - 10);
	}
}

/**
 * @brief Event triggered when collision happens
 *
 * @param other The other game object which hits this one.
 * @param p_my_hitbox The hitbox which collision happened.
 * @param p_other_hitbox The other object hitbox which the collision happened.
 *
 * @return void
 */
void Star::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox,
						engine::Hitbox* p_other_hitbox) {
	//Nothing
}
