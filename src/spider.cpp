/**
 * @file spider.cpp
 * @brief Purpose: Contains spider's methods.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/spider.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

/**
 * @brief Initializes Spider enemy.
 *
 * Constructor responsible to initialize a spider in game.
 *
 * @param name Object's name.
 * @param position X and Y axis positions.
 * @param priority Rendering priority object.
 */

Spider::Spider(
    std::string name,
    std::pair<int, int> position,
    int priority
    ):Enemy(
        name,
        position,
        priority,
        100
    ) {
        initialize_state_map();
        initialize_animations();
        initialize_hitboxes();
        initialize_animations();
        initialize_audio_effects();
        initialize_as_physicable();
};

/**
 * @brief Initialize spider's audio effects.
 *
 * Initialize audio effects when a spider is attacking or when is on attack.
 *
 * @return void.
 */

void Spider::initialize_audio_effects() {
    engine::Audio * spider_attacking = nullptr;

    spider_attacking = new engine::Audio(
        "attack",
        "../assets/audios/effects_songs/ataque_insetos.wav",
        engine::Audio::CHUNK);
    spider_attacking->set_duration(0.5);

    engine::Audio * spider_on_attack = nullptr;

    spider_on_attack = new engine::Audio(
        "hit_me",
        "../assets/audios/effects_songs/inseto_apanhando.wav",
        engine::Audio::CHUNK);
    spider_on_attack->set_duration(0.8);

    add_component(spider_attacking);
    add_component(spider_on_attack);
}

/**
 * @brief Initialize Spider's animations.
 *
 * Define spider's movement and attack animation.
 *
 * @return void.
 */

void Spider::initialize_animations() {
    engine::Animation* walking_left_animation = nullptr;

    walking_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_walking_left.png",
        1, 4, 0.9, "LEFT"
    );

    engine::Animation* walking_right_animation = nullptr;

    walking_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_walking_right.png",
        1, 4, 0.9, "RIGHT"
    );

    engine::Animation* idle_left_animation = nullptr;

    idle_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_idle_left.png",
        1, 2, 0.9, "LEFT"
    );

    engine::Animation* idle_right_animation = nullptr;

    idle_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_idle_right.png",
        1, 2, 0.9, "RIGHT"
    );

    engine::Animation* on_attack_left_animation = nullptr;

    on_attack_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_on_attack_left.png",
        1, 2, 0.5, "LEFT"
    );

    engine::Animation* on_attack_right_animation = nullptr;
    on_attack_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_on_attack_right.png",
        1, 2, 0.5, "RIGHT"
    );

    engine::Animation* attacking_left_animation = nullptr;

    attacking_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_attacking_left.png",
        1, 4, 0.5, "LEFT"
    );

    engine::Animation* attacking_right_animation = nullptr;

    attacking_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_attacking_right.png",
        1, 4, 0.5, "RIGHT"
    );

    engine::Animation* dying_left_animation = nullptr;

    dying_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_dying_left.png",
        1, 2, 0.5, "LEFT"
    );

    engine::Animation* dying_right_animation = nullptr;

    dying_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_dying_right.png",
        1, 2, 0.5, "RIGHT"
    );

    dying_left_animation->is_a_final_animation = true;
    dying_left_animation->in_loop = false;

    dying_right_animation->is_a_final_animation = true;
    dying_right_animation->in_loop = false;

    add_animation("walking_left_animation", walking_left_animation);
    add_animation("walking_right_animation", walking_right_animation);
    add_animation("idle_left_animation", idle_left_animation);
    add_animation("idle_right_animation", idle_right_animation);
    add_animation("on_attack_left_animation", on_attack_left_animation);
    add_animation("on_attack_right_animation", on_attack_right_animation);
    add_animation("dying_left_animation", dying_left_animation);
    add_animation("dying_right_animation", dying_right_animation);
    add_animation("attacking_right_animation", attacking_right_animation);
    add_animation("attacking_left_animation", attacking_left_animation);
    idle_left_animation->activate();
    set_actual_animation(idle_left_animation);
}

/**
 * @brief Creates Spider's animation.
 *
 * Creates an animation to Spider enemy.
 *
 * @param path Path to the image which contains the sprite sheet.
 * @param sprite_lines Number of the lines on the sprite sheet.
 * @param sprite_colums Number of colums on the sprite sheet.
 * @param duration Time duration of animation.
 * @param direction Direction of animation.
 * @return This method returns Spider's animation.
 */

engine::Animation* Spider::create_animation(
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
        std::make_pair(288, 288),
        std::make_pair(288, 288),
        std::make_pair(0, 0)
    );

    return animation;
}

/**
 * @brief Initialize physics on Spider.
 *
 * This method allow that the Spider turns collidable.
 *
 * @return void.
 */

void Spider::initialize_as_physicable() {
    engine::Physics *physics = nullptr;
    physics = engine::Physics::get_instance();
    physics->add_physicable(this);
    collidable = true;
}

