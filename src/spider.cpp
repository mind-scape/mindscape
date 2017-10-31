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
#include "../engine/include/log.hpp"
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
        /* Initialize all the characterists of the Spider. */
        initialize_state_map();
        initialize_animations();
        initialize_hitboxes();
        initialize_animations();
        initialize_audio_effects();
        initialize_as_physicable();
};

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
    DEBUG("Creating animations.");

    engine::Game& game = engine::Game::get_instance(); /**< Game.
    Gets an instance of a game just initializated. */

    engine::Animation* animation = nullptr; /**< Animation.
    Can represents all functions about spider's animation. */

    /* Initializes an animation object. */
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

    /* Sets values to init a initial position of animation on the screen.*/
    const int size_on_screen = 288;
    const int size_of_texture = 288;

    const int coordinates_x = 0;
    const int coordinates_y = 0;

    animation->set_values(
        std::make_pair(size_on_screen, size_on_screen),
        std::make_pair(size_of_texture, size_of_texture),
        std::make_pair(coordinates_x, coordinates_y)
    );

    DEBUG("Animations created.");
    return animation;
}

/**
 * @brief Initialize Spider's animations.
 *
 * Define spider's movement and attack animation.
 *
 * @return void.
 */

void Spider::initialize_animations() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing animations.");

    const int walking_sprite_lines = 1;
    const int walking_sprite_columns = 4;
    const double walking_duration = 0.9;

    engine::Animation* walking_left_animation = nullptr; /**< Animation.
    Animation that represents spider's walk to the left. */

    /* Creates spider's walk movement animation to the left. */
    walking_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_walking_left.png",
        walking_sprite_lines, walking_sprite_columns, walking_duration, "LEFT"
    );

    /* Adds spider's walk animation to the left. */
    add_animation("walking_left_animation", walking_left_animation);

    engine::Animation* walking_right_animation = nullptr; /**< Animation.
    Animation that represents spider's walk to the right. */

    /* Creates spider's walk movement animation to the right. */
    walking_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_walking_right.png",
        walking_sprite_lines, walking_sprite_columns, walking_duration, "RIGHT"
    );

    /* Adds spider's walk animation to the right. */
    add_animation("walking_right_animation", walking_right_animation);

    const int idle_sprite_lines = 1;
    const int idle_sprite_columns = 2;
    const double idle_duration = 0.9;

    engine::Animation* idle_left_animation = nullptr; /**< Animation.
    Animation that represents spider's idle to the left. */

    /* Creates spider's idle animation to the left. */
    idle_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_idle_left.png",
        idle_sprite_lines, idle_sprite_columns, idle_duration, "LEFT"
    );

    /* Adds spider's idle animation to the left. */
    add_animation("idle_left_animation", idle_left_animation);

    engine::Animation* idle_right_animation = nullptr; /**< Animation.
    Animation that represents spider's idle to the right. */

    /* Creates spider's idle animation to the right. */
    idle_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_idle_right.png",
        idle_sprite_lines, idle_sprite_columns, idle_duration, "RIGHT"
    );

    /* Adds spider's idle animation to the right. */
    add_animation("idle_right_animation", idle_right_animation);

    /* Sets spider's idle animation to define when its stopped. */
    idle_left_animation->activate();
    set_actual_animation(idle_left_animation);

    const int attacking_left_sprite_lines = 1;
    const int attacking_left_sprite_columns = 5;
    const double attacking_left_duration = 0.7;

    engine::Animation* attacking_left_animation = nullptr; /**< Animation.
     Animation that represents spider's attack to the left. */

    /* Creates spider's attack animation to the left. */
    attacking_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_attacking_left.png",
        attacking_left_sprite_lines, attacking_left_sprite_columns,
        attacking_left_duration, "LEFT"
    );

    /* Adds spider's attacking animation to the left. */
    add_animation("attacking_left_animation", attacking_left_animation);

    const int attacking_right_sprite_lines = 1;
    const int attacking_right_sprite_columns = 4;
    const double attacking_right_duration = 0.5;

    engine::Animation* attacking_right_animation = nullptr; /**< Animation.
    Animation that represents spider's attack to the right. */

    /* Creates spider's attack animation to the right. */
    attacking_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_attacking_right.png",
        attacking_right_sprite_lines, attacking_right_sprite_columns,
        attacking_right_duration, "RIGHT"
    );

    /* Adds spider's attacking animation to the right. */
    add_animation("attacking_right_animation", attacking_right_animation);

    const int on_attack_sprite_lines = 1;
    const int on_attack_sprite_columns = 2;
    const double on_attack_duration = 0.5;

    engine::Animation* on_attack_left_animation = nullptr; /**< Animation.
    Animation that represents spider's on attack to the left.  */

    /* Creates spider's animation to the left, when it take some damage. */
    on_attack_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_on_attack_left.png",
        on_attack_sprite_lines, on_attack_sprite_columns, on_attack_duration,
        "LEFT"
    );

    /* Adds spider's under attack animation to the left. */
    add_animation("on_attack_left_animation", on_attack_left_animation);

    engine::Animation* on_attack_right_animation = nullptr; /**< Animation.
    Animation that represents spider's on attack to the right. */

    /* Creates spider's animation to the right, when it take some damage. */
    on_attack_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_on_attack_right.png",
        on_attack_sprite_lines, on_attack_sprite_columns, on_attack_duration,
        "RIGHT"
    );

    /* Adds spider's under attack animation to the right. */
    add_animation("on_attack_right_animation", on_attack_right_animation);

    const int dying_sprite_lines = 1;
    const int dying_sprite_columns = 2;
    const double dying_duration = 0.5;

    engine::Animation* dying_left_animation = nullptr; /**< Animation.
    Animation that represents spider's death to the left. */

    /* Creates spider's death animation to the left. */
    dying_left_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_dying_left.png",
        dying_sprite_lines, dying_sprite_columns, dying_duration, "LEFT"
    );

    /* Initialize booleans that references the spider's death animation
    process, to the left. */
    dying_left_animation->is_a_final_animation = true;
    dying_left_animation->in_loop = false;

    /* Adds spider's dying animation to the left. */
    add_animation("dying_left_animation", dying_left_animation);

    engine::Animation* dying_right_animation = nullptr; /**< Animation.
    Animation that represents spider's death to the right. */

    /* Creates spider's death animation to the right. */
    dying_right_animation = create_animation(
        "../assets/images/sprites/enemies/spider/spider_dying_right.png",
        dying_sprite_lines, dying_sprite_columns, dying_duration, "RIGHT"
    );

    /* Initialize booleans that references the spider's death animation
    process, to the right. */
    dying_right_animation->is_a_final_animation = true;
    dying_right_animation->in_loop = false;

    /* Adds spider's dying animation to the right. */
    add_animation("dying_right_animation", dying_right_animation);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Animations initializated.");
}

