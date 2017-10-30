/**
 * @file arm.cpp
 * @brief Purpose: Contains methods to arm class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/arm.hpp"
#include "../include/platform.hpp"
#include "../engine/include/log.hpp"

using namespace mindscape;

/**
 * @brief Arm constructor
 *
 * @param name Name for the given object
 * @param position Pair of integers for its position
 * @param priority Priority for rendering it on the screen
 *
 * @return void
 */
Arm::Arm(
		std::string name,
		std::pair<int, int> position,
		int priority
)
		: Enemy(
		name,
		position,
		priority,
		100
) {
	initialize_state_map();
	initialize_hitboxes();
	initialize_animations();

	translations = {
			{engine::KeyboardEvent::LEFT,  "MOVE_LEFT"},
			{engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"},
	};
};

/**
 * @brief Initialize all the Arm's animations
 *
 * @return void
 */
void Arm::initialize_animations() {
	engine::Animation *right_arm = create_animation(
			"../assets/images/sprites/enemies/arm/right_arm.png",
			1, 4, 3.0, "RIGHT"
	);

	right_arm->set_values(
			std::make_pair(405, 542),
			std::make_pair(405, 542),
			std::make_pair(0, 0)
	);

	add_animation("right_arm", right_arm);
	right_arm->activate();

	engine::Animation *left_arm = create_animation(
			"../assets/images/sprites/enemies/arm/left_arm.png",
			1, 4, 3.0, "LEFT"
	);

	left_arm->set_values(
			std::make_pair(405, 542),
			std::make_pair(405, 542),
			std::make_pair(0, 0)
	);

	add_animation("left_arm", left_arm);
	set_actual_animation(right_arm);
}

/**
 * @brief Creates the animations
 *
 * Creates new animations for this object
 *
 * @param image_path Path for the image file
 * @param sprite_lines Number of lines in the spritesheet
 * @param sprite_columns Number of columns in the spritesheet
 * @param duration Duration of the animation
 * @param direction Direction (right or left) of the animation
 *
 * @return The animation created
 */
engine::Animation *Arm::create_animation(
		std::string image_path,
		int sprite_lines,
		int sprite_columns,
		double duration,
		std::string direction) {
	engine::Game &game = engine::Game::get_instance();

	engine::Animation *animation = new engine::Animation(
			game.get_renderer(),
			image_path,
			false,
			std::make_pair(0, 0),
			1,
			sprite_lines,
			sprite_columns,
			duration,
			true,
			direction
	);

	animation->set_values(
			std::make_pair(320, 320),
			std::make_pair(320, 320),
			std::make_pair(0, 0)
	);

	return animation;
}

/**
 * @brief Initialize object as a physicable object
 *
 * Using this method makes the object vulnerable to forces as gravity and collisions
 *
 * @return void
 */
void Arm::initialize_as_physicable() {
	engine::Physics *physics = engine::Physics::get_instance();
	physics->add_physicable(this);
	collidable = true;
}

/**
 * @brief Initialize hitboxes
 *
 * Initialize all the hitboxes of the object
 *
 * @return void
 */
void Arm::initialize_hitboxes() {
	engine::Game &game = engine::Game::get_instance();

	engine::Hitbox *arm_hitbox = new engine::Hitbox(
			"arm_hitbox",
			this->get_position(),
			std::make_pair(10, 45),
			std::make_pair(60, 8),
			game.get_renderer()
	);

	arm_hitbox->initialize();
	add_component(arm_hitbox);
}

/**
 * @brief Event for collisions
 *
 * This method is triggered everytime a collision happens
 *
 * @param other The other game object which collided
 * @param p_my_hitbox This object hitbox that received the collision
 * @param p_other_hitbox The other object hitbox which provided the collision
 */
void Arm::on_collision(engine::GameObject *other, engine::Hitbox *p_my_hitbox,
					   engine::Hitbox *p_other_hitbox) {
	Platform *platform = dynamic_cast<Platform *>(other);
	engine::Hitbox *my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox *other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if (get_speed_y() >= 0 && platform && my_hitbox->get_name() == "arm_hitbox") {
		/* If arm is not falling */

		set_speed_y(0.0);
		set_position_y(other_hitbox->get_coordinates().second - 30);

		states.set_state("Y_STATE", "ON_GROUND");

		engine::Game::get_instance()
		 .get_actual_scene()->deactivate_game_object(name);

		free();
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Initialize the object's state map
 *
 * @return void
 */
void Arm::initialize_state_map() {
	states.set_state("ACTION_STATE", "NORMAL");
	states.set_state("Y_STATE", "ON_GROUND");
}

/**
 * @brief Register an event
 *
 * This method register a GameEvent to the object
 *
 * @param game_event The event to be called
 *
 * @return void
 */
void Arm::on_event(GameEvent game_event) {
	std::string event_name = game_event.game_event_name;

	if (event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {

	/* If arm is moving left */
		set_position_x(get_position_x() + 10); // Moves position 10 pixels to the right
	}
	else if (event_name == "MOVE_RIGHT" &&
			!engine::GameObject::on_limit_of_level) {
	/* If arm is moving right */
		set_position_x(get_position_x() - 10); // Moves position 10 pixels to the left

	}
	else {
		INFO("Arm are not moving");
	}
}
