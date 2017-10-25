/**
 * @file uncle.cpp
 * @brief Purpose: Contains uncle's methods.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/uncle.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/log.hpp"
#include <stdlib.h>

using namespace mindscape;

/**
 * @brief Initializes Uncle enemy.
 *
 * Constructor responsible to initialize Uncle in game.
 *
 * @param name Object's name.
 * @param position X and Y axis positions.
 * @param priority Rendering priority object.
 */

Uncle::Uncle(
  		std::string name,
  		std::pair<int, int> position,
  		int priority
	):Enemy(
    	name,
    	position,
    	priority,
    	100
  	){
    	initialize_state_map();
    	initialize_hitboxes();
    	initialize_animations();
    	initialize_audio_effects();
	};

/**
 * @brief Initialize uncle's audio effects.
 *
 * Not implemented.
 *
 * @return void.
 */

void Uncle::initialize_audio_effects() {
}

/**
 * @brief Initialize Uncle's animations.
 *
 * Define Uncle's movement and attack animation.
 *
 * @return void.
 */

void Uncle::initialize_animations() {
  	engine::Animation* idle_animation = nullptr;
    idle_animation = create_animation(
      	"../assets/images/sprites/enemies/uncle/uncle_idle.png",
      	1, 4, 3.0, "LEFT"
    );

  	idle_animation->set_values(
      	std::make_pair(665, 484),
      	std::make_pair(665, 484),
      	std::make_pair(0, 0)
    );

  	engine::Animation* attacking_animation = nullptr;
    attacking_animation = create_animation(
     	"../assets/images/sprites/enemies/uncle/uncle_attacking.png",
      	1, 1, 3.0, "LEFT"
    );

  	attacking_animation->set_values(
      	std::make_pair(719, 523),
      	std::make_pair(719, 523),
      	std::make_pair(0, 0)
    );

  	attacking_animation->in_loop = false;

  	add_animation("idle_animation",idle_animation);
 	add_animation("attacking_animation",attacking_animation);
  	idle_animation->activate();
  	set_actual_animation(idle_animation);
}

/**
 * @brief Creates Uncle's animation.
 *
 * Creates an animation to Uncle enemy.
 *
 * @param path Path to the image which contains the sprite sheet.
 * @param sprite_lines Number of the lines on the sprite sheet.
 * @param sprite_colums Number of colums on the sprite sheet.
 * @param duration Time duration of animation.
 * @param direction Direction of animation.
 * @return This method returns Uncle's animation.
 */

engine::Animation* Uncle::create_animation(
	std::string path,
  	int sprite_lines,
  	int sprite_columns,
  	double duration,
  	std::string direction) {

  	engine::Game& game = engine::Game::get_instance();

    engine::Animation* animation = nullptr;
    animation = new engine::Animation(
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

  	animation->set_values(
    	std::make_pair(320, 320),
    	std::make_pair(320, 320),
    	std::make_pair(0, 0)
  	);

  	return animation;
}

/**
 * @brief Initialize Uncle's hitboxes.
 *
 * Initializes Uncle instance hitboxes.
 *
 * @return void.
 */

void Uncle::initialize_hitboxes() {
  	engine::Game& game = engine::Game::get_instance();

    engine::Hitbox* head_hitbox = nullptr;
    head_hitbox = new engine::Hitbox(
    	"head_hitbox",
    	this->get_position(),
    	std::make_pair(160, 380),
    	std::make_pair(180,20),
    	game.get_renderer()
  	);

  	add_component(head_hitbox);
}

/**
 * @brief Initialize Uncle's state map.
 *
 * Initialize all possibles states for the Uncle.
 *
 * @return void.
 */

void Uncle::initialize_state_map() {
  	states.set_state("ACTION_STATE","NORMAL");
}

/**
 * @brief Register game events.
 *
 * Register an event to Uncle.
 *
 * @param game_event Triggering in-game events.
 * @return void.
 */

void Uncle::on_event(GameEvent game_event) {
  	std::string event_name = "";
    event_name = game_event.game_event_name;

  	if (event_name == "MOVE_LEFT"
  		&& !engine::GameObject::on_limit_of_level) {

    	set_position_x(get_position_x() + 10);
  	}
  	else if (event_name == "MOVE_RIGHT"
  		&& !engine::GameObject::on_limit_of_level) {

    	set_position_x(get_position_x() - 10);
  	}
}

/**
 * @brief Notify if the object is in the range.
 *
 * Notify if there is an object in the Uncle's range.
 *
 * @param game_object The game object passed in notification, in this case,
 * the girl.
 * @return void.
 */

void Uncle::notify(engine::Observable *game_object) {
  	LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(game_object);

    if (little_girl) {
    	attack(little_girl);
  	}
    else {
        /* The Uncle don't attack. */
    }
}

/**
 * @brief Uncle's attack.
 *
 * This method define Uncle's state while is attacking, is on attack or
 * while is dying.
 *
 * @param little_girl Object to be attacked.
 * @return void.
 */

void Uncle::attack(engine::GameObject* little_girl) {
  	std::string actual_action_state = "";
    actual_action_state = get_state("ACTION_STATE");

  	if (actual_action_state == "DYING") {
  		return;
  	}

  	if (actual_action_state == "ON_ATTACK"
  		|| actual_action_state == "ATTACKING") {

    	if (get_actual_animation()->is_finished) {
      		states.set_state("ACTION_STATE","NORMAL");
      		set_actual_animation(animations["idle_animation"]);
    	}
    	else {
      		return;
    	}
  	}
}

/**
 * @brief Define a basic attack.
 *
 * Method not implemented.
 *
 * @return void.
 */

void Uncle::basic_attack(){
}

/**
 * @brief Define action when is on attack.
 *
 * Event called when Uncle is attacking.
 *
 * @param game_object Object to be attacked.
 * @return void.
 */

void Uncle::on_attack(engine::GameObject *game_object) {
  	states.set_state("ACTION_STATE","ON_ATTACK");

  	hit(game_object, 1);
  	if (is_alive()) {
    	set_actual_animation(animations["on_attack_animation"]);
    	//play_song("hit_me");
  	}
}

/**
 * @brief Death method.
 *
 * This method define an animation when Uncle is dead.
 *
 * @param game_object Uncle.
 * @return void.
 */

void Uncle::die(engine::GameObject *game_object) {
  	std::string actual_x_state = "";
    actual_x_state = get_state("X_STATE");

    states.set_state("ACTION_STATE", "DYING");
  	set_actual_animation(animations["dying_animation"]);
  	//play_song("hit_me");
}

/**
 * @brief Event for the collision.
 *
 * Method called everytime when two game objects collides.
 *
 * @param other Other game object that collides.
 * @param p_my_hitbox Hitbox that receives the collision.
 * @param p_other_hitbox Hitbox that collided.
 * @return void.
 */

void Uncle::on_collision(
	engine::GameObject* other,
	engine::Hitbox* p_my_hitbox,
	engine::Hitbox* p_other_hitbox) {

  	LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(other);

  	engine::Hitbox* my_hitbox = nullptr;
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);

  	engine::Hitbox* other_hitbox = nullptr;
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  	if (little_girl
  		&& little_girl->get_state("ACTION_STATE") == "ATTACKING"
  		&& my_hitbox->get_name() == "head_hitbox"
  		&& little_girl->get_actual_animation()->actual_column == 2
     	&& get_state("X_STATE") != little_girl->get_state("X_STATE")) {

      	if(get_state("ACTION_STATE") == "ON_ATTACK") {
      		return;
      	}
	    else {
	    	on_attack(other);
  		}
  	}
}
