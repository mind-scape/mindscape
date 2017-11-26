/**
 * @file dark_girl.cpp
 * @brief Purpose: Contains dark girl methods and attributes
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#include "dark_girl.hpp"
#include "platform.hpp"
#include "scorpion.hpp"
#include "goop.hpp"
#include "../engine/include/game.hpp"
#include "log.hpp"
#include "level_factory.hpp"
#include <typeinfo>
#include <algorithm>
#include <unistd.h>
#include <assert.h>

using namespace mindscape;

/**
 * @brief Initializes Dark Girl
 *
 * @param name Object's name
 * @param position x and y position
 * @param priority rendering object priority
 */
DarkGirl::DarkGirl(
		std::string name,
		std::pair<int, int> position,
		int priority
)

		:engine::GameObject(

		name,
		position,
		priority,
		{
				{engine::KeyboardEvent::LEFT, "MOVE_LEFT"},
				{engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"},
				{engine::KeyboardEvent::UP, "JUMP"},
				{engine::KeyboardEvent::DOWN, "CROUCH"},
				{engine::KeyboardEvent::F, "ATTACK"},
		}

), Fighter(90) {
	/* Initializes all the characteristics for the Dark Girl */
	initialize_state_map();
	initialize_hitbox();
	initialize_footer_hitbox();
	initialize_running_animation();
	initialize_idle_animation();
	initialize_jumping_animation();
	initialize_attacking_animation();
	initialize_dying_animation();
	initialize_audio_effects();
	initialize_as_physicable();
};

/**
 * @brief create dark girl animations
 *
 * Creates the animations for the dark girl on the second level
 *
 * @param path path to the image which contains the sprite sheet
 * @param sprite_lines number of the lines on the sprite sheet
 * @param sprite_columns number of columns on the sprite sheet
 * @param duration Time duration of the animation
 * @param direction direction of the animation
 *
 * @return animation created
 */
engine::Animation* DarkGirl::create_animation(

		std::string image_path,
		int sprite_lines,
		int sprite_columns,
		double duration,
		std::string direction) {

	DEBUG("create_animation");

	assert(image_path != "");
	assert(sprite_lines);
	assert(sprite_columns);
	assert(direction != "");

	engine::Game& game = engine::Game::get_instance();

	const bool default_is_active = false;
	const std::pair<int, int> default_displacement = std::make_pair(0, 0);
	const int default_priority = 1;
	const bool default_in_loop = true;

	/* Creates and initializes the object of the Dark GIrl */
	engine::Animation* animation = nullptr;
	animation = new engine::Animation(
			game.get_renderer(),
			image_path,
			// is_active
			default_is_active,
			// displacement
			default_displacement,
			// priority
			default_priority,
			sprite_lines,
			sprite_columns,
			duration,
			// in_loop
			default_in_loop,
			direction
	);


	/* Defaults dimensions and coordinates of dark girl in pixels */
	const std::pair<int, int> default_dimensions_dark_girl = std::make_pair(192, 192);

	const std::pair<int, int> coordinates_on_texture_dark_girl = std::make_pair(0, 0);

	/* Set dimentions on screen and, coordinates and dimention on texture  */
	animation->set_values(
			default_dimensions_dark_girl,
			default_dimensions_dark_girl,
			coordinates_on_texture_dark_girl
	);

	DEBUG("create_animation finished");

	assert(animation != nullptr);
	return animation;
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes running animation for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_running_animation() {
	DEBUG("initialize_running_right_animation ");
	/* Initializes animation of the Dark Girl running right */
	engine::Animation *running_right_animation = nullptr;
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_running = 9; /** Interger. Default
 	sprite column */
	const double default_animation_duration_running = 0.9; /** Double.
 	Default sprite line for animations */

	running_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_running_right.png",
			default_sprite_line,
			default_sprite_column_running,
			default_animation_duration_running, "RIGHT"
	);
	assert(running_right_animation != nullptr);
	add_animation("running_right_animation", running_right_animation);

	/* Initializes animation of the Dark Girl running left */
	DEBUG("running_left_animation");
	engine::Animation *running_left_animation = nullptr;
	running_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_running_left.png",
			default_sprite_line,
			default_sprite_column_running,
			default_animation_duration_running, "LEFT"
	);
	assert(running_left_animation != nullptr);
	add_animation("running_left_animation", running_left_animation);
	DEBUG("initialize_running_right_animation finished");
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes idle animation for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_idle_animation() {
	DEBUG("initialize_idle_animation");
	/* Initializes animation of the Dark Girl standing looking right */
	DEBUG("idle_right_animation");
	engine::Animation *idle_right_animation = nullptr;
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_idle = 10; /** Interger. Default
 	sprite column */
	const double default_animation_duration_idle = 1.5; /** Double.
 	Default sprite line for animations */

	idle_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_idle_right.png",
			default_sprite_line,
			default_sprite_column_idle,
			default_animation_duration_idle, "RIGHT"
	);
	assert(idle_right_animation != nullptr);
	add_animation("idle_right_animation", idle_right_animation);

	/* Initializes animation of the Dark Girl standing looking left */
	DEBUG("idle_left_animation");
	engine::Animation *idle_left_animation = nullptr;
	idle_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_idle_left.png",
			default_sprite_line,
			default_sprite_column_idle,
			default_animation_duration_idle, "LEFT"
	);
	assert(idle_left_animation != nullptr);
	add_animation("idle_left_animation", idle_left_animation);

	/* Initializes animation of the Dark Girl
	when she is standing */
	idle_right_animation->activate();
	set_actual_animation(idle_right_animation);
	DEBUG("initialize_idle_animation finished");
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes jumping animation for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_jumping_animation() {
	DEBUG("initialize_jumping_animation");
	/* Initializes animation of the Dark Girl jumping to the right */
	DEBUG("jumping_right_animation");
	engine::Animation *jumping_right_animation = nullptr;
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_jumping = 5; /** Interger. Default
 	sprite column */
	const double default_animation_duration_jumping = 1.5; /** Double.
 	Default sprite line for animations */

	jumping_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_jumping_right.png",
			default_sprite_line,
			default_sprite_column_jumping,
			default_animation_duration_jumping, "RIGHT"
	);
	assert(jumping_right_animation != nullptr);
	add_animation("jumping_right_animation", jumping_right_animation);

	/* Initializes animation of the Dark Girl jumping to the left */
	DEBUG("jumping_left_animation");
	engine::Animation *jumping_left_animation = nullptr;
	jumping_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_jumping_left.png",
			default_sprite_line,
			default_sprite_column_jumping,
			default_animation_duration_jumping, "LEFT"
	);
	assert(jumping_left_animation != nullptr);
	add_animation("jumping_left_animation", jumping_left_animation);
	DEBUG("initialize_jumping_animation finished");
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes attacking animation for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_attacking_animation() {
	DEBUG("initialize_attacking_animation");
	/* Initializes animation of the Dark Girl attacking to the right */
	DEBUG("attacking_right_animation");
	engine::Animation *attacking_right_animation = nullptr;
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_attacking = 5; /** Interger. Default
 	sprite column */
	const double default_animation_duration_attacking = 0.5; /** Double.
 	Default sprite line for animations */

	attacking_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_attacking_right.png",
			default_sprite_line,
			default_sprite_column_attacking,
			default_animation_duration_attacking, "RIGHT"
	);
	attacking_right_animation->in_loop = false;
	add_animation("attacking_right_animation", attacking_right_animation);

	/* Initializes animation of the Dark Girl attacking to the left */
	DEBUG("attacking_left_animation");
	engine::Animation *attacking_left_animation = nullptr;
	attacking_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_attacking_left.png",
			default_sprite_line,
			default_sprite_column_attacking,
			default_animation_duration_attacking, "LEFT"
	);
	attacking_left_animation->in_loop = false;
	assert(attacking_left_animation != nullptr);
	add_animation("attacking_left_animation", attacking_left_animation);
	DEBUG("initialize_attacking_animation finished");
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes dying animation for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_dying_animation(){
	DEBUG("initialize_dying_animation")
	/* Initializes animation of the Dark Girl
	when she was sying looking to the left */
	DEBUG("dying_left_animation");
	engine::Animation* dying_left_animation = nullptr;
	const int default_sprite_line = 1; /** Interger. Default sprite
 	line for animations */
	const int default_sprite_column_dying = 5; /** Interger. Default
 	sprite column */
	const double default_animation_duration_dying = 1.0; /** Double.
 	Default sprite line for animations */

	dying_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_dying_left.png",
			default_sprite_line,
			default_sprite_column_dying,
			default_animation_duration_dying, "LEFT"
	);

	dying_left_animation->in_loop = false;
	dying_left_animation->is_a_final_animation = true;
	assert(dying_left_animation != nullptr);
	add_animation("dying_left_animation", dying_left_animation);

	/* Initializes animation of the Dark Girl
	when she was sying looking to the right */
	DEBUG("dying_right_animation");
	engine::Animation* dying_right_animation = nullptr;
	dying_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_dying_right.png",
			default_sprite_line,
			default_sprite_column_dying,
			default_animation_duration_dying, "RIGHT"
	);

	dying_right_animation->in_loop = false;
	dying_right_animation->is_a_final_animation = true;
	assert( dying_right_animation != nullptr);
	add_animation("dying_right_animation", dying_right_animation);
	DEBUG("initialize_dying_animation finished");
}

