/**
 * @file arm.cpp
 * @brief Purpose: Contains methods to arm class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include <assert.h>
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
    /* Objects declaration */
	Platform *platform = dynamic_cast<Platform *>(other); /**< Plataform. Plataform of the game */
	engine::Hitbox *my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox); /**< Hitbox. Arm hitbox */
	engine::Hitbox *other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox); /**< Hitbox. Girl hitbox */

	/* Parameters & objects verification */
	assert(p_my_hitbox && p_other_hitbox && other);
	assert(my_hitbox && other_hitbox && platform);

	if (get_speed_y() >= 0 && platform && my_hitbox->get_name() == "arm_hitbox") {
		/* If arm is not falling */

		/* Constants declaration */
		const int movement_arm_axis_y = 30; /**< const int. Movement arm in pixel */
		const float speed_arm = 0.0; /**< const float. Speed arm */

		/* Values set */
		set_speed_y(speed_arm);
		set_position_y(other_hitbox->get_coordinates()
		 .second - movement_arm_axis_y);

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
 * @brief Initialize object as a physicable object
 *
 * Using this method makes the object vulnerable to forces as gravity and collisions
 *
 * @return void
 */
void Arm::initialize_as_physicable() {
	/* Object declaration */
	engine::Physics *physics = engine::Physics::get_instance(); /**< Instance. Instance of the game */

	/* Object verification */
	assert(physics);

	/* State of the physics and hitboxes */
	physics->add_physicable(this);
	collidable = true;
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
	/* Parameters verification */
	assert(!game_event.game_event_name.empty());

	/* Constants and variables declaration */
	std::string event_name = game_event.game_event_name;
	const int movement_arm = 10; /**< const int. Movemet of the arm in pixels */

	if (event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {

		/*
		 * If arm is moving left.
		 * Moves position 10 pixels to the right.
		 */
		set_position_x(get_position_x() + movement_arm);
	}
	else if (event_name == "MOVE_RIGHT" &&
			!engine::GameObject::on_limit_of_level) {
		/*
		 * If arm is moving right.
		 * Moves position 10 pixels to the left.
		 */
		set_position_x(get_position_x() - movement_arm);

	}
	else {
		INFO("Arm are not moving");
	}
}

/**
 * @brief Initialize all the Arm's animations
 *
 * @return void
 */
void Arm::initialize_animations() {
	/* Constants declaration */
	const int default_sprite_line = 1;
	const int default_sprite_column = 4;
	const float default_animation_duration = 3.0;
	const std::pair<int, int> default_dimensions_arm =
	 std::make_pair(405, 542);
 	const std::pair<int, int> coordinates_on_texture_arm =
	 std::make_pair(0, 0);

	/* Instance and values of objects */
	engine::Animation *right_arm = create_animation(
			"../assets/images/sprites/enemies/arm/right_arm.png",
			default_sprite_line, default_sprite_column,
			default_animation_duration, "RIGHT"
	);

	right_arm->set_values(default_dimensions_arm,
						  default_dimensions_arm,
				  		  coordinates_on_texture_arm);

	add_animation("right_arm", right_arm);
	right_arm->activate();

	engine::Animation *left_arm = create_animation(
			"../assets/images/sprites/enemies/arm/left_arm.png",
			default_sprite_line, default_sprite_column,
			default_animation_duration, "LEFT"
	);

	right_arm->set_values(default_dimensions_arm,
						  default_dimensions_arm,
				  		  coordinates_on_texture_arm);

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

	/* Parameters verification */
	assert(!image_path.empty() && !direction.empty());
	assert(sprite_lines >= 0 && sprite_columns >= 0 && duration >= 0.0);

	/* Object declaration */
	engine::Game &game = engine::Game::get_instance();

	/* Object verification */
	assert(&game);

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

	/* Constants declaration */
	const std::pair<int, int> default_dimensions_animation =
	 std::make_pair(320, 320);
	const std::pair<int, int> coordinates_on_texture_animation =
	 std::make_pair(0, 0);

	/* Animation values */
	animation->set_values(default_dimensions_animation,
						  default_dimensions_animation,
						  coordinates_on_texture_animation);

	return animation;
}

/**
 * @brief Initialize hitboxes
 *
 * Initialize all the hitboxes of the object
 *
 * @return void
 */
void Arm::initialize_hitboxes() {
	/* Object declaration */
	engine::Game &game = engine::Game::get_instance();

	/* Object verification */
	assert(&game);

	/* Hitboxe's values */
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
 * @brief Initialize the object's state map
 *
 * @return void
 */
void Arm::initialize_state_map() {
	states.set_state("ACTION_STATE", "NORMAL");
	states.set_state("Y_STATE", "ON_GROUND");
}
