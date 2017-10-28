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
        /* Initialize all the characterists of the Uncle's boss. */
    	initialize_state_map();
    	initialize_hitboxes();
    	initialize_animations();
    	initialize_audio_effects();
	};

/**
 * @brief Initialize Uncle's animations.
 *
 * Define Uncle's movement and attack animation.
 *
 * @return void.
 */

void Uncle::initialize_animations() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing animations.");

  	engine::Animation* idle_animation = nullptr; /**< Animation.
    Animation that represents uncle's in a idle state.s */

    /* Creates uncle's idle animation. */
    idle_animation = create_animation(
      	"../assets/images/sprites/enemies/uncle/uncle_idle.png",
      	1, 4, 3.0, "LEFT"
    );

    /* Sets uncle's idle animation to define when its stopped. */
  	idle_animation->set_values(
      	std::make_pair(665, 484),
      	std::make_pair(665, 484),
      	std::make_pair(0, 0)
    );

    add_animation("idle_animation",idle_animation);

    idle_animation->activate();
  	set_actual_animation(idle_animation);

  	engine::Animation* attacking_animation = nullptr; /**< Animation.
    Animation that represents uncle's attacking. */

    /* Creates uncle's attack animation. */
    attacking_animation = create_animation(
     	"../assets/images/sprites/enemies/uncle/uncle_attacking.png",
      	1, 1, 3.0, "LEFT"
    );

    /* Sets uncle's attacking animation to define when its attacking. */
  	attacking_animation->set_values(
      	std::make_pair(719, 523),
      	std::make_pair(719, 523),
      	std::make_pair(0, 0)
    );

  	attacking_animation->in_loop = false;

   	add_animation("attacking_animation",attacking_animation);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Animations initializated.");
}

/**
 * @brief Initialize Uncle's hitboxes.
 *
 * Initializes Uncle instance hitboxes.
 *
 * @return void.
 */

void Uncle::initialize_hitboxes() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing uncle's hitbox.");

  	engine::Game& game = engine::Game::get_instance(); /**< Game.
    Gets an instance of a game just initializated. */

    engine::Hitbox* head_hitbox = nullptr; /**< Hitbox.
    Initialize uncle's head hitbox. */

    head_hitbox = new engine::Hitbox(
    	  "head_hitbox",
    	  this->get_position(),
    	  std::make_pair(160, 380),
    	  std::make_pair(180,20),
    	  game.get_renderer()
  	);

    /* Add hitbox component into the game object. */
  	add_component(head_hitbox);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Uncle's hitbox initialized");
}

/**
 * @brief Initialize Uncle's state map.
 *
 * Initialize all possibles states for the Uncle.
 *
 * @return void.
 */

void Uncle::initialize_state_map() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing uncle's state.");
  	states.set_state("ACTION_STATE","NORMAL");
    /* Ends debugger that represents the end of the method. */
    DEBUG("Uncle's state initialized.");
}

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
 * @brief Register game events.
 *
 * Register an event to Uncle.
 *
 * @param game_event Triggering in-game events.
 * @return void.
 */

void Uncle::on_event(GameEvent game_event) {
  	std::string event_name = ""; /**< String.
    Gets an event catched by the Uncle. */

    /* Gets event related with the Uncle. */
    event_name = game_event.game_event_name;

    /* Check if the Uncle gets an event to move to the left direction. */
  	if (event_name == "MOVE_LEFT"
  		&& !engine::GameObject::on_limit_of_level) {

        /* The Uncle increments its actual position. */
    	  set_position_x(get_position_x() + 10);
  	}
    /* Check if the Uncle gets an event to move to the right direction. */
  	else if (event_name == "MOVE_RIGHT"
  		&& !engine::GameObject::on_limit_of_level) {

        /* The Uncle decrements its actual position. */
    	  set_position_x(get_position_x() - 10);
  	}
    else {
        /* Event name is not found. */
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
  	LittleGirl* little_girl = nullptr; /**< LittleGirl.
    Gets as observable that tells when little_girl is next. */

    little_girl = dynamic_cast<LittleGirl *>(game_object);

    /* Notify if little_girl exists, moving to her direction. */
    if (little_girl) {
        /* The Uncle moves in direction of the girl. */
      	attack(little_girl);
  	}
    else {
        /* The Uncle don't attack. */
    }
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
  	LittleGirl* little_girl = nullptr; /**< LittleGirl.
    References to LittleGirl object. */
    little_girl = dynamic_cast<LittleGirl *>(other);

  	engine::Hitbox* my_hitbox = nullptr; /**< Hitbox.
    References to Uncle's hitbox. */
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);

  	engine::Hitbox* other_hitbox = nullptr; /**< Hitbox.
    References to girl's hitbox. */
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

    /* Check if the girl is attacking the Uncle. */
  	if (little_girl
  		&& little_girl->get_state("ACTION_STATE") == "ATTACKING"
  		&& my_hitbox->get_name() == "head_hitbox"
  		&& little_girl->get_actual_animation()->actual_column == 2
     	&& get_state("X_STATE") != little_girl->get_state("X_STATE")) {

          /* Check if the Uncle is under attack. */
          if(get_state("ACTION_STATE") == "ON_ATTACK") {
              return;
          }
          else {
              on_attack(other);
          }
  	}
    else {
        /* The girl is not attacking the Uncle. */
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
 * @brief Uncle's attack.
 *
 * This method define Uncle's state while is attacking, is on attack or
 * while is dying.
 *
 * @param little_girl Object to be attacked.
 * @return void.
 */

void Uncle::attack(engine::GameObject* little_girl) {
    DEBUG("The uncle is attacking.");

  	std::string actual_action_state = ""; /**< String.
    Gets the actual state of the uncle. */
    actual_action_state = get_state("ACTION_STATE");

  	if (actual_action_state == "DYING") {
        INFO("The Uncle is dying.");
    		return;
  	}
    else {
        /* The Uncle stills alive. */
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
    else {
        /* The Uncle is in a idle state. */
    }
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
    else {
        /* The Uncle is dead. */
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
    DEBUG("The uncle is dying.");
  	std::string actual_x_state = ""; /**< String.
    Gets the actual state of the uncle. */
    actual_x_state = get_state("X_STATE");
    /* Sets a state that represents when uncle is dead. */
    states.set_state("ACTION_STATE", "DYING");
    /* Initiates the animation that show the uncle dying.*/
  	set_actual_animation(animations["dying_animation"]);
  	//play_song("hit_me");
    DEBUG("The uncle died.");
}