/**
 * @brief Initializes hitboxes for dark girl
 *
 * Initializes dark girl instance hitbox
 *
 * @return void
 */
void DarkGirl::initialize_hitbox() {
	DEBUG("initialize_hitbox");

	/* Get actual state of the game */
	engine::Game &game = engine::Game::get_instance();
	const std::pair<int, int> default_hitbox_displacement =
			std::make_pair(60, 45); /**< Pair(int, int). Hitbox's displacement */
	const std::pair<int, int> default_hitbox_dimension =
			std::make_pair(50, 130); /**< Pair(int, int). Hitbox's dimension */

	/* Creates Dark Girl Hitbox*/
	engine::Hitbox *hitbox = nullptr;
	hitbox = new engine::Hitbox(
			"hitbox",
			get_position(),
			default_hitbox_displacement,
			default_hitbox_dimension,
			game.get_renderer()
	);

	/* Add component in the game */
	assert(hitbox != nullptr);
	add_component(hitbox);
	DEBUG("initialize_hitbox finished");
}

/**
 * @brief Initializes hitboxes for dark girl
 *
 * Initializes dark girl instance footer hitbox
 *
 * @return void
 */
void DarkGirl::initialize_footer_hitbox(){
	DEBUG("initialize_footer_hitbox");

	engine::Game &game = engine::Game::get_instance();
	const std::pair<int,int> default_footer_displacement =
			std::make_pair(60, 180); /**< Pair(int, int). Hitbox's displacement */
	const std::pair<int,int> default_footer_dimension =
			std::make_pair(50, 20); /**< Pair(int, int). Hitbox's dimension */

	/* Creates Dark Girl Hitbox on footer*/
	engine::Hitbox* footer = nullptr;
	footer = new engine::Hitbox(
			"footer",
			get_position(),
			default_footer_displacement,
			default_footer_dimension,
			game.get_renderer()
	);

	/* Add component in the game */
	assert(footer != nullptr);
	add_component(footer);

	DEBUG("initialize_footer_hitbox finished");
}

