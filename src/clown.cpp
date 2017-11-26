/**
 * @file clown.cpp
 * @biref Purpose: Contains clown's methods and attributes
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */

#include "../include/clown.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/log.hpp"
#include "level_factory.hpp"
#include <stdlib.h>
#include <assert.h>

using namespace mindscape;

/**
 * @brief Initializes Clown boss
 *
 * Constructor responsible for initialize clown in game
 *
 * @param name Object's name
 * @param position  x nd y position
 * @param priority  rendering object priority
 */
Clown::Clown(
		std::string name,
		std::pair<int, int> position,
		int priority)
		: Enemy(
		name,
		position,
		priority,
		100
) {
	/* Initializes all the characteristics for the clown */
	initialize_state_map();
	initialize_foot_hitbox();
	initialize_head_hitbox();
	initialize_attack_hitbox();
	initialize_animation_on_attack();
	initialize_animation_dying();
	initialize_animation_attacking();
	initialize_animation_idle();
	initialize_animation_idle_vunerable();
	initialize_as_physicable();
	initialize_audio_effects();
};

/**
 * @brief Creates clown animations
 *
 * Creates an animation for the clown
 *
 * @param path path to the image which contains the sprite sheet
 * @param sprite_lines number of the lines on the sprite sheet
 * @param sprite_columns number of columns on the sprite sheet
 * @param duration Time duration of the animation
 * @param direction direction of the animation
 *
 *
 * @return animation created
 */
engine::Animation *Clown::create_animation(
		/* Creates and initializes the object of the clown  */
		std::string path,
		int sprite_lines,
		int sprite_columns,
		double duration,
		std::string direction) {
	DEBUG("create_animation")
	engine::Game &game = engine::Game::get_instance();

	engine::Animation *animation = nullptr;
	animation = new engine::Animation(
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
			std::make_pair(320, 320),
			std::make_pair(320, 320),
			std::make_pair(0, 0)
	);

	assert(animation != nullptr);
	DEBUG("create_animation finished")
	return animation;
}

/**
 * @brief Initializes Clown animations
 *
 * Initializes animations on attack of the clown.
 *
 * @return void
 */
void Clown::initialize_animation_on_attack() {

	DEBUG("on_attack_animation")
	/* Initializes the anitmation when the clown is getting a hit */

	engine::Animation *on_attack_animation = nullptr;
	const std::pair<int, int> default_dimensions_clown =
			std::make_pair(448, 448); /**< Pair(int, int).
 			default dimensions and coordinates of the clown */
	const std::pair<int, int> default__coordinate_on_texture_clown =
			std::make_pair(0, 0); /**< Pair(int, int).
 			default coordinate on texture of the clown */
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_on_attack = 4; /** Interger. Default
 	sprite column */
	const double default_animation_duration_on_attack = 0.4; /** Double.
 	Default sprite line for animations */

	on_attack_animation = create_animation(
			"../assets/images/sprites/enemies/clown/clown_on_attack.png",
			default_sprite_line,
			default_sprite_column_on_attack,
			default_animation_duration_on_attack, "LEFT"
	);

	on_attack_animation->set_values(
			default_dimensions_clown,
			default_dimensions_clown,
			default__coordinate_on_texture_clown
	);
	on_attack_animation->in_loop = false;
	assert(on_attack_animation != nullptr);
	add_animation("on_attack_animation", on_attack_animation);
	DEBUG("on_attack_animation finished")
}

/**
 * @brief Initializes Clown animations
 *
 * Initializes animations dying of the clown.
 *
 * @return void
 */