/**
 * @brief Initialize physics on Spider.
 *
 * This method allow that the Spider turns collidable.
 *
 * @return void.
 */

void Spider::initialize_as_physicable() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing spider as physicable.");

    engine::Physics *physics = nullptr; /**< Physics.
    Gets a physics instance to spider of a game just initialized. */

    /* Changes physics of an object catched by an instance,
    turning it collidable. */
    physics = engine::Physics::get_instance();
    physics->add_physicable(this);
    collidable = true;

    /* Ends debugger that represents the end of the method. */
    DEBUG("Spider is now collidable.");
}

/**
 * @brief Initialize Spider's hitboxes.
 *
 * Initializes Spider instance hitboxes.
 *
 * @return void.
 */

void Spider::initialize_hitboxes() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing spider's hitbox.");

    engine::Game& game = engine::Game::get_instance(); /**< Game.
    Gets an instance of a game just initializated. */

    engine::Hitbox* spider_hitbox = nullptr; /**< Hitbox.
    Initialize spider's hitbox with its height. */

    spider_hitbox = new engine::Hitbox(
        "spider_hitbox",
        this->get_position(),
        std::make_pair(60, 280),
        std::make_pair(180, 8),
        game.get_renderer()
    );

    /* Adds spider's hitbox component. */
    add_component(spider_hitbox);

    engine::Hitbox* spider_attack = nullptr; /**< Hitbox.
    Initialize spider's hitbox when its attack. */

    spider_attack = new engine::Hitbox(
        "spider_attack",
        this->get_position(),
        std::make_pair(5, 200),
        std::make_pair(283,10),
        game.get_renderer()
    );

    /* Adds spider's attack hitbox component .*/
    add_component(spider_attack);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Spider's hitbox initialized");
}