/**
 * @brief Initialize state map for dark girl
 *
 * Initialize all the possibles states for dark girl
 *
 * @return void
 */
void DarkGirl::initialize_state_map() {
	/* Sets the initial position of the Dark Girl on the game,
	also her action and states*/
	DEBUG("initialize_state_map");
	states.set_state("X_STATE", "LOOKING_RIGHT");
	states.set_state("Y_STATE", "FALLING");
	states.set_state("ACTION_STATE", "NORMAL");
	DEBUG("initialize_state_map finished");
}

/**
 * @brief Initializes audio effects
 *
 * Initializes audio effects for dark girl on second level
 *
 * @return void
 */
void DarkGirl::initialize_audio_effects() {
	DEBUG("initialize_audio_effects");

	/* Initializes Audio effects while the Dark GIrl is Walking*/
	DEBUG("little_girl_steps")
	engine::Audio * little_girl_steps = nullptr;
	const float sound_duration_steps  = 1; /**Float. Sound duration effect */
	const int sound_volume = 45; /**Int. Sound duration effect */

	little_girl_steps = new engine::Audio(
			"steps",
			"../assets/audios/effects_songs/menina_passos_rapido.wav",
			engine::Audio::CHUNK
	);

	little_girl_steps->set_duration(sound_duration_steps);
	little_girl_steps->set_effect_volume(sound_volume);
	assert(little_girl_steps != nullptr);
	add_component(little_girl_steps);

	/* Initializes Audio effects while the Dark GIrl is getting a hit*/
	DEBUG("little_gitl_getting_hit")
	engine::Audio * little_girl_getting_hit = nullptr;

	const float sound_duration = 0.5; /**Float. Sound duration effect */

	little_girl_getting_hit = new engine::Audio(
			"hit_me",
			"../assets/audios/effects_songs/menina_apanhando.wav",
			engine::Audio::CHUNK
	);

	little_girl_getting_hit->set_duration(sound_duration);
	assert(little_girl_getting_hit != nullptr);
	add_component(little_girl_getting_hit);

	/* Initializes Audio effects while the Dark GIrl is Attacking*/
	DEBUG("sword_song")
	engine::Audio * sword_song = nullptr;
	sword_song = new engine::Audio(
			"sword_attack",
			"../assets/audios/effects_songs/espada_fase_1.wav",
			engine::Audio::CHUNK
	);
	sword_song->set_duration(sound_duration);
	assert(sword_song != nullptr);
	add_component(sword_song);

	DEBUG("initialize_audio_effects finished");
}