void Clown::initialize_animation_dying(){

	/* Initializes the animation when the clown is dying */
	DEBUG("dying_animation")
	engine::Animation *dying_animation = nullptr;
	const std::pair<int, int> default_dimensions_clown =
			std::make_pair(448, 448); /**< Pair(int, int).
 			default dimensions and coordinates of the clown */
	const std::pair<int, int> default__coordinate_on_texture_clown =
			std::make_pair(0, 0); /**< Pair(int, int).
 			default coordinate on texture of the clown */
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_dying = 5; /** Interger.
 	Default sprite column */
	const double default_animation_duration_dying = 0.9; /** Double.
 	Default sprite line for animations */
	dying_animation = create_animation(
			"../assets/images/sprites/enemies/clown/clown_dying.png",
			default_sprite_line,
			default_sprite_column_dying,
			default_animation_duration_dying, "LEFT"
	);

	dying_animation->set_values(
			default_dimensions_clown,
			default_dimensions_clown,
			default__coordinate_on_texture_clown
	);
	dying_animation->in_loop = false;
	dying_animation->is_a_final_animation = true;
	assert(dying_animation != nullptr);
	add_animation("dying_animation", dying_animation);
	DEBUG("dying_animation finished")
}

/**
 * @brief Initializes Clown animations
 *
 * Initializes animations attacking of the clown.
 *
 * @return void
 */
void Clown::initialize_animation_attacking() {

	/* Initializes the animation when clown is attacking */
	DEBUG("attacking_animation")
	engine::Animation *attacking_animation = nullptr;
	const std::pair<int, int> default_dimensions_clown =
			std::make_pair(448, 448); /**< Pair(int, int).
 			default dimensions and coordinates of the clown */
	const std::pair<int, int> default__coordinate_on_texture_clown =
			std::make_pair(0, 0); /**< Pair(int, int).
 			default coordinate on texture of the clown */
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_attacking = 6; /** Interger.
 	Default sprite column */
	const double default_animation_duration_attacking = 1.5; /** Double.
 	Default sprite line for animations */
	attacking_animation = create_animation(
			"../assets/images/sprites/enemies/clown/clown_attacking.png",
			default_sprite_line,
			default_sprite_column_attacking,
			default_animation_duration_attacking, "LEFT"
	);

	attacking_animation->set_values(
			default_dimensions_clown,
			default_dimensions_clown,
			default__coordinate_on_texture_clown
	);
	assert(attacking_animation != nullptr);
	add_animation("attacking_animation", attacking_animation);
	DEBUG("attacking_animation finished")
}

/**
 * @brief Initializes Clown animations
 *
 * Initializes animations idle of the clown.
 *
 * @return void
 */
void Clown::initialize_animation_idle() {

	/* Initializes the clown standing animation */
	DEBUG("idle_animation")
	engine::Animation *idle_animation = nullptr;
	const std::pair<int, int> default_dimensions_clown =
			std::make_pair(448, 448); /**< Pair(int, int).
 			default dimensions and coordinates of the clown */
	const std::pair<int, int> default__coordinate_on_texture_clown =
			std::make_pair(0, 0); /**< Pair(int, int).
 			default coordinate on texture of the clown */
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_idle = 15; /** Interger.
 	Default sprite column */
	const double default_animation_duration_idle = 3; /** Double.
 	Default sprite line for animations */

	idle_animation = create_animation(
			"../assets/images/sprites/enemies/clown/clown_idle.png",
			default_sprite_line,
			default_sprite_column_idle,
			default_animation_duration_idle, "LEFT"
	);

	idle_animation->set_values(
			default_dimensions_clown,
			default_dimensions_clown,
			default__coordinate_on_texture_clown
	);
	assert(idle_animation != nullptr);
	add_animation("idle_animation", idle_animation);
	idle_animation->activate();
	set_actual_animation(idle_animation);
	DEBUG("idle_animation finished")
}

/**
 * @brief Initializes Clown animations
 *
 * Initializes animations vunerable of the clown.
 *
 * @return void
 */
