/**
 * @file little_girl.cpp
 * @brief Purpose: Contains methods to little_girl class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include "../include/scorpion.hpp"
#include "../include/goop.hpp"
#include "../engine/include/game.hpp"
#include "level_factory.hpp"
#include <typeinfo>
#include <algorithm>
#include <unistd.h>

using namespace mindscape;

/**
 * @brief Constructor for the little girl
 *
 * @param name Name of the object
 * @param position Pair of integers with x and y position
 * @param priority Integer representing its priority on rendering
 *
 * @return void
 */
LittleGirl::LittleGirl(
		std::string name,
		std::pair<int, int> position,
		int priority)
		: engine::GameObject(
		name,
		position,
		priority,
		{
				{engine::KeyboardEvent::LEFT,  "MOVE_LEFT"},
				{engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"},
				{engine::KeyboardEvent::UP,    "JUMP"},
				{engine::KeyboardEvent::DOWN,  "CROUCH"},
				{engine::KeyboardEvent::F,     "ATTACK"},
		}
), Fighter(90) {
	
	/* Inicialize all the characterists of the Little Girl */
	initialize_state_map();
	initialize_hitboxes();
	initialize_animations();
	initialize_audio_effects();
	initialize_as_physicable();
};

/**
 * @brief Initialize all states map
 *
 * @return void
 */
void LittleGirl::initialize_state_map() {
	/* Sets initial position of the Little Girl in the game, also her action
		state */ 
	states.set_state("X_STATE", "LOOKING_RIGHT");
	states.set_state("Y_STATE", "FALLING");
	states.set_state("ACTION_STATE", "NORMAL");
}

/**
 * @brief Initialize all hitboxes
 *
 * @return void
 */
void LittleGirl::initialize_hitboxes() {

	/* Gets actual state of the game */
	engine::Game &game = engine::Game::get_instance();

	/* Creates Little Girl's hitbox */
	engine::Hitbox *hitbox = new engine::Hitbox(
			"hitbox", /* Hitbox's name */
			get_position(), /* Little Girl's coordinate */
			std::make_pair(60, 45), /* Hitbox's displacement */
			std::make_pair(50, 130), /* Hitbox's dimentions */
			game.get_renderer() /* Gets Renderer */
	);
	
	/* Creates Little Girl's hitbox on footer */
	engine::Hitbox *footer = new engine::Hitbox(
			"footer", /* Hitbox's name */
			get_position(), /* Little Girl's coordinate */
			std::make_pair(60, 180), /* "Footer" Hitbox's displacement */
			std::make_pair(50, 20), /* "Footer" Hitbox's dimentions */
			game.get_renderer() /* Gets Renderer */
	);
	
	/* Adds both components in game */
	add_component(hitbox);
	add_component(footer);
}

/**
 * @brief Initialize all audio effects
 *
 * @return void
 */
void LittleGirl::initialize_audio_effects() {
	
	/* Initiates sound effect while the Litte Girl is walking */
	engine::Audio *little_girl_steps = new engine::Audio(
			"steps",
			"../assets/audios/effects_songs/menina_passos_rapido.wav",
			engine::Audio::CHUNK);
	little_girl_steps->set_duration(1);
	little_girl_steps->set_effect_volume(45);
	add_component(little_girl_steps);

	/* Initiates sound effect while the Litte Girl is been hit */
	engine::Audio *little_girl_getting_hit = new engine::Audio(
			"hit_me",
			"../assets/audios/effects_songs/menina_apanhando.wav",
			engine::Audio::CHUNK);
	little_girl_getting_hit->set_duration(0.5);
	add_component(little_girl_getting_hit);

	/* Initiates sound effect while the Litte Girl is using the sword */
	engine::Audio *sword_song = new engine::Audio(
			"sword_attack",
			"../assets/audios/effects_songs/espada_fase_1.wav",
			engine::Audio::CHUNK);
	sword_song->set_duration(0.4);
	add_component(sword_song);
}

/**
 * @brief Initialize all animations
 *
 * @return void
 */
void LittleGirl::initialize_animations() {

	/* Initiates animation of the Litte Girl's running to right */
	engine::Animation *running_right_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_running_right.png",
		1, 9, 0.9, "RIGHT"
	);
	add_animation("running_right_animation", running_right_animation);

	/* Initiates animation of the Litte Girl's running to left */
	engine::Animation *running_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_running_left.png",
		1, 9, 0.9, "LEFT"
	);
	add_animation("running_left_animation", running_left_animation);

	/* Initiates animation of the Litte Girl's standing looking right */
	engine::Animation *idle_right_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_idle_right.png",
		1, 10, 1.5, "RIGHT"
	);
	add_animation("idle_right_animation", idle_right_animation);

	/* Initiates animation of the Litte Girl's standing looking left */
	engine::Animation *idle_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_idle_left.png",
		1, 10, 1.5, "LEFT"
	);
	add_animation("idle_left_animation", idle_left_animation);

	/* Initiates animation of the Litte Girl's jumping to right */
	engine::Animation *jumping_right_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_jumping_right.png",
		1, 5, 1.5, "RIGHT"
	);
	add_animation("jumping_right_animation", jumping_right_animation);

	/* Initiates animation of the Litte Girl's jumping to left */
	engine::Animation *jumping_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_jumping_left.png",
		1, 5, 1.5, "LEFT"
	);
	add_animation("jumping_left_animation", jumping_left_animation);

	/* Initiates animation of the Litte Girl's attacking on right direction */
	engine::Animation *attacking_right_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_attacking_right.png",
		1, 5, 0.4, "RIGHT"
	);
	add_animation("attacking_right_animation", attacking_right_animation);

	/* Initiates animation of the Litte Girl's attacking on left direction */
	engine::Animation *attacking_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_attacking_left.png",
		1, 5, 0.4, "LEFT"
	);
	add_animation("attacking_left_animation", attacking_left_animation);

	/* Initiates animation of the Litte Girl when She's been attacking in right */
	engine::Animation *on_attack_right_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_on_attack_right.png",
		1, 3, 0.8, "RIGHT"
	);
	add_animation("on_attack_right_animation", on_attack_right_animation);

	/* Initiates animation of the Litte Girl when She's been attacking in left */
	engine::Animation *on_attack_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_on_attack_left.png",
		1, 3, 0.8, "LEFT"
	);
	add_animation("on_attack_left_animation", on_attack_left_animation);

	/* Initiates animation of the Litte Girl when She's dying looking to left*/
	engine::Animation *dying_left_animation = create_animation(
		"../assets/images/sprites/little_girl/little_girl_dying_left.png",
		1, 5, 0.8, "LEFT"
	);
	add_animation("dying_left_animation", dying_left_animation);
	dying_left_animation->in_loop = false;
	dying_left_animation->is_a_final_animation = true;

	/* Initiates animation of the Litte Girl when She's dying looking to right */
	engine::Animation *dying_right_animation = create_animation(
			"../assets/images/sprites/little_girl/little_girl_dying_right.png",
			1, 5, 1.0, "RIGHT"
	);
	dying_right_animation->in_loop = false;
	dying_right_animation->is_a_final_animation = true;
	add_animation("dying_right_animation", dying_right_animation);

	/* Initiates Little Girl animation when She's standing */
	idle_right_animation->activate();
	set_actual_animation(idle_right_animation);
}