/**
 * @brief Initialize Spider's state map.
 *
 * Initialize all possibles states for the spider.
 *
 * @return void.
 */

void Spider::initialize_state_map() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing spider's state.");
    /* Sets a normal state to spider's states. */
    states.set_state("ACTION_STATE","NORMAL");
    /* Ends debugger that represents the end of the method. */
    DEBUG("Spider's state initialized.");
}

/**
 * @brief Initialize spider's audio effects.
 *
 * Initialize audio effects when a spider is attacking or when is on attack.
 *
 * @return void.
 */

void Spider::initialize_audio_effects() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing audio effects.");

    engine::Audio * spider_attacking = nullptr; /**< Audio.
    Sound that represents when spider is attacking. */

    /* Creates spider's sound when it's attacking. */
    spider_attacking = new engine::Audio(
        "attack",
        "../assets/audios/effects_songs/ataque_insetos.wav",
        engine::Audio::CHUNK);

    const double duration_attacking = 0.5;

    /* Sets the duration of sound when it's attacking. */
    spider_attacking->set_duration(duration_attacking);

    add_component(spider_attacking);

    engine::Audio * spider_on_attack = nullptr; /**< Audio.
    Sound that represents when spider is on attack. */

    /* Creates spider's sound when it's hitted. */
    spider_on_attack = new engine::Audio(
        "hit_me",
        "../assets/audios/effects_songs/inseto_apanhando.wav",
        engine::Audio::CHUNK);

    const double on_attack_duration = 0.8;

    /* Sets the duration of sound when it's hitted. */
    spider_on_attack->set_duration(on_attack_duration);

    add_component(spider_on_attack);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Audio effects initialized.");
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
    std::string event_name = ""; /**< String.
    Gets an event catched by the spider. */

    /* Gets event related with the spider. */
    event_name = game_event.game_event_name;

    int actual_position = 0; /**< Integer.
    Define the actual position of the spider on the screen. */

    const int distance_to_move = 10;

    /* Check if the spider gets an event to move to the left direction. */
    if (event_name == "MOVE_LEFT"
        && !engine::GameObject::on_limit_of_level) {

        /* The spider increments its actual position. */
        actual_position = get_position_x();
        set_position_x(actual_position + distance_to_move);
    }
    /* Check if the spider gets an event to move to the right direction. */
    else if (event_name == "MOVE_RIGHT"
        && !engine::GameObject::on_limit_of_level) {

        /* The spider decrements its actual position. */
        actual_position = get_position_x();
        set_position_x(actual_position - distance_to_move);
    }
    else {
        /* Event name is not found. */
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
    LittleGirl* little_girl = nullptr; /**< LittleGirl.
    Gets as observable that tells when little_girl is next. */

    little_girl = dynamic_cast<LittleGirl *>(game_object);

    /* Notify if little_girl exists, moving to her direction. */
    if (little_girl) {
        /* The spider moves in direction of the girl. */
        move(little_girl);
    }
    else {
        /* The spider stays in the same place. */
    }
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
    /* Gets Y positions of the spider and of the girl. */
    float spider_position_y = 0;
    spider_position_y = get_position_y();

    float girl_position_y = 0;
    girl_position_y = girl->get_position_y();

    //100 is the diference of girl position_y and spider position_y

    const int height_difference = 100;

    /* Verifies if the spider and the girl is at the same height. */
    if (spider_position_y + height_difference == girl_position_y) {
        /* The spider is in the same position that the girl. */
        same_nivel = true;
    }
    else {
        /* The spider isn't in the same position that the girl. */
        same_nivel = false;
    }

    /* Verifies if the spider is dead. */
    if (get_state("ACTION_STATE") == "DYING") {
        return;
    }
    else {
        /* The spider still alive. */
    }

    /* Verifies if the actual animation of the spider is finished. */
    if (get_actual_animation()->is_finished){
        /* Set spider's actual state with a normal state. */
        states.set_state("ACTION_STATE","NORMAL");
    }
    else {
        /* The spider's actual animation is not finished yet. */
    }

    /* Verifies if the spider is on attack. */
    if(get_state("ACTION_STATE") == "ON_ATTTACK") {
        return;
    }
    else {
        /* The spider isn't under attack. */
    }

    /* Gets X positions of the spider and of the girl and initializes
    they distance between them. */
    int distance_from_girl = 0;

    float spider_position = 0;
    spider_position = get_position_x();

    float girl_position = 0;
    girl_position = girl->get_position_x();

    /* Verifies the spider position on the X axis to define
    the spider's state. */
    if (spider_position > girl_position) {
        /* Sets spider's state to looking to the left. */
        states.set_state("X_STATE","LOOKING_LEFT");
        /* Calculates the distance between the spider and the girl. */
        distance_from_girl = spider_position - girl_position;

        const int max_left_area = 300;
        const int left_vision_area = 50;

        /* Check if the girl is too far away behind the spider. */
        if (distance_from_girl > max_left_area) {
            /* Sets a idle state to spider's state. */
            set_actual_animation(animations["idle_left_animation"]);
        }
        /* Check if the girl is in the fields vision of the spider. */
        else {
            /* Sets a normal state to spider's states. */
            states.set_state("ACTION_STATE","NORMAL");

            /* Check if the girl is next or far away to the spider. */
            if (distance_from_girl >= left_vision_area) {
                /* Updates the X position of the spider, making it walking.*/
                set_position_x(get_position_x() - (same_nivel? 8 : 3));
                /* Initiates the animation that show the spider
                walking to the left. */
                set_actual_animation(animations["walking_left_animation"]);
            }
            else {
                /* Check if the spider and the girl is in the same nivel.*/
                if (same_nivel) {
                    /* Calls the method that build the attack action. */
                    attack();
                }
                else {
                    /* The girl is not in the same nivel that the spider.*/
                }
            }
        }
    }
    else {
        /* Sets spider's state to looking to the right. */
        states.set_state("X_STATE","LOOKING_RIGHT");
        distance_from_girl = girl_position - spider_position;

        const int max_right_area = 588;
        const int right_vision_area = 150;

        /* Check if the spider is to far away in front of spider. */
        if (distance_from_girl > max_right_area) {
            /* Sets a idle state to spider's state. */
            set_actual_animation(animations["idle_right_animation"]);
        }
        else {
            /* Check if the girl is in the fields vision of the spider. */
            if (distance_from_girl >= right_vision_area) {
                /* Updates the X position of the spider, making it walking.*/
                set_position_x(get_position_x() + (same_nivel? 8 : 3));
                /* Initiates the animation that show the spider
                walking to the right. */
                set_actual_animation(animations["walking_right_animation"]);
            }
            else {
                /* Check if the spider and the girl is in the same nivel. */
                if (same_nivel) {
                    /* Calls the method that build the attack action. */
                    attack();
                }
                else {
                    /* The girl is not in the same nivel that the spider.*/
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

void Spider::on_collision(
    engine::GameObject* other,
    engine::Hitbox* p_my_hitbox,
    engine::Hitbox* p_other_hitbox) {

    Platform* platform = nullptr; /**< Platform.
    References the map where is happening the collision. */
    platform = dynamic_cast<Platform *>(other);

    LittleGirl* little_girl = nullptr; /**< LittleGirl.
    References to LittleGirl object. */
    little_girl = dynamic_cast<LittleGirl *>(other);

    engine::Hitbox* my_hitbox = nullptr; /**< Hitbox.
    References to spider's hitbox. */
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);

    engine::Hitbox* other_hitbox = nullptr; /**< Hitbox.
    References to girl's hitbox. */
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

    const double stop_speed = 0.0;
    const int plataform_height = 280;

    /* Check if the spider and the girl are on collision. */
    if (get_speed_y() >= 0
        && platform
        && my_hitbox->get_name() == "spider_hitbox") {

        /* Stops the spider. */
        set_speed(std::make_pair(get_speed_x(), stop_speed));
        set_position(
            std::make_pair(get_position().first,
            other_hitbox->get_coordinates().second - plataform_height)
        );
    }
    else {
        /* The spider isn't colliding with the girl. */
    }

    /* Check if the girl is attacking the spider. */
    if (little_girl
        && little_girl->get_state("ACTION_STATE") == "ATTACKING"
        && my_hitbox->get_name() == "spider_attack"
        && little_girl->get_actual_animation()->actual_column == 2
        && get_state("X_STATE") != little_girl->get_state("X_STATE")) {

        /* Check if the spider is under attack. */
        if (get_state("ACTION_STATE") == "ON_ATTACK") {
            return;
        }
        else {
            on_attack(other);
        }
    }
    else {
        /* The girl is not attacking the spider. */
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
    DEBUG("The spider is attacking.");
    /* Sets a state that represents when spider is attacking. */
    states.set_state("ACTION_STATE","ATTACKING");
    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the spider. */

    actual_x_state = get_state("X_STATE");

    /* Check if the spider is looking to the left. */
    if (actual_x_state == "LOOKING_LEFT") {
        /* Initiates the animation that attacking left. */
        set_actual_animation(animations["attacking_left_animation"]);
        INFO("The spider is attacking to the left.");
    }
    /* Check if the spider is looking to the right. */
    else if (actual_x_state == "LOOKING_RIGHT") {
        /* Initiates the animation that attacking right. */
        set_actual_animation(animations["attacking_right_animation"]);
        INFO("The spider is attacking to the right.");
    }
    else {
        /* Warns if spider's actual state is not found . */
        WARN("Spider's actual state is not found.");
    }

    /* Starts spider's sound attack. */
    play_song("attack");
    DEBUG("The spider stop to attack.");
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
    DEBUG("The spider is under attack.");
    /* Sets a state that represents when spider is under attack. */
    states.set_state("ACTION_STATE","ON_ATTACK");
    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the spider. */

    actual_x_state = get_state("X_STATE");

    /* Damage received by the spider. */
    const int damage = 15;
    hit(game_object, 15);
    INFO("The spider take 15 of damage.");

    /* Verifies if the spider is alive. */
    if (is_alive()) {
        /* Condition that verifies if the spider is looking to the left. */
        if (actual_x_state == "LOOKING_LEFT") {
            /* Initiates the animation that show the spider
            being hitted left. */
            set_actual_animation(animations["on_attack_left_animation"]);
            INFO("The spider continues alive looking to the left.");
        }
        else if (actual_x_state == "LOOKING_RIGHT") {
            /* Initiates the animation that show the spider
            being hitted right. */
            set_actual_animation(animations["on_attack_right_animation"]);
            INFO("The spider continues alive looking to the right.");
        } else {
            /* Warns if the spider's actual state is not found. */
            WARN("The actual state of the spider is invalid.");
        }
        /* Starts song when the spider is under attack. */
        play_song("hit_me");
    } else {
        /* Informs that the spider is dead. */
        INFO("The spider is dead.");
    }

    DEBUG("The spider is no longer under attack.");
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
    DEBUG("The spider is dying.");
    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the spider. */

    actual_x_state = get_state("X_STATE");

    /* Check if the spider is looking to the left. */
    if (actual_x_state == "LOOKING_LEFT") {
        /* Sets a state that represents when spider is dead. */
        states.set_state("ACTION_STATE", "DYING");
        /* Initiates the animation that show the spider dying to the left.*/
        set_actual_animation(animations["dying_left_animation"]);
        INFO("The spider die looking to the left.");
    }
    /* Check if the spider is looking to the right. */
    else if (actual_x_state == "LOOKING_RIGHT") {
        /* Sets a state that represents when spider is dead. */
        states.set_state("ACTION_STATE", "DYING");
        /* Initiates the animation that show the spider dying to the right.*/
        set_actual_animation(animations["dying_right_animation"]);
        INFO("The spider die looking to the right.");
    } else {
        /* Informs that the spider is dead. */
        WARN("The actual state of the spider is not found.");
    }
    /* Starts song when the spider is about to die. */
    play_song("hit_me");

    DEBUG("The spider died.");
}