/**
 * @brief Initializes the dark girl as a physical object
 *
 * Make this girl object suffer forces consequences.
 *
 * @return void
 */
void DarkGirl::initialize_as_physicable() {

	/* Gets physics objects and makes dark girl collidable */
	DEBUG("initialize_as_physicable");

	engine::Physics *physics = nullptr;
	physics = engine::Physics::get_instance();
	assert(physics != nullptr);
	physics->add_physicable(this);
	collidable = true;

	DEBUG("initialize_as_physicable finished");
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
void DarkGirl::on_collision(engine::GameObject* other,
									 engine::Hitbox* p_my_hitbox,
									 engine::Hitbox* p_other_hitbox) {

	on_collision_goop(other, p_my_hitbox,p_other_hitbox);
	on_collision_spider(other, p_my_hitbox,p_other_hitbox);
	on_collision_platform(other, p_my_hitbox,p_other_hitbox);
	on_collision_scorpion(other, p_my_hitbox,p_other_hitbox);
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the platform
 *
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void DarkGirl::on_collision_platform(engine::GameObject* other,
									 engine::Hitbox* p_my_hitbox,
									 engine::Hitbox* p_other_hitbox) {

	DEBUG("on_collision_platform")
	/* Gets instances of the platform */
	Platform* platform = nullptr;
	platform = dynamic_cast<Platform *>(other);
	engine::Hitbox* my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox* other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "footer") {
		//if she is falling on a platform
		INFO("She is falling on a platform")
		set_speed_y(0.0);
		set_position_y(other_hitbox->get_coordinates().second - 180);
	}
	else {
		/* Do nothing */
	}
	assert(platform != nullptr);
	assert(my_hitbox != nullptr);
	assert(p_my_hitbox != nullptr);
	DEBUG("on_collision_platform finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the scorpion
 *
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void DarkGirl::on_collision_scorpion(engine::GameObject* other,
									 engine::Hitbox* p_my_hitbox,
									 engine::Hitbox* p_other_hitbox) {

	DEBUG("on_collision_scorpion")
	/* Gets instances of the scorpion */
	Scorpion* scorpion = nullptr;
	scorpion = dynamic_cast<Scorpion *>(other);
	engine::Hitbox* my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox* other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if(scorpion &&
	   scorpion->get_state("ACTION_STATE") == "ATTACKING" &&
	   other_hitbox->get_name() == "scorpion_attack" &&
	   scorpion->get_actual_animation()->actual_column == 1) {
		/* if the scorpion is attacking the dark girl */
		INFO("Scorpion is attacking")

		/* Makes dark girl be hit and play sound effects */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}
	else {
		/* Do nothing */
	}

	assert(my_hitbox != nullptr);
	assert(p_my_hitbox != nullptr);
	DEBUG("on_collision_scorpion finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the spider
 *
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void DarkGirl::on_collision_spider(engine::GameObject* other,
								   engine::Hitbox* p_my_hitbox,
								   engine::Hitbox* p_other_hitbox) {

	DEBUG("on_collision")
	/* Gets instances of the spider */
	Spider* spider = nullptr;
	spider = dynamic_cast<Spider *>(other);
	engine::Hitbox* my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox* other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	if(spider &&
	   spider->get_state("ACTION_STATE") == "ATTACKING" &&
	   other_hitbox->get_name() == "spider_attack" &&
	   spider->get_actual_animation()->actual_column == 3) {
		/*if the spider is attacking the dark girl*/
		INFO("Spider is attacking")

		/* Makes dark girl be hit and play sound effects */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}
	else {
		/* Do nothing */
	}
	assert(my_hitbox != nullptr);
	assert(p_my_hitbox != nullptr);
	DEBUG("on_collision_spider finished")
}

/**
 * @brief On Collision event
 *
 * Method called everytime there is a collision with the goop
 *
 *
 * @param other the other game object that collided
 * @param p_my_hitbox hitbox that recives the collision
 * @param p_other_hitbox hitbox that collided
 *
 * @return void
 */
void DarkGirl::on_collision_goop(engine::GameObject* other,
								 engine::Hitbox* p_my_hitbox,
								 engine::Hitbox* p_other_hitbox) {

	DEBUG("on_collision_goop")
	/* Gets instances of the goop */
	Goop* goop = nullptr;
	goop = dynamic_cast<Goop *>(other);
	engine::Hitbox* my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox* other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);


	if(goop) {
		/* if the goop is on the dark girl direction */
		INFO("Goop is on her direction")

		if(get_state("ACTION_STATE") == "ATTACKING"
		   && goop->get_state("ACTION_STATE") != "REFUTED") {
			INFO("Goop refuted by the dark girl")
			/* if the goop was refuted by the dark girl */

			/* Makes the goop be refuted */
			goop->set_speed_x(goop->get_speed_x() * (-1));
			goop->set_speed_y(-10);

			goop->set_actual_animation(
					goop->animations["refuted_goop_animation"]);

			goop->states.set_state("ACTION_STATE","REFUTED");
		}
		else {
			/*Makes dark girl be hit and play sound effects */
			INFO("Dark girl get a hit")
			play_song("hit_me");
			on_attack(other);
			hit(other,1);
		}
	}
	else {
		/* Do nothing */
	}

	assert(my_hitbox != nullptr);
	assert(p_my_hitbox != nullptr);
	DEBUG("on_collision_goop finished")
}

/**
 * @brief Register game events
 *
 * Register an event for the dark girl, such as jump, attack and move
 *
 * @param game_event triggering in-game events
 *
 * @return void
 */
void DarkGirl::on_event(GameEvent game_event) {
	DEBUG("on_event")
	/* Gets the name of the game event */
	std::string event_name = "";
	event_name = game_event.game_event_name;
	assert(event_name != "");

	/* Gets the actual animation of the dark girl  */
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);

	/* Gets x coordinates of the game event */
	std::string actual_x_state = "";
	actual_x_state = states.get_state("X_STATE");
	assert(actual_x_state != "");

	/* Gets y coordinates of the game event */
	std::string actual_y_state = "";
	actual_y_state = states.get_state("Y_STATE");
	assert(actual_y_state != "");

	/* Gets the action state of the game event */
	std::string actual_action_state = "";
	actual_action_state = states.get_state("ACTION_STATE");
	assert(actual_action_state != "");

	if(event_name == "JUMP" && actual_y_state == "ON_GROUND") {
		/* if the event is jump and the dark girl is on groun */
		INFO("dark girl jump and she is on ground")

		/* Makes the dark girl jump */
		jump(actual_x_state);
	}
	else if(event_name == "MOVE_LEFT") {
		/* else if the event is move left */
		INFO("dark girl move left")
		/* Makes the dark girl move left*/
		move_left(actual_x_state, actual_y_state);
	}
	else if(event_name == "MOVE_RIGHT") {
		/* else if the event is move right */
		INFO("dark girl move right")
		/*Makes the dark girl move right*/
		move_right(actual_x_state, actual_y_state);
	}
	else if(event_name == "ATTACK" && actual_action_state != "ATTACKING") {
		/* if the event is attack and the actual state is
		different from attacking */
		INFO("attack event")
		/*Makes the dark girl attack*/
		attack();
	}
	else {
		/*Do Nothing */
	}
	DEBUG("on_event finished")
}

/**
 * @brief Jump Method
 *
 * Method called when dark girl need's to jump
 *
 * @param actual_x_state if the girl is facing left or right
 *
 * @return void
 */
void DarkGirl::jump(std::string actual_x_state) {

	DEBUG("jump");
	assert(actual_x_state != "");
	if(get_state("Y_STATE") != "JUMPING" ||
	   get_state("Y_STATE") != "FALLING") {
		/*if the states of the dark girl on y axis is
		different from jumping or falling */
		INFO("dark girl jump")

		/* Makes the dark girl jump */
		set_speed_y(-23);
		states.set_state("Y_STATE", "JUMPING");

		if(actual_x_state == "LOOKING_RIGHT") {
			/*If the the state of the dark girl is looking right */
			INFO("jump to the right")

			/*Stop sound effects of walking and starts the animation of
			jumping to the right direction */
			stop_song("steps");
			set_actual_animation(animations["jumping_right_animation"]);
		}
		else if(actual_x_state == "LOOKING_LEFT") {
			/* else if the state of the dark girl is looking to the left*/
			INFO("jump to the left")

			/*Stop sound effects of walking and starts the animation of
			 jumping to the left direction */
			stop_song("steps");
			set_actual_animation(animations["jumping_left_animation"]);
		}
		else {
			/*Do Nothing */
		}
		/* Gets the actual animation and increments
		jumping_animation_count value */
		engine::Animation* actual_animation = nullptr;
		actual_animation = get_actual_animation();
		assert(actual_animation != nullptr);
		jumping_animation_count += 1; /**Increment
 		jumping animation counter by 1 */
		const int jumping_animation_count_max = 26; /**Interger. Constant of
		jumping animation counter */

		if(jumping_animation_count < jumping_animation_count_max) {
			/* If the jumping_animation_count has value lower than 26 */
			INFO("jumping_animation_count value")

			if(jumping_animation_count % 5 == 0) {
				INFO("jumping_animation_count divisible")
				/* If the jumping_animation_count is divisible by 5 */

				const int coordinate_on_texture_minimum = 192;/**Interger.
 				Minimum coordinate on texture constant */
				const int coordinate_on_texture_max = 960;/**Interger. Maximum
 				coordinate on texture constant */

				/* Increment the value of the coordinates */
				actual_animation->coordinatesOnTexture.first += coordinate_on_texture_minimum;

				if(actual_animation->coordinatesOnTexture.first == coordinate_on_texture_max) {
					/*if the cordinate on the y axis is lower than 960 */
					INFO("cordinate on the Y axis")

					/* Sets coordinatesOnTexture to 0 */
					actual_animation->coordinatesOnTexture.first = 0;
				}
				else {
					/* Do nothing */
				}
			}
			else {
				/* Do nothing */
			}
		}
			/* else jumping_animation_count is higher than 25 */
		else {

			/* Sets the jumping_animation_count to 26*/
			jumping_animation_count = jumping_animation_count_max;
		}
	}
	else {
		/* Do nothing */
	}

	DEBUG("jump finished");
}

/**
 * @brief Method to walk right
 *
 * Method called when the girl needs to walk in the right direction
 *
 * @param actual_x_state if the girl is facing left or right
 * @param actual_y_state if the girl is jumping or falling
 *
 * @return void
 */
void DarkGirl::move_right(std::string actual_x_state,
						  std::string actual_y_state) {

	assert(actual_x_state != "");
	assert(actual_y_state != "");
	/* Gets the actual animation and increses
	the coordinatesOnTexture value in 192*/
	DEBUG("move_right");
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);
	const int coordinates_on_texture_lower  = 192;/**Interger. Minimum
 	coordinate on texture constant */
	const int coordinates_on_texture_higher = 1728;/**Interger. Maximum
 	coordinate on texture constant */

	actual_animation->coordinatesOnTexture.first += coordinates_on_texture_lower;

	if(actual_animation->coordinatesOnTexture.first >= coordinates_on_texture_higher ) {
		/* If the coordinatesOnTexture is lower or equal to 1728 */
		INFO("coordinateOnTexture")

		/* Sets the coordinatesOnTexture to 0 */
		actual_animation->coordinatesOnTexture.first = 0;
	}
	else {
		/* Do nothing */
	}

	/* Makes the dark girl walk to the right direction */
	states.set_state("X_STATE", "LOOKING_RIGHT");
	set_actual_animation(animations["running_right_animation"]);
	play_song("steps");
	set_speed_x(0.1);

	if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_LEFT") {
		/* if the dark girl is jumping and looking left*/
		INFO("jumping and looking left")

		/* Turn the dark girl to the right and keep her jumping */
		states.set_state("X_STATE", "LOOKING_RIGHT");
		play_song("steps");
		set_actual_animation(animations["jumping_right_animation"]);
	}
	else {
		/* Do nothing */
	}
	DEBUG("move_right finished");
}

/**
 * @brief Method to walk left
 *
 * Method called when the girl needs to walk in the left direction
 *
 * @param actual_x_state if the girl is facing left or right
 * @param actual_y_state if the girl is jumping or falling
 *
 * @return void
 */
void DarkGirl::move_left(std::string actual_x_state,
						 std::string actual_y_state) {
	assert(actual_x_state != "");
	assert(actual_y_state != "");
	/* Gets the actual animation and decreases
	the coordinatesOnTexture value in 192*/
	DEBUG("move_left");
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);
	const int coordinates_on_texture_lower  = 192;/**Interger. Minimum
 	coordinate on texture constant */
	const int coordinates_on_texture_higher = 1536;/**Interger. Maximum
 	coordinate on texture constant */

	actual_animation->coordinatesOnTexture.first -= coordinates_on_texture_lower;

	if(actual_animation->coordinatesOnTexture.first <= 0) {
		/* if the coordinatesOnTexture is equal or lower than 0*/
		INFO("coordinatesOnTexture")

		/* Sets the coordinatesOnTexture equal to 1536 */
		actual_animation->coordinatesOnTexture.first = coordinates_on_texture_higher;
	}
	else {
		/* Do nothing */
	}

	/* Makes the dark girl walk to the left */
	states.set_state("X_STATE", "LOOKING_LEFT");
	set_actual_animation(animations["running_left_animation"]);
	play_song("steps");
	set_speed_x(-0.1);

	if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT") {
		/* if the dark girl is jumping and looking to the right */
		INFO("jumping and looking right")

		/* Turn the dark girl to the left and keep her jumping */
		states.set_state("X_STATE", "LOOKING_LEFT");
		play_song("steps");
		set_actual_animation(animations["jumping_left_animation"]);
	}
	else {
		/* Do nothing */
	}

	DEBUG("move_left finished");
}

