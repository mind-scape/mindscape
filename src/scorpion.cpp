/**
 * @file scorpion.cpp
 * @brief Purpose: Contains scorpion's methods.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/scorpion.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

/**
 * @brief Initializes Scorpion enemy.
 *
 * Constructor responsible to initialize a scorpion in game.
 *
 * @param name Object's name.
 * @param position X and Y axis positions.
 * @param priority Rendering priority object.
 */

Scorpion::Scorpion(
    std::string name,
    std::pair<int, int> position,
    int priority)
    :Enemy(
        name,
        position,
        priority,
        100
    ){
        initialize_state_map();
        initialize_hitboxes();
        initialize_animations();
        initialize_as_physicable();
        initialize_audio_effects();
};

/**
 * @brief Initialize scorpion's audio effects.
 *
 * Initialize audio effects when a scorpion is attacking or when is on attack.
 *
 * @return void.
 */

void Scorpion::initialize_audio_effects() {
    engine::Audio * scorpion_attacking = nullptr;

    scorpion_attacking = new engine::Audio(
        "attack",
        "../assets/audios/effects_songs/ataque_insetos.wav", 
        engine::Audio::CHUNK);

    scorpion_attacking->set_duration(0.7);

    engine::Audio * scorpion_on_attack = nullptr;

    scorpion_on_attack = new engine::Audio(
        "hit_me",
        "../assets/audios/effects_songs/inseto_apanhando.wav", 
        engine::Audio::CHUNK);

    scorpion_on_attack->set_duration(0.8);

    add_component(scorpion_attacking);
    add_component(scorpion_on_attack);
}

/**
 * @brief Initialize Scorpion's animations.
 *
 * Define scorpion's movement and attack animation.
 *
 * @return void.
 */

void Scorpion::initialize_animations() {
    engine::Animation* walking_left_animation = nullptr;

    walking_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_walking_left.png",
        1, 5, 0.9, "LEFT"
    );

    engine::Animation* walking_right_animation = nullptr;

    walking_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_walking_right.png",
        1, 5, 0.9, "RIGHT"
    );

    engine::Animation* idle_left_animation = nullptr;

    idle_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_idle_left.png",
        1, 2, 0.9, "LEFT"
    );

    engine::Animation* idle_right_animation = nullptr;

    idle_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_idle_right.png",
        1, 2, 0.9, "RIGHT"
    );

    engine::Animation* attacking_left_animation = nullptr;

    attacking_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_attacking_left.png",
        1, 5, 0.7, "LEFT"
    );

    engine::Animation* attacking_right_animation = nullptr;

    attacking_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_attacking_right.png",
        1, 5, 0.7, "RIGHT"
    );

    engine::Animation* on_attack_left_animation = nullptr;

    on_attack_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_on_attack_left.png",
        1, 2, 0.8, "LEFT"
    );

    engine::Animation* on_attack_right_animation = nullptr;

    on_attack_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_on_attack_right.png",
        1, 2, 0.8, "RIGHT"
    );

    engine::Animation* dying_left_animation = nullptr;

    dying_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_dying_left.png",
        1, 5, 0.8, "LEFT"
    );

    dying_left_animation->is_a_final_animation = true;
    dying_left_animation->in_loop = false;

    engine::Animation* dying_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_dying_right.png",
        1, 5, 0.8, "RIGHT"
    );

    dying_right_animation->is_a_final_animation = true;
    dying_right_animation->in_loop = false;

    add_animation("walking_left_animation", walking_left_animation);
    add_animation("walking_right_animation", walking_right_animation);
    add_animation("idle_left_animation", idle_left_animation);
    add_animation("idle_right_animation", idle_right_animation);
    add_animation("attacking_left_animation", attacking_left_animation);
    add_animation("attacking_right_animation", attacking_right_animation);
    add_animation("on_attack_left_animation", on_attack_left_animation);
    add_animation("on_attack_right_animation", on_attack_right_animation);
    add_animation("dying_left_animation", dying_left_animation);
    add_animation("dying_right_animation", dying_right_animation);
    idle_right_animation->activate();
    set_actual_animation(idle_right_animation);
}