/**
 * @brief Creates an animation
 *
 * Creates an animations for the little girl
 *
 * @params path File path to the image which contains the spritesheet
 * @params sprite_lines Number of lines on the spritesheet
 * @params sprite_columns Number of columns on the spritesheet
 * @params duration Time duration of the animation
 * @params direction Direction (left or right) of the animation
 *
 * @return The animation created
 */
engine::Animation *LittleGirl::create_animation(
		std::string path,
		int sprite_lines,
		int sprite_columns,
		double duration,
		std::string direction) {
	
	engine::Game &game = engine::Game::get_instance(); /* Gets game instance */
	
	/* Creates an animation Object of the Little Girl */
	engine::Animation *animation = new engine::Animation(
			game.get_renderer(),
			path,               
			false,             
			std::make_pair(0, 0),
			1,                
			sprite_lines,         
			sprite_columns,       
			duration,         
			true,            
			direction          
	);
	
	/* Set dimentions on screen and, coordinates and dimention on texture  */
	animation->set_values(
			std::make_pair(192, 192),
			std::make_pair(192, 192),
			std::make_pair(0, 0)
	);
	
	return animation;
}

/**
 * @brief Initialize the object as physicable
 *
 * This makes the object vulnerable to collisions and forces like gravity
 *
 * @return void
 */
void LittleGirl::initialize_as_physicable() {

	/* Gets Physics object and makes Little Girl collidable */
	engine::Physics *physics = engine::Physics::get_instance();
	physics->add_physicable(this);
	collidable = true;
}

/**
 * @brief On collision event
 *
 * Method called everytime a collision happens
 *
 * @param other The other object which collided
 * @param p_my_hitbox This object hitbox which received the collision
 * @param p_other_hitbox The other object hitbox which provided the collision
 */