/**
 * @brief Method for dark girl attack
 *
 * 	Method called for attack a game object
 *
 * @return void
 */
void DarkGirl::attack() {

	/* Gets the actual state of the dark girl on the axis X*/
	DEBUG("attack");
	std::string actual_x_state = "";
	actual_x_state = states.get_state("X_STATE");
	assert(actual_x_state != "");

	/* Sets states equal  attack */
	states.set_state("ACTION_STATE", "ATTACKING");

	if(actual_x_state == "LOOKING_RIGHT") {
		/* if the dark girl is looking to the right*/
		INFO("attack looking right")

		/* Makes dark girl attack looking right */
		set_actual_animation(animations["attacking_right_animation"]);
		get_actual_animation()->is_finished = false;
	}
	else if(actual_x_state == "LOOKING_LEFT") {
		/* if the dark girl is looking to the left*/
		INFO("attack looking left")
		/* Makes the dark girl attack looking left */
		set_actual_animation(animations["attacking_left_animation"]);
		get_actual_animation()->is_finished = false;
	}
	else {
		/*Do Nothing */
	}

	play_song("sword_attack");

	DEBUG("attack");
}

/**
 * @brief Event for attack
 *
 * Method called everytime an attack happens
 *
 * @param game_object
 *
 * @return void
 */