void Clown::initialize_animation_idle_vunerable(){

	/* Initializes the animation when the clown if vunerable to get a hit */
	DEBUG("idle_vunelrable_animation")
	engine::Animation *idle_vulnerable_animation = nullptr;
	const std::pair<int, int> default_dimensions_clown =
			std::make_pair(448, 448); /**< Pair(int, int).
 			default dimensions and coordinates of the clown */
	const std::pair<int, int> default__coordinate_on_texture_clown =
			std::make_pair(0, 0); /**< Pair(int, int).
 			default coordinate on texture of the clown */
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_idle= 15; /** Interger.
 	Default sprite column */
	const double default_animation_duration_idle = 3; /** Double.
 	Default sprite line for animations */

	idle_vulnerable_animation = create_animation(
			"../assets/images/sprites/enemies/clown/clown_vulnerable_idle.png",
			default_sprite_line,
			default_sprite_column_idle,
			default_animation_duration_idle, "LEFT"
	);

	idle_vulnerable_animation->set_values(
			default_dimensions_clown,
			default_dimensions_clown,
			default__coordinate_on_texture_clown
	);
	assert(idle_vulnerable_animation != nullptr);
	add_animation("idle_vulnerable_animation", idle_vulnerable_animation);

	DEBUG("intialize_animations finished")
}

/**
 * @brief Initializes the clown as a physical object
 *
 * Makes the clowns become physical, making it impossible to cross it
 *
 * @return void
 */