void LittleGirl::on_collision(
		engine::GameObject *other,
		engine::Hitbox *p_my_hitbox,
		engine::Hitbox *p_other_hitbox) {
	
	/* Gets instances of the Enemies */
	Platform *platform = dynamic_cast<Platform *>(other);
	Scorpion *scorpion = dynamic_cast<Scorpion *>(other);
	Spider *spider = dynamic_cast<Spider *>(other);
	Goop *goop = dynamic_cast<Goop *>(other);
	engine::Hitbox *my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
	engine::Hitbox *other_hitbox = 
			dynamic_cast<engine::Hitbox *>(p_other_hitbox);
	
	if (get_speed_y() >= 0 && platform && my_hitbox->get_name() == "footer") { 
	/* If she is falling on a platform */

		set_speed_y(0.0);
		set_position_y(other_hitbox->get_coordinates().second - 180);
	}
	
	if (scorpion &&
		scorpion->get_state("ACTION_STATE") == "ATTACKING" &&
		other_hitbox->get_name() == "scorpion_attack" &&
		scorpion->get_actual_animation()->actual_column == 1) {
	/* If the scorpion is attacking the Little Girl */

		/* Makes the Little Girl be hit and plays the sound effect */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}
	
	if (spider &&
		spider->get_state("ACTION_STATE") == "ATTACKING" &&
		other_hitbox->get_name() == "spider_attack" &&
		spider->get_actual_animation()->actual_column == 3) {
	/* If the spider is attacking the Little Girl */

		/* Makes the Little Girl be hit and plays the sound effect */
		play_song("hit_me");
		on_attack(other);
		hit(other, 1);
	}
	
	if (goop) {
	/* If the goop is coming to the Little Girl's direction */

		if (get_state("ACTION_STATE") == "ATTACKING" && 
			goop->get_state("ACTION_STATE") != "REFUTED") {
		/* If the goop has been refuted by the Girl */

			/* Makes the goop be refuted */
			goop->set_speed_x(goop->get_speed_x() * (-1));
			goop->set_speed_y(-10);
			goop->set_actual_animation(
				goop->animations["refuted_goop_animation"]
			);
			goop->states.set_state("ACTION_STATE", "REFUTED");
		} 

		else if (get_state("ACTION_STATE") != "ATTACKING") {
		/* If the goop hits the Girl */
			
			/* Makes the Little Girl be hit and plays the sound effect */
			play_song("hit_me");
			on_attack(other);
			hit(other, 1);
		}
	}
}

/**
 * @brief Method for dying
 *
 * This method is called when the little girl must die
 *
 * @param game_object
 */
void LittleGirl::die(engine::GameObject *game_object) {
	std::string actual_x_state = get_state("X_STATE");
	
	if (actual_x_state == "LOOKING_LEFT") {
	/* If the Little Girl is dying looking left */

		/* Sets the animation of the Little Girl dying looking left */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_left_animation"]);
	} 

	else if (actual_x_state == "LOOKING_RIGHT") {
	/* If the Little Girl is dying looking right */

		/* Sets the animation of the Little Girl dying looking right */
		states.set_state("ACTION_STATE", "DYING");
		set_actual_animation(animations["dying_right_animation"]);
	}
	
	/* Creates "level" of Game over */
	LevelFactory *level_factory = new LevelFactory();
	engine::Game *game = &(engine::Game::get_instance());
	level_factory->update_level(
			dynamic_cast<engine::Level *>(game->get_actual_scene()),
			"../data/game_over.dat"
	);
	
	/* Pauses the game */
	game->set_state(engine::Game::PAUSED);
}

/**
 * @brief Registers an event
 *
 * This method receives an event and registers it
 *
 * @param game_event The event to be registered
 *
 * @return void
 */
void LittleGirl::on_event(GameEvent game_event) {

	std::string event_name = game_event.game_event_name; /* Gets name of the 
	game event */
	std::string actual_x_state = states.get_state("X_STATE"); /* Gets x 
	coordinates of the game event */
	std::string actual_y_state = states.get_state("Y_STATE"); /* Gets y 
	coordinates of the game event */
	std::string actual_action_state = states.get_state("ACTION_STATE"); /* Gets  
	action state of the game event */
	
	if (event_name == "JUMP" && actual_y_state == "ON_GROUND") {
	/* If the event is JUMP and the girl is on ground */

		/* Makes the Girl jump */
		jump(actual_x_state);
	} 

	else if (event_name == "MOVE_LEFT") {
	/* If the event is MOVE LEFT */

		/* Makes the Girl move to the left */
		move_left(actual_x_state, actual_y_state);
	}

	else if (event_name == "MOVE_RIGHT") {
	/* If the event is MOVE RIGHT */

		/* Makes the Girl move to the right */
		move_right(actual_x_state, actual_y_state);
	}

	else if (event_name == "ATTACK" && actual_action_state != "ATTACKING") {
	/* If the event is ATTACK and the action state is diffrent from ATTACKING */

		/* Makes the Girl attack */
		attack();
	}
}