void DarkGirl::on_attack(GameObject *game_object) {
	DEBUG("on_attack")
	/* Gets the actual state on the X axis */
	std::string actual_x_state = states.get_state("X_STATE");
	assert(actual_x_state != "");

	/* Sets states equal to on attacking */
	states.set_state("ACTION_STATE", "ON_ATTACK");

	if(actual_x_state == "LOOKING_LEFT") {
		/* if the dark girl is looking left */
		INFO("get a hit from left")

		/* Makes the dark girl be attacked by the left */
		set_actual_animation(animations["on_attack_left_animation"]);
	}
	else if(actual_x_state == "LOOKING_RIGHT") {
		/* if the dark girl is looking right */
		INFO("get a hit from right")

		/* Makes the dark girl be attacked by the right */
		set_actual_animation(animations["on_attack_right_animation"]);
	}
	else {
		/*Do Nothing */
	}
	DEBUG("on_attack finished")
}

/**
 * @brief Update the state map
 *
 * update the state map of the dark girl
 *
 * @return void
 *
 */
void DarkGirl::update_state(){
	update_state_get_position();
	update_state_attacking();
	update_state_idle();
	update_state_on_ground();
}

/**
 * @brief Update the state map
 *
 * get the dark girl position to update state
 *
 * @return void
 *
 */