/**
 * @brief Initialize Spider's hitboxes.
 *
 * Initializes Spider instance hitboxes.
 * 
 * @return void.
 */

void Spider::initialize_hitboxes() {
    engine::Game& game = engine::Game::get_instance();
    engine::Hitbox* spider_hitbox = nullptr;

    spider_hitbox = new engine::Hitbox(
        "spider_hitbox",
        this->get_position(),
        std::make_pair(60, 280),
        std::make_pair(180, 8),
        game.get_renderer()
    );

    engine::Hitbox* spider_attack = nullptr;

    spider_attack = new engine::Hitbox(
        "spider_attack",
        this->get_position(),
        std::make_pair(5, 200),
        std::make_pair(283,10),
        game.get_renderer()
    );

    add_component(spider_attack);
    add_component(spider_hitbox);
}

/**
 * @brief Initialize Spider's state map.
 *
 * Initialize all possibles states for the scorpion.
 * 
 * @return void.
 */

void Spider::initialize_state_map() {
    states.set_state("ACTION_STATE","NORMAL");
}

/**
 * @brief Register game events.
 *
 * Register an event to Spider.
 *
 * @param game_event Triggering in-game events.
 * @return void.
 */

void Spider::on_event(GameEvent game_event) {
    std::string event_name = "";
    event_name = game_event.game_event_name;
    
    int actual_position = 0;

    if (event_name == "MOVE_LEFT" 
        && !engine::GameObject::on_limit_of_level) {
        actual_position = get_position_x();
        set_position_x(actual_position + 10);
    }
    else if (event_name == "MOVE_RIGHT" 
        && !engine::GameObject::on_limit_of_level) {
        actual_position = get_position_x();
        set_position_x(actual_position - 10);
    }
}

/**
 * @brief Notify if the object is in the range.
 *
 * Notify if there is an object in the Spider's range.
 *
 * @param game_object The game object passed in notification, in this case, 
 * the girl.
 * @return void.
 */

void Spider::notify(engine::Observable *game_object) {
    LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(game_object);
  
    if (little_girl) {
        move(little_girl);
    }
}

/**
 * @brief Spider's attack.
 *
 * This method define Spider's state while is attacking to the left or
 * to the right.
 * 
 * @return void.
 */

void Spider::attack() {
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
 * @brief Spider's move.
 *
 * This method allow that a Spider can follow the girl.
 *
 * @param game_object Girl.
 * @return void.
 */

void Spider::move(engine::GameObject* girl) {
    float spider_position = 0;
    spider_position = get_position_x();
    float girl_position = 0;
    girl_position = girl->get_position_x();

    float spider_position_y = 0;
    spider_position_y = get_position_y();

    float girl_position_y = 0;
    girl_position_y = girl->get_position_y();

    //100 is the diference of girl position_y and spider position_y
    if (spider_position_y + 100 == girl_position_y) {
        same_nivel = true;
    } 
    else {
        same_nivel = false;
    }


    if (get_state("ACTION_STATE") == "DYING") {
        return;
    }

    if (get_actual_animation()->is_finished){
        states.set_state("ACTION_STATE","NORMAL");
    }

    if(get_state("ACTION_STATE") == "ON_ATTTACK") {
        return;
    }

    int distance_from_girl = 0;

    //little_girl on left
    if (spider_position > girl_position) {
        states.set_state("X_STATE","LOOKING_LEFT");
        distance_from_girl = spider_position - girl_position;

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
    //little_girl on right
    }
    else {
        states.set_state("X_STATE","LOOKING_RIGHT");
        distance_from_girl = girl_position - spider_position;

        if (distance_from_girl > 588) {
            set_actual_animation(animations["idle_right_animation"]);
        }
        else if (distance_from_girl <= 588) {
            if (distance_from_girl >= 150) {
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
 * @brief Define action when is on attack.
 *
 * Event called when a Spider is attacking.
 *
 * @param game_object Object to be attacked.
 * @return void.
 */

void Spider::on_attack(GameObject *game_object) {
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
 * This method define an animation when a Spider is dead.
 *
 * @param game_object Spider.
 * @return void.
 */

void Spider::die(engine::GameObject *game_object) {
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
 * @brief Event for the collision.
 *
 * Method called everytime when two game objects collides.
 *
 * @param other Other game object that collides.
 * @param p_my_hitbox Hitbox that receives the collision.
 * @param p_other_hitbox Hitbox that collided.
 * @return void.
 */

void Spider::on_collision(
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

    if (get_speed_y() >= 0 && platform 
        && my_hitbox->get_name() == "spider_hitbox") {
        
        set_speed(std::make_pair(get_speed_x(), 0.0));
        set_position(
            std::make_pair(get_position().first, 
            other_hitbox->get_coordinates().second - 280)
        );
    }
  
    if (little_girl 
        && little_girl->get_state("ACTION_STATE") == "ATTACKING" 
        && my_hitbox->get_name() == "spider_attack" 
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