/**
 * @brief Method for jumping
 *
 * Method called when the character must jump
 *
 * @param actual_x_state If the girl is jumping, falling, to the right, etc.
 *
 * @return void
 */
void LittleGirl::jump(std::string actual_x_state) {
	if (get_state("Y_STATE") != "JUMPING" 
		|| get_state("Y_STATE") != "FALLING") {
	/* If the state in y axis is different from JUMPING or FALLING */

		/* Makes Little Girl jump */
		set_speed_y(-23);
		states.set_state("Y_STATE", "JUMPING");
		
		if (actual_x_state == "LOOKING_RIGHT") {
		/* If in x axis the Little Girl is looking to the right */

			/* Stops "steps" sound effect and set jump animation */
			stop_song("steps");
			set_actual_animation(animations["jumping_right_animation"]);
		} 

		else if (actual_x_state == "LOOKING_LEFT") {
		/* If in x axis the Little Girl is looking to the left */

			/* Stops "steps" sound effect and set jump animation */
			stop_song("steps");
			set_actual_animation(animations["jumping_left_animation"]);
		}

		/* Gets actual animation and increments jump_animation_count value */
		engine::Animation *actual_animation = get_actual_animation();
		jumping_animation_count += 1;

		if (jumping_animation_count < 26) {
		/* If jump_animation_count has value equal or lower than 25 */
			
			if (jumping_animation_count % 5 == 0) {
			/* If jump_animation_count value is divisible for 5 */
			
				/* Increases value of coordinatesOnTexture */	
				actual_animation->coordinatesOnTexture.first += 192;
				
				if (actual_animation->coordinatesOnTexture.first == 960) {
				/* If jump_animation_count value is equal 960 */
			
					/* Sets coordinatesOnTexture equal zero */	
					actual_animation->coordinatesOnTexture.first = 0;
				}
			}
		}

		else {
		/* if jumping_animation_count is higher than 25 */
			
			/* Makes jumping_animation_count value equal 26 */
			jumping_animation_count = 26;
		}
	}
}

/**
 * @brief Move to the right
 *
 * Move the little girl to the right
 *
 * @param actual_x_state If the girl is turned left or right
 * @param actual_y_state If she is jumping or falling
 *
 * @return void
 */
void LittleGirl::move_right(std::string actual_x_state, 
	std::string actual_y_state) {
	
	/* Gets actual animation and increases coordinateOnTexture value in 192 */
	engine::Animation *actual_animation = get_actual_animation();
	actual_animation->coordinatesOnTexture.first += 192;
	
	if (actual_animation->coordinatesOnTexture.first >= 1728) {
	/* If coordinateOnTexture value is equal or higher than 1728 */
		
		/* Makes coordinateOnTexture value equal 26 */
		actual_animation->coordinatesOnTexture.first = 0;
	}
	
	/* Makes Little Girl walk to the right */
	states.set_state("X_STATE", "LOOKING_RIGHT");
	set_actual_animation(animations["running_right_animation"]);
	play_song("steps");
	set_speed_x(0.1);
	
	if (actual_y_state == "JUMPING" && actual_x_state == "LOOKING_LEFT") {
	/* If the Little Girl is jumping and looking left */

		/* Turns the Little Girl to the right, and keeps she jumping */
		states.set_state("X_STATE", "LOOKING_RIGHT");
		play_song("steps");
		set_actual_animation(animations["jumping_right_animation"]);
	}
}

/**
 * @brief Move to the left
 *
 * Move the little girl to the left
 *
 * @param actual_x_state If the girl is turned left or right
 * @param actual_y_state If she is jumping or falling
 *
 * @return void
 */
void LittleGirl::move_left(std::string actual_x_state,
	std::string actual_y_state) {
	
	/* Gets actual animation and decreases coordinateOnTexture value in 192 */
	engine::Animation *actual_animation = get_actual_animation();
	actual_animation->coordinatesOnTexture.first -= 192;
	
	if (actual_animation->coordinatesOnTexture.first <= 0) {
	/* If coordinateOnTexture value is equal or lower than 0 */
		
		/* Makes coordinateOnTexture value equal 1536 */
		actual_animation->coordinatesOnTexture.first = 1536;
	}
	
	/* Makes Little Girl walk to the left */
	states.set_state("X_STATE", "LOOKING_LEFT");
	set_actual_animation(animations["running_left_animation"]);
	play_song("steps");
	set_speed_x(-0.1);
	
	if (actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT") {
	/* If the Little Girl is jumping and looking right */

		/* Turns the Little Girl to the left, and keeps she jumping */
		states.set_state("X_STATE", "LOOKING_LEFT");
		play_song("steps");
		set_actual_animation(animations["jumping_left_animation"]);
	}
}