void DarkGirl::update_state_get_position() {
	DEBUG("update_state")
	/* Gets the actual animations */
	engine::Animation *actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);

	const int position_y_axis_minimum = 576; /** Minimum position
 	on the Y axis */

	if (get_position_y() >= position_y_axis_minimum) {
		/* if the position on the y axis is higher  or equal than 576*/
		INFO("position on the Y axis")

		/* Keep the dark girl alive */
		die(nullptr);
	} else {
		/* Do nothing */
	}
}

/**
 * @brief Update the state map
 *
 * update state when de dark girl is attacking or
 * being on attack
 *
 * @return void
 *
 */
void DarkGirl::update_state_attacking() {

	/* Gets the actual animations */
	engine::Animation *actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);

	/* Gets the actual action state of the dark girl */
	std::string actual_action_state = states.get_state("ACTION_STATE");

	if (actual_action_state == "ATTACKING"
		|| actual_action_state == "ON_ATTACK") {
		/*if the actual state is attack or beeing attacked */
		INFO("ATTACKING OR ON_ATTACK")

		if (get_actual_animation()->is_finished) {
			/* if the animation is finished */
			INFO("animation is finished")

			/* Sets the dark girl state to normal */
			states.set_state("ACTION_STATE", "NORMAL");
		}
			/* else do nothing */
		else {
			return;
		}
	} else {
		/* Do nothing */
	}
}