void Clown::initialize_as_physicable() {
	/* Initializes the clown as a physical object */
	DEBUG("initialize_as_physicable")
	engine::Physics *physics = nullptr;
	physics = engine::Physics::get_instance();
	physics->add_physicable(this);
	collidable = true;
	assert(physics != nullptr);
	DEBUG("intialize_as_physicable finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void Clown::on_collision(engine::GameObject* other,
						 engine::Hitbox* p_my_hitbox,
						 engine::Hitbox* p_other_hitbox) {

	DEBUG("on_collision")
	on_collision_platform(other, p_my_hitbox,p_other_hitbox);
	on_collision_little_girl(other, p_my_hitbox,p_other_hitbox);
	on_collision_goop(other, p_my_hitbox,p_other_hitbox);
	DEBUG("on_collision finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the platform
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void Clown::on_collision_platform(engine::GameObject *other,
								  engine::Hitbox *p_my_hitbox,
								  engine::Hitbox *p_other_hitbox) {

	DEBUG("on_collision_platform")
	/* Get the instances of the enemies */
	Platform *platform = nullptr;
	platform = dynamic_cast<Platform *>(other);
	engine::Hitbox *my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox *other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if (get_speed_y() >= 0 && platform && my_hitbox->get_name() == "foot_hitbox") {
		/* if clown is on ground */
		INFO("clown is on ground")
		set_speed_y(0.0); /* Set speed on Y axis to 0 */
		set_position_y(other_hitbox->get_coordinates().second - 380);
	}
	else {
		/*Do Nothing */
	}
	assert(platform != nullptr);
	assert(my_hitbox != nullptr);
	assert(other_hitbox != nullptr);
	DEBUG("on_collision_platform finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the little girl
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void Clown::on_collision_little_girl(engine::GameObject *other,
									 engine::Hitbox *p_my_hitbox,
									 engine::Hitbox *p_other_hitbox) {

	DEBUG("on_collision_little_girl")
	LittleGirl *little_girl = nullptr;
	little_girl = dynamic_cast<LittleGirl *>(other);
	engine::Hitbox *my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox *other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if (little_girl &&
		little_girl->get_state("ACTION_STATE") == "ATTACKING" &&
		my_hitbox->get_name() == "attack_hitbox" &&
		little_girl->get_actual_animation()->actual_column == 2
		&& get_state("X_STATE") != little_girl->get_state("X_STATE")
		&& get_state("ACTION_STATE") == "VULNERABLE") {
		/* if little girl is attacking the clown and the action state of the
			  clown different of vulnerable */
		DEBUG("clown is being attacked and vunerable")

		if (get_state("ACTION_STATE") == "ON_ATTACK") {
			/* if the state of the clown is on attack */
			INFO("clown state equal to on attack")

			return;
		}
		else {
			/* Else on attack */
			on_attack(other);
		}
	}
	else {
		/*Do Nothing */
	}
	assert(little_girl != nullptr);
	assert(my_hitbox != nullptr);
	assert(other_hitbox != nullptr);
	DEBUG("on_collision_little_girl finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the goop
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void Clown::on_collision_goop(engine::GameObject *other,
							  engine::Hitbox *p_my_hitbox,
							  engine::Hitbox *p_other_hitbox) {

	DEBUG("on_collision_goop")
	Goop *goop = nullptr;
	goop = dynamic_cast<Goop *>(other);
	engine::Hitbox *my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox *other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if (goop) {
		/* if goop*/
		INFO("goop")
		if (get_state("ACTION_STATE") == "NORMAL" &&
			goop->get_state("ACTION_STATE") == "REFUTED"
			&& my_hitbox->get_name() == "head_hitbox") {
			/* if the goop is refuted by the little girl */
			INFO("goop refuted")
			refuted_goop_hits++; /*Increment refuted_goop_hits*/

			goop->set_actual_animation(goop->animations["goop_squash_animation"]);
			goop->set_speed_x(0.0); /*Set goop speed on X axis to 0 */

			const int refuted_goop_hits_limit = 20; /**Interger. Limit of refuted goops */

			if (refuted_goop_hits >= refuted_goop_hits_limit) {
				/* If the refuted goop hits is higher or equal than 20,
				set the state of the clown to vunerable. */
				INFO("refuted goops hits")
				states.set_state("ACTION_STATE", "VULNERABLE"); /* Set state to vunerable*/
				set_actual_animation(animations["idle_vulnerable_animation"]); /* Set the animation to
  				idle_vulnerable_animation */
				refuted_goop_hits = 0;
				//engine::Game::get_instance().get_actual_scene()->deactivate_game_object(goop->name);
				//goop->free();
			}
			else {
				/*Do Nothing */
			}
		}
		else {
			/*Do Nothing */
		}
	}
	else {
		/*Do Nothing */
	}
	assert(goop != nullptr);
	assert(my_hitbox != nullptr);
	assert(other_hitbox != nullptr);
	DEBUG("on_collision_goop finished")
}

/**
 * @brief Initializes Clown hitboxes
 *
 * Initializes clown instance foot hitbox
 *
 * @return void
 *
 */
void Clown::initialize_foot_hitbox() {

	/* Get actual state of the game */
	DEBUG("initialize_foot_hitbox")
	engine::Game &game = engine::Game::get_instance();
	const std::pair<int, int> default_foothitbox_displacement =
			std::make_pair(160, 380); /**< Pair(int, int). Hitbox's displacement */
	const std::pair<int, int> default_foothitbox_dimension =
			std::make_pair(180, 20); /**< Pair(int, int). Hitbox's dimension */

	/* Creates the foot hitbox for the clown */
	DEBUG("foot_hitbox")
	engine::Hitbox *foot_hitbox = nullptr;
	foot_hitbox = new engine::Hitbox(
			"foot_hitbox",
			this->get_position(),
			default_foothitbox_displacement,
			default_foothitbox_dimension,
			game.get_renderer()
	);
	/* Add component to the game */
	assert(foot_hitbox != nullptr);
	add_component(foot_hitbox);
	DEBUG("initialize_foot_hitbox finished")
}

/**
 * @brief Initializes Clown hitboxes
 *
 * Initializes clown instace attack hitbox
 *
 * @return void
 *
 */
void Clown::initialize_attack_hitbox() {

	/* Get actual state of the game */
	DEBUG("initialize_attack_hitbox")
	engine::Game &game = engine::Game::get_instance();
	const std::pair<int, int> default_attack_hitbox_displacement =
			std::make_pair(120, 170); /**< Pair(int, int).
 			Hitbox's displacement */
	const std::pair<int, int> default_attack_hitbox_dimension =
			std::make_pair(100, 25); /**< Pair(int, int).
 			Hitbox's dimension */

	/* Creates the attack hitbox for the clown */
	DEBUG("attack_hitbox")
	engine::Hitbox *attack_hitbox = nullptr;
	attack_hitbox = new engine::Hitbox(
			"attack_hitbox",
			this->get_position(),
			default_attack_hitbox_displacement,
			default_attack_hitbox_dimension,
			game.get_renderer()
	);
	/* Add component to the game */
	assert(attack_hitbox != nullptr);
	add_component(attack_hitbox);
	DEBUG("initialize_attack_hitbox finished")
}

/**
 * @brief Initializes Clown hitboxes
 *
 * Initializes clown instance head hitbox
 *
 * @return void
 *
 */
void Clown::initialize_head_hitbox() {

	/* Get actual state of the game */
	DEBUG("initialize_head_hitbox")
	engine::Game &game = engine::Game::get_instance();
	const std::pair<int,int> default_head_hitbox_displacement =
			std::make_pair(120, 90); /**< Pair(int, int).
 			Hitbox's displacement */
	const std::pair<int,int> default_head_hitbox_dimension =
			std::make_pair(110,110); /**< Pair(int, int).
 			Hitbox's dimension */

	/* Creates the head hitbox of the clown */
	DEBUG("head_hitbox")
	engine::Hitbox *head_hitbox = nullptr;
	head_hitbox = new engine::Hitbox(
			"head_hitbox",
			this->get_position(),
			default_head_hitbox_displacement,
			default_head_hitbox_dimension,
			game.get_renderer()
	);
	/* Add component to the game */
	assert(head_hitbox != nullptr);
	add_component(head_hitbox);
	DEBUG("initialize_head_hitbox finished ")
}

/**
 * @brief Initializes Clown state map
 *
 * Initializes all possibles states for the clown
 *
 * @return void
 *
 */
void Clown::initialize_state_map() {
	/* Set the initial position and state for the clown on the game */
	DEBUG("initialize_state_map")
	states.set_state("ACTION_STATE", "NORMAL");
	DEBUG("initialize_state_map finished")
}

/**
 * @brief Register game events
 *
 * Register an event for the clown
 *
 * @param game_event triggering in-game events
 *
 * @return void
 */
void Clown::on_event(GameEvent game_event) {
	/* Gets the name of the game event */
	DEBUG("on_event")
	std::string event_name = game_event.game_event_name;

	if (event_name == "MOVE_LEFT" &&
		!engine::GameObject::on_limit_of_level) {
		/* If the event name is move left and the hitboxes are int
		 the limit set the position on the x axis +10 */
		INFO("limit move left")
		set_position_x(get_position_x() + 10);
	}
	else if (event_name == "MOVE_RIGHT" &&
			 !engine::GameObject::on_limit_of_level) {
		/* If the event name is move right and the hitboxes are int
		the limit set the position on the x axis -10 */
		INFO("limit move right")
		set_position_x(get_position_x() - 10);
	}
	else {
		/*Do Nothing */
	}

	assert(event_name != "");
	DEBUG("on_event finished")
}

/**
 * @brief Notify if the object is in the range
 *
 * Notify if there is any object that are in the range of the clown
 *
 * @param game_object the game object passed in the notification
 *
 * @return void
 *
 */
void Clown::notify(engine::Observable *game_object) {
	DEBUG("notify")
	/* Gets as observable that tells when the little girl is closer  */
	LittleGirl *little_girl = nullptr;
	little_girl = dynamic_cast<LittleGirl *>(game_object);

	/* Notify if the little girl exists, to attack her */
	if (little_girl) {
		INFO("notify clown about little girl")
		attack(little_girl);
	}
	else {
		/*Do Nothing */
	}
	assert(little_girl != nullptr);
	DEBUG("notify finished")
}

/**
 * @brief Creates a goop
 *
 * Method that creates a goop for the clowns attack
 *
 * @return the goop's game object
 */
engine::GameObject *Clown::create_goop() {
	DEBUG("create_goop")

	engine::GameObject *goop = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/
	const int pair_goop_x_axis = 885; /** Interger. constant on the
 	x axis for the first tidy pair of the goop */
	const int pair_goop_y_axis = 420; /** Interger. constant on the
 	y axis for the first tidy pair of the goop */
	const int goop_y_axis = 60; /** Interger. constant on the y
 	axis for pair of the goop */

	goop = new Goop("goop", std::make_pair(pair_goop_x_axis, pair_goop_y_axis),
					goop_y_axis);
	engine::Game::get_instance().get_actual_scene()->add_object(goop);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop);

	/** Load the object goop*/
	goop->load();

	assert(goop != nullptr);
	return goop;
	DEBUG("create_goop finished")
}

/**
 * @brief Method for clown attack
 *
 * Method called for attack a game object
 *
 * @param little_girl object to be attacked
 *
 * @return void
 */
void Clown::attack(engine::GameObject *little_girl){

	attacking(little_girl);
	dying(little_girl);
	attack_girl(little_girl);
	vunerable(little_girl);
}

/**
 * @brief Method for clown attack
 *
 * Method called when the clown is vunerable
 *
 * @param little_girl object to be attacked
 *
 * @return void
 */
void Clown::vunerable(engine::GameObject *little_girl) {

	DEBUG("attack")
	/* Gets the actual action state of the clown  */
	std::string actual_action_state = get_state("ACTION_STATE");


	if (actual_action_state == "VULNERABLE") {
		/* If the action state of the clown is vunerable */
		INFO("clown is vunerable")
		if (get_actual_animation()->is_finished) {
			/* if the actual animation of the clown is finished */
			INFO("animation has finished")
			set_actual_animation(animations["idle_vulnerable_animation"]);
		} else {
			/*Do Nothing */
		}

		vulnerable_counter++; /*Increment vunerable_counter */

		const int vunerable_counter_limit = 600; /** Interger. limit for
 		the vunerable counter */

		if (vulnerable_counter >= vunerable_counter_limit) {
			/* if the vunerable counter is higher or equal to 600 */
			INFO("vunerable_counter")
			states.set_state("ACTION_STATE", "NORMAL");
			set_actual_animation(animations["idle_animation"]);
			vulnerable_counter = 0;
		} else {
			/* Else do nothing */
			return;
		}
	} else {
		/*Do Nothing */
	}
	assert(actual_action_state != "");
}

/**
 * @brief Method for clown attack
 *
 * Method called when the clown is attacking
 *
 * @param little_girl object to be attacked
 *
 * @return void
 */
void Clown::attacking(engine::GameObject *little_girl) {
	/* Gets the actual action state of the clown  */
	std::string actual_action_state = get_state("ACTION_STATE");

	if (actual_action_state == "ON_ATTACK" ||
		actual_action_state == "ATTACKING") {
		/* if the actual action state of the clown is on attack or attacking */
		INFO("clown state")
		if (get_actual_animation()->is_finished) {
			/*if the actual animation of the clown is finished */
			INFO("animation has finished")
			states.set_state("ACTION_STATE", "NORMAL");
			set_actual_animation(animations["idle_animation"]);
		} else {
			/* Else do nothing*/
			return;
		}
	} else {
		/*Do Nothing */
	}
	assert(actual_action_state != "");
}

/**
 * @brief Method for clown attack
 *
 * Method called when the clown attack little girl
 *
 * @param little_girl object to be attacked
 *
 * @return void
 */
void Clown::attack_girl(engine::GameObject *little_girl) {

	/* Gets the actual action state of the clown  */
	std::string actual_action_state = get_state("ACTION_STATE");
	float clown_position = 0; /**< Interger. Clown position on the x axis */
	/* Gets the position of the clown on the x axis */
	clown_position = get_position_x();
	float little_girl_position = 0; /**<Interger. Little girl
	position on the x axis*/
	/*Gets the position of the little girl on the x axis */
	little_girl_position = little_girl->get_position_x();
	float distance_from_girl = 0; /**< Interger. distance in between
 	the little girl and the clown */
	const int distance_from_girl_limit_max = 650;/**< Interger.
 	Max distance from girl*/
	const int attack_animation_trigger_limit = 90;/**< Interger.
 	Attack animation trigger limit */
	/* Gets the distance from the little girl */
	distance_from_girl = clown_position - little_girl_position;

	if (distance_from_girl < distance_from_girl_limit_max
		&& actual_action_state != "VULNERABLE") {
		/* if the distance from girl is lower than 650*/
		INFO("distance from girl")
		/* increment the attack animation trigger +1*/
		attack_animation_trigger += 1;

		if (attack_animation_trigger == attack_animation_trigger_limit) {
			/* if the attack animation trigger is equal to 90*/
			INFO("attack animation trigger")
			/* Set the state of the clown to attacking */
			states.set_state("ACTION_STATE", "ATTACKING");
			/* Set the actual animation of the clown to attacking */
			set_actual_animation(animations["attacking_animation"]);

			int clown_attack_option = rand() % 1000; /**< Interger.
 			clown attack option to random %1000*/
			const int clown_attack_option_limit_lower = 300; /**< Interger.
 			clown attack option limit lower */
			const int clown_attack_option_limit_higher = 700; /**< Interger.
 			clown attack option limit  higher*/

			if (clown_attack_option < clown_attack_option_limit_lower) {
				/* if the clown attack option is lower than 300*/
				INFO("clown basic attack")
				/* Basic attack of the clown */
				basic_attack();
			}
			else if (clown_attack_option >= clown_attack_option_limit_lower &&
					 clown_attack_option < clown_attack_option_limit_higher) {
				/* else if the clown attack option is higher or
				equal to 300 and lower than 700*/
				INFO("clown double attack")
				/* Double attack of the clown */
				double_attack();
			}
			else {
				/* else serial attack */
				INFO("clown serial attack")
				/* Serial attack of the clown */
				serial_attack();
			}
			/* Attack animation trigger setted to 0  */
			attack_animation_trigger = 0;
		}
		else {
			/*Do Nothing */
		}

	}
	else {
		/*Do Nothing */
	}
	assert(actual_action_state != "");
	DEBUG("attack finished")
}

/**
 * @brief Method for clown attack
 *
 * Method called when the clown is dying
 *
 * @param little_girl object to be attacked
 *
 * @return void
 */
void Clown::dying(engine::GameObject *little_girl) {

	// meio do metodo 3 chamada
	/* Gets the actual action state of the clown  */
	std::string actual_action_state = get_state("ACTION_STATE");

	if (actual_action_state == "DYING") {
		/* if the actual action state of the clown is dying */
		INFO("clown is dying")
		return;
	} else {
		/*Do Nothing */
	}
	assert(actual_action_state != "");
}

/**
 * @brief Clown basic attack
 *
 * Method for clown basic attack
 *
 * @return void
 */
void Clown::basic_attack() {
	DEBUG("basic_attack")
	clown_goops.clear();

	DEBUG("goop")
	engine::GameObject *goop = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/
	const int add_position_X_axis = 40; /** Interger. Constant to
 	add on the X axis */
	const int add_position_Y_axis = 150; /** Interger. Constant to
 	add on the y axis */
	const int goop_position_Y_axis = 60; /** Interger. Constant to
 	on the y axis for the goop */

	goop = new Goop("goop", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop);

	goop->load();
	goop->set_speed_x(-30);
	goop->set_speed_y(-10);

	/** Push back the object goop */
	assert(goop != nullptr);
	clown_goops.push_back(goop);
	DEBUG("basic_attack finished")
}

/**
 * @brief Clown double attack
 *
 * Method for double the basic attack of the clown
 *
 * @return void
 *
 */
void Clown::double_attack() {
	DEBUG("double_attack")
	clown_goops.clear();

	DEBUG("goop_5")
	engine::GameObject *goop_5 = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/
	const int add_position_X_axis = 40; /** Interger. Constant to
 	add on the X axis */
	const int add_position_Y_axis = 150; /** Interger. Constant to
 	add on the y axis */
	const int goop_position_Y_axis = 60; /** Interger. Constant to
 	on the y axis for the goop */

	goop_5 = new Goop("goop_5", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					  goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop_5);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_5);

	goop_5->load();
	goop_5->set_speed_x(-7);
	goop_5->set_speed_y(-10);

	/** Push back the object goop */
	assert(goop_5 != nullptr);
	clown_goops.push_back(goop_5);

	DEBUG("goop_6")
	engine::GameObject *goop_6 = nullptr;/** Variable < pointer to goop,
 	attack of the clown*/

	goop_6 = new Goop("goop_6", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					  goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop_6);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_6);

	goop_6->load();
	goop_6->set_speed_x(-15);
	goop_6->set_speed_y(-10);

	/** Push back the object goop */
	assert(goop_6 != nullptr);
	clown_goops.push_back(goop_6);
	DEBUG("double_attack finished")
}

/**
 * @brief Clown serial attack
 *
 * Method for serial attack of the clown
 *
 * @return void
 *
 */
void Clown::serial_attack() {
	DEBUG("serial_attack")

	if (clown_goops.size() > 3) {
		INFO("clown goops size")
		clown_goops.clear();
	}
	else {
		/*Do Nothing */
	}


	DEBUG("goop_1")
	engine::GameObject *goop_1 = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/
	const int add_position_X_axis = 40; /** Interger. Constant to
 	add on the X axis */
	const int add_position_Y_axis = 150; /** Interger. Constant to
 	add on the y axis */
	const int goop_position_Y_axis = 60; /** Interger. Constant to
 	on the y axis for the goop */

	goop_1 = new Goop("goop_1", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					  goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop_1);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_1);

	goop_1->load();
	goop_1->set_speed_x(-20);
	goop_1->set_speed_y(-8);
	assert(goop_1 != nullptr);
	clown_goops.push_back(goop_1);

	DEBUG("goop_2")
	engine::GameObject *goop_2 = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/

	goop_2 = new Goop("goop_2", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					  goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop_2);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_2);

	goop_2->load();
	goop_2->set_speed_x(-20);
	goop_2->set_speed_y(-20);
	assert(goop_2 != nullptr);
	clown_goops.push_back(goop_2);

	DEBUG("goop_3")
	engine::GameObject *goop_3 = nullptr; /** Variable < pointer to goop,
 	attack of the clown*/

	goop_3 = new Goop("goop_3", std::make_pair(
			get_position_x() + add_position_X_axis,
			get_position_y() + add_position_Y_axis),
					  goop_position_Y_axis);

	engine::Game::get_instance().get_actual_scene()->add_object(goop_3);
	engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_3);

	goop_3->load();
	goop_3->set_speed_x(-20);
	goop_3->set_speed_y(-25);
	assert(goop_3 != nullptr);
	clown_goops.push_back(goop_3);

	DEBUG("serial_attack")
}

/**
 * @brief On Attack Event
 *
 * Event called on the clown is attacking
 *
 * @param game_object object to be attacked
 *
 * @return void
 */
void Clown::on_attack(engine::GameObject *game_object) {
	//states.set_state("ACTION_STATE","ON_ATTACK");
	DEBUG("on_attack")
	hit(game_object, 1);

	if (is_alive()) {
		/* if the object is alive set the actual
		   animation to on attack animation */
		INFO("object is alive")
		set_actual_animation(animations["on_attack_animation"]);
		//play_song("hit_me");
	}
	else {
		/*Do Nothing */
	}
	DEBUG("on_attack finished")
}

/**
 * @brief Death Method
 *
 * Method for the death of the clown
 *
 * @param game_object Clown
 *
 * @return void
 */
void Clown::die(engine::GameObject *game_object) {

	DEBUG("die")
	std::string actual_x_state = get_state("X_STATE");
	/** String <Variable to save the actual state */

	/* Set the actual state for dying */
	states.set_state("ACTION_STATE", "DYING");

	/* Set the actual animation to dying animation */
	set_actual_animation(animations["dying_animation"]);
	//play_song("hit_me");
	DEBUG("level_factory")
	LevelFactory *level_factory = nullptr; /** Pointer< to the object level factory */
	level_factory = new LevelFactory();
	engine::Game *game = &(engine::Game::get_instance());

	level_factory->update_level(
			dynamic_cast<engine::Level *>(game->get_actual_scene()),
			"../data/win.dat"
	);

	/*Set the state of the game to paused */
	assert(actual_x_state != "");
	assert(level_factory != nullptr);
	game->set_state(engine::Game::PAUSED);
	DEBUG("die finished")
}

/**
 * @brief Initializes audio effects for the clown
 *
 * Not Implemented
 *
 * @return void
 *
 */
void Clown::initialize_audio_effects() {
	/* Empty method to audio effects of the clown */
}