/**
 * @brief Makes the girl attack
 *
 * @return void
 */
void LittleGirl::attack() {

	/* Gets actual state in x axis */
	std::string actual_x_state = states.get_state("X_STATE");
	states.set_state("ACTION_STATE", "ATTACKING"); /* Sets states 
	equal Attacking */
	
	if (actual_x_state == "LOOKING_RIGHT") {
	/* If the Little Girl is looking right */

		/* Makes Little Girl attack looking right */
		set_actual_animation(animations["attacking_right_animation"]);
		get_actual_animation()->is_finished = false;
	} 

	else if (actual_x_state == "LOOKING_LEFT") {
	/* If the Little Girl is looking left */

		/* Makes Little Girl attack looking left */
		set_actual_animation(animations["attacking_left_animation"]);
		get_actual_animation()->is_finished = false;
	}

	play_song("sword_attack"); /* Plays sword sound effect */
}

/**
 * @brief Event for on attack
 *
 * Event called everytime an attack happens
 *
 * @param game_object
 *
 * @return void
 */
void LittleGirl::on_attack(GameObject *game_object) {

	/* Gets actual state in x axis */
	std::string actual_x_state = states.get_state("X_STATE");
	states.set_state("ACTION_STATE", "ON_ATTACK"); /* Sets states 
	equal On Attacking */

	if (actual_x_state == "LOOKING_LEFT") {
	/* If the Little Girl is looking left */

		set_actual_animation(animations["on_attack_left_animation"]); /* Makes
		Little Girl be attacked looking left */
	}

	else if (actual_x_state == "LOOKING_RIGHT") {
	/* If the Little Girl is looking right */

		set_actual_animation(animations["on_attack_right_animation"]); /* Makes
		Little Girl be attacked looking right */
	}
}

/**
 * @brief Updates the state
 *
 * Updates the state on the states map
 *
 * @return void
 */
void LittleGirl::update_state() {

	if (get_position_y() >= 576) {
	/* If the coordinate in y axe is higher or equal than 576 */

		die(NULL); /* Keeps the Little Girl alive */
	}

	/* Gets Little Girl's states */
	std::string actual_y_state = states.get_state("Y_STATE");
	std::string actual_action_state = states.get_state("ACTION_STATE");
	std::string actual_x_state = states.get_state("X_STATE");
	
	if (actual_action_state == "ATTACKING" || 
		actual_action_state == "ON_ATTACK") {
	/* If the Little Girl is attacking or been attacked */

		if (get_actual_animation()->is_finished) {
		/* If the Little Girl animation is over */

			states.set_state("ACTION_STATE", "NORMAL"); /* Sets action state
			equal Normal */
		} 

		else {
		/* Do nothing */	
		
			return;
		}
	}
	
	if (get_speed_x() == 0.0 && get_speed_y() == 0.0 
		&& actual_action_state == "NORMAL") {
	/* If the Little Girl is not moving */

		if (actual_x_state == "LOOKING_RIGHT") {
		/* If the Little Girl is looking right */
		
			set_actual_animation(animations["idle_right_animation"]);/* Makes
			She rest looking right */
		} 

		else if (actual_x_state == "LOOKING_LEFT") {
		/* If the Little Girl is looking left */

			set_actual_animation(animations["idle_left_animation"]);/* Makes
			She rest looking left */
		}
		
		/* Sets jumping_animation_count equals zero */
		jumping_animation_count = 0;
	}
	
	if (get_speed_y() == 0.0 && get_state("Y_STATE") != "JUMPING") {
	/* If the Little Girl does not have speed in y axe and she is not jumping */

		/* Makes she stay on ground */
		states.set_state("Y_STATE", "ON_GROUND");
	} 

	else if (get_speed_y() == 0.0) {
	/* If the Little Girl does not have speed in y axe and she is jumping */

		/* Makes she fall */
		states.set_state("Y_STATE", "FALLING");
	}
	
	/* Sets new x coordinates and makes speed in x axe equal 0 */
	set_position_x(get_position_x() - get_speed_x());
	set_speed_x(0.0);
}