/**
 * @brief Update the state map
 *
 * get the dark girl standing position
 *
 * @return void
 *
 */
void DarkGirl::update_state_idle() {

	/* Gets the actual animations */
	engine::Animation *actual_animation = nullptr;
	actual_animation = get_actual_animation();
	assert(actual_animation != nullptr);

	/* Gets the actual state on the X axis */
	std::string actual_x_state = states.get_state("X_STATE");
	assert(actual_x_state != "");

	/* Gets the actual action state of the dark girl */
	std::string actual_action_state = states.get_state("ACTION_STATE");

	if (get_speed_x() == 0.0 && get_speed_y() == 0.0
		&& actual_action_state == "NORMAL") {
		/* if the dark girl is moving */
		INFO("dark girl is moving")

		if (actual_x_state == "LOOKING_RIGHT") {
			/* if the dark girl is looking right */
			INFO("dark girl is looking right")

			/* Makes she stand looking right */
			set_actual_animation(animations["idle_right_animation"]);
		} else if (actual_x_state == "LOOKING_LEFT") {
			/* else if the dark girl is looking left */
			INFO("dark girl is looking left")

			/* Makes she stand looking left */
			set_actual_animation(animations["idle_left_animation"]);
		} else {
			/*Do Nothing */
		}

		/* Sets the jumping_animation_count equal to 0*/
		jumping_animation_count = 0;
	} else {
		/*Do Nothing */
	}
}

/**
 * @brief Update the state map
 *
 * check the state of the dark girl on the Y axis
 *
 * @return void
 *
 */
void DarkGirl::update_state_on_ground(){
		/* Gets the actual animations */
		engine::Animation *actual_animation = nullptr;
		actual_animation = get_actual_animation();
		assert(actual_animation != nullptr);


		/* Gets the actual state on the Y axis */
		std::string actual_y_state = states.get_state("Y_STATE");
		assert(actual_y_state != "");

	if(get_speed_y() == 0.0 && get_state("Y_STATE") != "JUMPING") {
		/* if the dark girl has no speed in the y axis
		and she is not jumping  */
		INFO("dark girl on ground")
		/* Sets the dark girl on the ground */
		states.set_state("Y_STATE", "ON_GROUND");
	}
	else if(get_speed_y() == 0.0) {
		/* else if the dark girl has no speed
	on the y axis and she is jumping */
		INFO("dark girl falling")

		/* Sets the dark girl to state of falling */
		states.set_state("Y_STATE", "FALLING");
	}
	else {
		/*Do Nothing */
	}

	/* Sets new coordinates to the dark girl and
	sets speed on the x axis equal to 0*/
	set_position_x(get_position_x() - get_speed_x());
	set_speed_x(0.0);
	DEBUG("update_state finished")
}

/**
 * @brief Death Method
 *
 * Method for the death of the dark girl
 *
 * @param game_object dark girl
 *
 * @return void
 */
void DarkGirl::die(engine::GameObject *game_object) {

	/* Gets the actual state of the dark Girl */
	DEBUG("die");
	std::string actual_x_state = get_state("X_STATE");


	if(actual_x_state == "LOOKING_LEFT") {
		/* If dark girl is dying looking left  */
		INFO("Dark girl is dying looking left")

		/* Sets the animation of the dark girl dying left */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_left_animation"]);
	}
	else if(actual_x_state == "LOOKING_RIGHT") {
		/* If dark girl is dying looking right */
		INFO("Dark girl is dying looking right")

		/* Sets the animation of the dark girl dying right */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_right_animation"]);
	}
	else {
		/*Do Nothing */
	}

	assert(actual_x_state != "");
	sleep(1);

	DEBUG("die finished");
}
