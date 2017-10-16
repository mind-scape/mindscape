/**
 * @file dark_girl.cpp
 * @brief Purpose: Contains dark girl methods and attributes
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "../include/dark_girl.hpp"
#include "../include/platform.hpp"
#include "../include/scorpion.hpp"
#include "../include/goop.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/log.hpp"
#include "level_factory.hpp"
#include <typeinfo>
#include <algorithm>
#include <unistd.h>

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
	initialize_hitboxes();
	initialize_animations();
	initialize_audio_effects();
	initialize_as_physicable();
};

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
 * @brief Initializes hitboxes for dark girl
 *
 * Initializes dark girl instance hitboxes
 *
 * @return void
 *
 */
void DarkGirl::initialize_hitboxes() {
	DEBUG("initialize_hitboxes");
	/* Get actual state of the game */
	engine::Game& game = engine::Game::get_instance();

	/* Creates Dark Girl Hitbox*/
	engine::Hitbox* hitbox = nullptr;
	hitbox = new engine::Hitbox(
			"hitbox",
			get_position(),
			std::make_pair(60, 45),
			std::make_pair(50,130),
			game.get_renderer()
	);

	/* Add component in the game */
	add_component(hitbox);

	/* Creates Dark Girl Hitbox on footer*/
	engine::Hitbox* footer = nullptr;
	footer = new engine::Hitbox(
			"footer",
			get_position(),
			std::make_pair(60, 180),
			std::make_pair(50, 20),
			game.get_renderer()
	);

	/* Add component in the game */
	add_component(footer);

	DEBUG("initialize_hitboxes finished");
}

/**
 * @brief Initializes audio effects
 *
 * Initializes audio effects for dark girl on second level
 *
 * @return void
 *
 */
void DarkGirl::initialize_audio_effects() {
	DEBUG("initialize_audio_effects");

	/* Initializes Audio effects while the Dark GIrl is Walking*/
	DEBUG("little_girl_steps")
	engine::Audio * little_girl_steps = nullptr;
	little_girl_steps = new engine::Audio(
			"steps",
			"../assets/audios/effects_songs/menina_passos_rapido.wav",
			engine::Audio::CHUNK
	);

	little_girl_steps->set_duration(1);
	little_girl_steps->set_effect_volume(45);
	add_component(little_girl_steps);

	/* Initializes Audio effects while the Dark GIrl is getting a hit*/
	DEBUG("little_gitl_getting_hit")
	engine::Audio * little_girl_getting_hit = nullptr;
	little_girl_getting_hit = new engine::Audio(
			"hit_me",
			"../assets/audios/effects_songs/menina_apanhando.wav",
			engine::Audio::CHUNK
	);

	little_girl_getting_hit->set_duration(0.5);
	add_component(little_girl_getting_hit);

	/* Initializes Audio effects while the Dark GIrl is Attacking*/
	DEBUG("sword_song")
	engine::Audio * sword_song = nullptr;
	sword_song = new engine::Audio(
			"sword_attack",
			"../assets/audios/effects_songs/espada_fase_1.wav",
			engine::Audio::CHUNK
	);
	sword_song->set_duration(0.5);
	add_component(sword_song);

	DEBUG("initialize_audio_effects finished");
}

/**
 * @brief Initializes dark girl animations
 *
 * Initializes animations for dark girl in second level
 *
 * @return void
 */