/**
 * @brief Creates Scorpion's animation.
 *
 * Creates an animation to Scorpion enemy.
 *
 * @param path Path to the image which contains the sprite sheet.
 * @param sprite_lines Number of the lines on the sprite sheet.
 * @param sprite_colums Number of colums on the sprite sheet.
 * @param duration Time duration of animation.
 * @param direction Direction of animation.
 * @return This method returns Scorpion's animation.
 */

engine::Animation* Scorpion::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction){

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
 * @brief Initialize physics on Scorpion.
 *
 * This method allow that the Scorpion turns collidable.
 *
 * @return void.
 */

void Scorpion::initialize_as_physicable() {
    engine::Physics *physics = nullptr;
    physics = engine::Physics::get_instance();
    physics->add_physicable(this);
    collidable = true;
}

/**
 * @brief Initialize Scorpion's hitboxes.
 *
 * Initializes Scorpion instance hitboxes.
 * 
 * @return void.
 */

void Scorpion::initialize_hitboxes() {
    engine::Game& game = engine::Game::get_instance();

    engine::Hitbox* scorpion_hitbox = nullptr;
    scorpion_hitbox = new engine::Hitbox(
        "scorpion_hitbox",
        this->get_position(),
        std::make_pair(40, 312),
        std::make_pair(180,8),
        game.get_renderer()
    );

    engine::Hitbox* scorpion_attack = nullptr;
    scorpion_attack = new engine::Hitbox(
        "scorpion_attack",
        this->get_position(),
        std::make_pair(5, 200),
        std::make_pair(283,10),
        game.get_renderer()
    );
  
    add_component(scorpion_attack);
    add_component(scorpion_hitbox);
}

/**
 * @brief Initialize Scorpion's state map.
 *
 * Initialize all possibles states for the scorpion.
 * 
 * @return void.
 */

void Scorpion::initialize_state_map() {
    states.set_state("ACTION_STATE", "NORMAL");
}

/**
 * @brief Register game events.
 *
 * Register an event to Scorpion.
 *
 * @param game_event Triggering in-game events.
 * @return void.
 */

void Scorpion::on_event(GameEvent game_event) {
    std::string event_name = "";
    event_name = game_event.game_event_name;
    int actual_position = 0;

    if (event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {
        actual_position = get_position_x();
        set_position_x(actual_position + 10);
    }
    else if (event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level) {
        actual_position = get_position_x();
        set_position_x(actual_position - 10);
    }
}

/**
 * @brief Notify if the object is in the range.
 *
 * Notify if there is an object in the Scorpion's range.
 *
 * @param game_object The game object passed in notification, in this case,
 * the girl.
 * @return void.
 */

void Scorpion::notify(engine::Observable *game_object) {
    LittleGirl* little_girl = nullptr; 
    little_girl = dynamic_cast<LittleGirl *>(game_object);
    
    if (little_girl) {
        move(little_girl);
    }
}

/**
 * @brief Scorpion's attack.
 *
 * This method define Scorpion's state while is attacking to the left or
 * to the right.
 * 
 * @return void.
 */

void Scorpion::attack() {
    states.set_state("ACTION_STATE","ATTACKING");
    std::string actual_x_state = "";
    actual_x_state = get_state("X_STATE");
  
    if (actual_x_state == "LOOKING_LEFT") {
        set_actual_animation(animations["attacking_left_animation"]);
    }
    else if (actual_x_state == "LOOKING_RIGHT") {
        set_actual_animation(animations["attacking_right_animation"]);
    }

    play_song("attack");
}

/**
 * @brief Define action when is on attack.
 *
 * Event called when a Scorpion is attacking.
 *
 * @param game_object Object to be attacked.
 * @return void.
 */

void Scorpion::on_attack(GameObject *game_object) {
    states.set_state("ACTION_STATE","ON_ATTACK");

    std::string actual_x_state = "";
    actual_x_state = get_state("X_STATE");
    hit(game_object, 15);

    if (is_alive()) {
        if (actual_x_state == "LOOKING_LEFT") {
            set_actual_animation(animations["on_attack_left_animation"]);
        }
        else if (actual_x_state == "LOOKING_RIGHT") {
            set_actual_animation(animations["on_attack_right_animation"]);
        }
        play_song("hit_me");
    }
}

/**
 * @brief Death method.
 *
 * This method define an animation when a Scorpion is dead.
 *
 * @param game_object Scorpion.
 * @return void.
 */

void Scorpion::die(engine::GameObject *game_object) {
    std::string actual_x_state = "";
    actual_x_state = get_state("X_STATE");
  
    if (actual_x_state == "LOOKING_LEFT") {
        states.set_state("ACTION_STATE", "DYING");
        set_actual_animation(animations["dying_left_animation"]);
    }
    else if (actual_x_state == "LOOKING_RIGHT") {
        states.set_state("ACTION_STATE", "DYING");
        set_actual_animation(animations["dying_right_animation"]);
    }
    play_song("hit_me");
}

/**
 * @brief Scorpion's move.
 *
 * This method allow that a Scorpion can follow the girl.
 *
 * @param game_object Girl.
 * @return void.
 */

void Scorpion::move(engine::GameObject* girl) {
    float scorpion_position = 0;
    scorpion_position = get_position_x();

    float girl_position = 0;
    girl_position  = girl->get_position_x();

    float scorpion_position_y = 0;
    scorpion_position_y = get_position_y();

    float girl_position_y = 0;
    girl_position_y = girl->get_position_y();

  //132 is the diference of girl position_y and scorpion position_y
    if (scorpion_position_y + 132 == girl_position_y) {
        same_nivel = true;
    } 
    else {
        same_nivel = false;
    }

    if (get_state("ACTION_STATE") == "DYING") {
        return;
    }

    if(get_actual_animation()->is_finished) {
        states.set_state("ACTION_STATE","NORMAL");
    }

    if(get_state("ACTION_STATE") == "ON_ATTACK") {
        return;
    }

    int distance_from_girl = 0;

    if (scorpion_position > girl_position) {
        states.set_state("X_STATE","LOOKING_LEFT");
        distance_from_girl = scorpion_position - girl_position;

        if (distance_from_girl > 300) {
            set_actual_animation(animations["idle_left_animation"]);
        }
        else if (distance_from_girl <= 300) {
            states.set_state("ACTION_STATE","NORMAL");
            
            if (distance_from_girl >= 50) {
                set_position_x(get_position_x() - (same_nivel? 8 : 3));
                set_actual_animation(animations["walking_left_animation"]);
            }
            else {
                if (same_nivel) {
                    attack();
                }
            }
        }
    }
    else {
        states.set_state("X_STATE","LOOKING_RIGHT");
        distance_from_girl = girl_position - scorpion_position;

        if (distance_from_girl > 588) {
            set_actual_animation(animations["idle_right_animation"]);
        }
        else if (distance_from_girl <= 588) {

            if (distance_from_girl >= 200) {
                set_position_x(get_position_x() + (same_nivel? 8 : 3));
                set_actual_animation(animations["walking_right_animation"]);
            }
            else {
                if (same_nivel) {
                    attack();
                }
            }
        }
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

void Scorpion::on_collision(
    engine::GameObject* other, 
    engine::Hitbox* p_my_hitbox, 
    engine::Hitbox* p_other_hitbox) {

    Platform* platform = nullptr;
    platform = dynamic_cast<Platform *>(other);

    LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(other);

    engine::Hitbox* my_hitbox = nullptr;
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);

    engine::Hitbox* other_hitbox = nullptr;
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);


    if (get_speed_y() >= 0 
        && platform 
        && my_hitbox->get_name() == "scorpion_hitbox") {
        
        set_speed_y(0.0);
        set_position_y(other_hitbox->get_coordinates().second - 312);
    }

    if (little_girl 
        && little_girl->get_state("ACTION_STATE") == "ATTACKING" 
        && my_hitbox->get_name() == "scorpion_attack" 
        && little_girl->get_actual_animation()->actual_column == 2 
        && get_state("X_STATE") != little_girl->get_state("X_STATE")) {
        
        if (get_state("ACTION_STATE") == "ON_ATTACK") {
            return;
        }
        else {
            on_attack(other);
        }
    }
}