void DarkGirl::initialize_animations() {
	DEBUG("initialize_animations");

	/* Initializes animation of the Dark Girl running right */
	DEBUG("running_right_animation");
	engine::Animation* running_right_animation = nullptr;
	running_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_running_right.png",
			1, 9, 0.9, "RIGHT"
	);
	add_animation("running_right_animation", running_right_animation);

	/* Initializes animation of the Dark Girl running left */
	DEBUG("running_left_animation");
	engine::Animation* running_left_animation = nullptr;
	running_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_running_left.png",
			1, 9, 0.9, "LEFT"
	);
	add_animation("running_left_animation", running_left_animation);

	/* Initializes animation of the Dark Girl standing looking right */
	DEBUG("idle_right_animation");
	engine::Animation* idle_right_animation = nullptr;
	idle_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_idle_right.png",
			1, 10, 1.5, "RIGHT"
	);
	add_animation("idle_right_animation", idle_right_animation);

	/* Initializes animation of the Dark Girl standing looking left */
	DEBUG("idle_left_animation");
	engine::Animation* idle_left_animation = nullptr;
	idle_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_idle_left.png",
			1, 10, 1.5, "LEFT"
	);
	add_animation("idle_left_animation", idle_left_animation);

	/* Initializes animation of the Dark Girl jumping to the right */
	DEBUG("jumping_right_animation");
	engine::Animation* jumping_right_animation = nullptr;
	jumping_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_jumping_right.png",
			1, 5, 1.5, "RIGHT"
	);
	add_animation("jumping_right_animation", jumping_right_animation);

	/* Initializes animation of the Dark Girl jumping to the left */
	DEBUG("jumping_left_animation");
	engine::Animation* jumping_left_animation = nullptr;
	jumping_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_jumping_left.png",
			1, 5, 1.5, "LEFT"
	);
	add_animation("jumping_left_animation", jumping_left_animation);

	/* Initializes animation of the Dark Girl attacking to the right */
	DEBUG("attacking_right_animation");
	engine::Animation* attacking_right_animation = nullptr;
	attacking_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_attacking_right.png",
			1, 5, 0.5, "RIGHT"
	);
	attacking_right_animation->in_loop = false;
	add_animation("attacking_right_animation", attacking_right_animation);

	/* Initializes animation of the Dark Girl attacking to the left */
	DEBUG("attacking_left_animation");
	engine::Animation* attacking_left_animation = nullptr;
	attacking_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_attacking_left.png",
			1, 5, 0.5, "LEFT"
	);
	attacking_left_animation->in_loop = false;
	add_animation("attacking_left_animation", attacking_left_animation);

	/* Initializes animation of the Dark Girl
		when she was sying looking to the left */
	DEBUG("dying_left_animation");
	engine::Animation* dying_left_animation = nullptr;
	dying_left_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_dying_left.png",
			1, 5, 0.8, "LEFT"
	);

	dying_left_animation->in_loop = false;
	dying_left_animation->is_a_final_animation = true;
	add_animation("dying_left_animation", dying_left_animation);

	/* Initializes animation of the Dark Girl
		when she was sying looking to the right */
	DEBUG("dying_right_animation");
	engine::Animation* dying_right_animation = nullptr;
	dying_right_animation = create_animation(
			"../assets/images/sprites/dark_girl/dark_girl_dying_right.png",
			1, 5, 1.0, "RIGHT"
	);

	dying_right_animation->in_loop = false;
	dying_right_animation->is_a_final_animation = true;
	add_animation("dying_right_animation", dying_right_animation);

	/* Initializes animation of the Dark Girl
		when she is standing */
	idle_right_animation->activate();
	set_actual_animation(idle_right_animation);

	DEBUG("initialize_animations finished");
}

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

	engine::Game& game = engine::Game::get_instance();


	/* Creates and initializes the object of the Dark GIrl */
	engine::Animation* animation = nullptr;
	animation = new engine::Animation(
			game.get_renderer(),
			image_path,
			// is_active
			false,
			// displacement
			std::make_pair(0, 0),
			// priority
			1,
			sprite_lines,
			sprite_columns,
			duration,
			// in_loop
			true,
			direction
	);

	/* Set dimentions on screen and, coordinates and dimention on texture  */
	animation->set_values(
			std::make_pair(192, 192),
			std::make_pair(192, 192),
			std::make_pair(0, 0)
	);

	DEBUG("create_animation finished");

	return animation;
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


	/* Gets instances of the Enemies */
	Platform* platform = nullptr;
	platform = dynamic_cast<Platform *>(other);

	Scorpion* scorpion = nullptr;
	scorpion = dynamic_cast<Scorpion *>(other);
	Spider* spider = nullptr;
	spider = dynamic_cast<Spider *>(other);

	Goop* goop = nullptr;
	goop = dynamic_cast<Goop *>(other);

	engine::Hitbox* my_hitbox = nullptr;
	my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox* other_hitbox = nullptr;
	other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

	//if she is falling on a platform
	if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "footer") {
		INFO("She is falling on a platform")
		set_speed_y(0.0);
		set_position_y(other_hitbox->get_coordinates().second - 180);
	}

	/* if the scorpion is attacking the dark girl */
	if(scorpion &&
	   scorpion->get_state("ACTION_STATE") == "ATTACKING" &&
	   other_hitbox->get_name() == "scorpion_attack" &&
	   scorpion->get_actual_animation()->actual_column == 1) {
		INFO("Scorpion is attacking")

		/* Makes dark girl be hit and play sound effects */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}

	/*if the spider is attacking the dark girl*/
	if(spider &&
	   spider->get_state("ACTION_STATE") == "ATTACKING" &&
	   other_hitbox->get_name() == "spider_attack" &&
	   spider->get_actual_animation()->actual_column == 3) {
		INFO("Spider is attacking")

		/* Makes dark girl be hit and play sound effects */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}


	/* if the goop is on the dark girl direction */
	if(goop) {
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

			/*Makes dark girl be hit and play sound effects */
		else {
			INFO("Dark girl get a hit")
			play_song("hit_me");
			on_attack(other);
			hit(other,1);
		}
	}

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
	std::string actual_x_state = "";
	actual_x_state = get_state("X_STATE");

	/* If dark girl is dying looking left  */
	if(actual_x_state == "LOOKING_LEFT") {
		INFO("Dark girl is dying looking left")

		/* Sets the animation of the dark girl dying left */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_left_animation"]);
	}

	/* If dark girl is dying looking right */
	else if(actual_x_state == "LOOKING_RIGHT") {
		INFO("Dark girl is dying looking right")

		/* Sets the animation of the dark girl dying right */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_right_animation"]);
	}


	sleep(1);

	DEBUG("die finished");
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

	/* Gets the name of the game event */
	std::string event_name = "";
	event_name = game_event.game_event_name;

	/* Gets the actual animation of the dark girl  */
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();

	/* Gets x coordinates of the game event */
	std::string actual_x_state = "";
	actual_x_state = states.get_state("X_STATE");

	/* Gets y coordinates of the game event */
	std::string actual_y_state = "";
	actual_y_state = states.get_state("Y_STATE");

	/* Gets the action state of the game event */
	std::string actual_action_state = "";
	actual_action_state = states.get_state("ACTION_STATE");

	/* if the event is jump and the dark girl is on groun */
	if(event_name == "JUMP" && actual_y_state == "ON_GROUND") {
		INFO("dark girl jump and she is on ground")

		/* Makes the dark girl jump */
		jump(actual_x_state);
	}

	/* else if the event is move left */
	else if(event_name == "MOVE_LEFT") {
		INFO("dark girl move left")
		/* Makes the dark girl move left*/
		move_left(actual_x_state, actual_y_state);
	}

	/* else if the event is move right */
	else if(event_name == "MOVE_RIGHT") {
		INFO("dark girl move right")
		/*Makes the dark girl move right*/
		move_right(actual_x_state, actual_y_state);
	}

	/* if the event is attack and the actual state is different from attacking */
	else if(event_name == "ATTACK" && actual_action_state != "ATTACKING") {
		INFO("attack event")
		/*Makes the dark girl attack*/
		attack();
	}

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

	/*if the states of the dark girl on y axis is
	 different from jumping or falling */
	DEBUG("jump");

	if(get_state("Y_STATE") != "JUMPING" || get_state("Y_STATE") != "FALLING") {
		INFO("dark girl jump")

		/* Makes the dark girl jump */
		set_speed_y(-23);
		states.set_state("Y_STATE", "JUMPING");

		/*If the the state of the dark girl is looking right */
		if(actual_x_state == "LOOKING_RIGHT") {
			INFO("jump to the right")

			/*Stop sound effects of walking and starts the animation of
			  jumping to the right direction */
			stop_song("steps");
			set_actual_animation(animations["jumping_right_animation"]);
		}

		/* else if the state of the dark girl is looking to the left*/
		else if(actual_x_state == "LOOKING_LEFT") {
			INFO("jump to the left")

			/*Stop sound effects of walking and starts the animation of
			  jumping to the left direction */
			stop_song("steps");
			set_actual_animation(animations["jumping_left_animation"]);
		}

		/* Gets the actual animation and increments
		jumping_animation_count value */

		engine::Animation* actual_animation = nullptr;
		actual_animation = get_actual_animation();

		jumping_animation_count += 1;

		/* If the jumping_animation_count has value lower than 26 */
		if(jumping_animation_count < 26) {
			INFO("jumping_animation_count value")

			/* If the jumping_animation_count is divisible by 5 */
			if(jumping_animation_count % 5 == 0) {
				INFO("jumping_animation_count divisible")

				/* Increment the value of the coordinates */
				actual_animation->coordinatesOnTexture.first += 192;

				/*if the cordinate on the y axis is lower than 960 */
				if(actual_animation->coordinatesOnTexture.first == 960) {
					INFO("cordinate on the Y axis")

					/* Sets coordinatesOnTexture to 0 */
					actual_animation->coordinatesOnTexture.first = 0;
				}
			}
		}

		/* else jumping_animation_count is higher than 25 */
		else {

			/* Sets the jumping_animation_count to 26*/
			jumping_animation_count = 26;
		}
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

	/* Gets the actual animation and increses
	the coordinatesOnTexture value in 192*/
	DEBUG("move_right");
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();

	actual_animation->coordinatesOnTexture.first += 192;

	/* If the coordinatesOnTexture is lower or equal to 1728 */
	if(actual_animation->coordinatesOnTexture.first >= 1728) {
		INFO("coordinateOnTexture")

		/* Sets the coordinatesOnTexture to 0 */
		actual_animation->coordinatesOnTexture.first = 0;
	}

	/* Makes the dark girl walk to the right direction */
	states.set_state("X_STATE", "LOOKING_RIGHT");
	set_actual_animation(animations["running_right_animation"]);
	play_song("steps");
	set_speed_x(0.1);

	/* if the dark girl is jumping and looking left*/
	if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_LEFT") {
		INFO("jumping and looking left")

		/* Turn the dark girl to the right and keep her jumping */
		states.set_state("X_STATE", "LOOKING_RIGHT");
		play_song("steps");
		set_actual_animation(animations["jumping_right_animation"]);
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

	/* Gets the actual animation and decreases
	the coordinatesOnTexture value in 192*/
	DEBUG("move_left");
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();

	actual_animation->coordinatesOnTexture.first -= 192;

	/* if the coordinatesOnTexture is equal or lower than 0*/
	if(actual_animation->coordinatesOnTexture.first <= 0) {
		INFO("coordinatesOnTexture")

		/* Sets the coordinatesOnTexture equal to 1536 */
		actual_animation->coordinatesOnTexture.first = 1536;
	}

	/* Makes the dark girl walk to the left */
	states.set_state("X_STATE", "LOOKING_LEFT");
	set_actual_animation(animations["running_left_animation"]);
	play_song("steps");
	set_speed_x(-0.1);

	/* if the dark girl is jumping and looking to the right */
	if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT") {
		INFO("jumping and looking right")

		/* Turn the dark girl to the left and keep her jumping */
		states.set_state("X_STATE", "LOOKING_LEFT");
		play_song("steps");
		set_actual_animation(animations["jumping_left_animation"]);
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

	/* Sets states equal  attack */
	states.set_state("ACTION_STATE", "ATTACKING");

	/* if the dark girl is looking to the right*/
	if(actual_x_state == "LOOKING_RIGHT") {
		INFO("attack looking right")

		/* Makes dark girl attack looking right */
		set_actual_animation(animations["attacking_right_animation"]);
		get_actual_animation()->is_finished = false;
	}

	/* if the dark girl is looking to the left*/
	else if(actual_x_state == "LOOKING_LEFT") {
		INFO("attack looking left")
		/* Makes the dark girl attack looking left */
		set_actual_animation(animations["attacking_left_animation"]);
		get_actual_animation()->is_finished = false;
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

	/* Gets the actual state on the X axis */
	std::string actual_x_state = "";
	actual_x_state = states.get_state("X_STATE");

	/* Sets states equal to on attacking */
	states.set_state("ACTION_STATE", "ON_ATTACK");

	/* if the dark girl is looking left */
	if(actual_x_state == "LOOKING_LEFT") {
		INFO("get a hit from left")

		/* Makes the dark girl be attacked by the left */
		set_actual_animation(animations["on_attack_left_animation"]);
	}

	/* if the dark girl is looking right */
	else if(actual_x_state == "LOOKING_RIGHT") {
		INFO("get a hit from right")

		/* Makes the dark girl be attacked by the right */
		set_actual_animation(animations["on_attack_right_animation"]);
	}

}

/**
 * @brief Update the state map
 *
 * Updates the states on the state map
 *
 * @return void
 *
 */
void DarkGirl::update_state() {

	/* Gets the actual animations */
	engine::Animation* actual_animation = nullptr;
	actual_animation = get_actual_animation();

	/* Gets the actual state on the X axis */
	std::string actual_x_state = "";
	actual_x_state = states.get_state("X_STATE");

	/* Gets the actual state on the Y axis */
	std::string actual_y_state = "";
	actual_y_state = states.get_state("Y_STATE");

	/* Gets the actual action state of the dark girl */
	std::string actual_action_state = states.get_state("ACTION_STATE");

	/* if the position on the y axis is higher  or equal than 576*/
	if(get_position_y() >= 576) {
		INFO("position on the Y axis")

		/* Keep the dark girl alive */
		die(NULL);
	}

	/*if the actual state is attack or beeing attacked */
	if(actual_action_state == "ATTACKING"
	   || actual_action_state == "ON_ATTACK") {
		INFO("ATTACKING OR ON_ATTACK")

		/* if the animation is finished */
		if(get_actual_animation()->is_finished) {
			INFO("animation is finished")

			/* Sets the dark girl state to normal */
			states.set_state("ACTION_STATE", "NORMAL");
		}

		/* else do nothing */
		else {
			return;
		}
	}

	/* if the dark girl is moving */
	if(get_speed_x() == 0.0 && get_speed_y() == 0.0
	   && actual_action_state == "NORMAL") {
		INFO("dark girl is moving")

		/* if the dark girl is looking right */
		if(actual_x_state == "LOOKING_RIGHT") {
			INFO("dark girl is looking right")

			/* Makes she stand looking right */
			set_actual_animation(animations["idle_right_animation"]);
		}

		/* else if the dark girl is looking left */
		else if(actual_x_state == "LOOKING_LEFT") {
			INFO("dark girl is looking left")

			/* Makes she stand looking left */
			set_actual_animation(animations["idle_left_animation"]);
		}

		/* Sets the jumping_animation_count equal to 0*/
		jumping_animation_count = 0;
	}

	/* if the dark girl has no speed in the y axis
	 and she is not jumping  */
	if(get_speed_y() == 0.0 && get_state("Y_STATE") != "JUMPING") {
		INFO("dark girl on ground")
		/* Sets the dark girl on the ground */
		states.set_state("Y_STATE", "ON_GROUND");
	}

	/* else if the dark girl has no speed
	on the y axis and she is jumping */
	else if(get_speed_y() == 0.0) {
		INFO("dark girl falling")

		/* Sets the dark girl to state of falling */
		states.set_state("Y_STATE", "FALLING");
	}

	/* Sets new coordinates to the dark girl and
	 sets speed on the x axis equal to 0*/
	set_position_x(get_position_x() - get_speed_x());
	set_speed_x(0.0);

}
