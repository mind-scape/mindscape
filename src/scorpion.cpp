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
#include "../engine/include/log.hpp"
#include <stdlib.h>
#include <limits>

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
        /* Initialize all the characterists of the Scorpion. */
        initialize_state_map();
        initialize_hitboxes();
        initialize_animations();
        initialize_as_physicable();
        initialize_audio_effects();
};

void set_duration_scorpion_attacking(engine::Audio*);
void set_duration_scorpion_on_attack(engine::Audio*);

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
 *
 * @return This method returns Scorpion's animation.
 */

engine::Animation* Scorpion::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction){
    DEBUG("Creating animations.");

    engine::Game& game = engine::Game::get_instance(); /**< Game.
    Gets an instance of a game just initializated. */

    engine::Animation* animation = nullptr; /**< Animation.
    Can represents all functions about scorpion's animation. */

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
    const int size_on_screen = 320;
    const int size_of_texture = 320;

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
 * @brief Initialize Scorpion's animations.
 *
 * Define scorpion's movement and attack animation.
 *
 * @return void.
 */

void Scorpion::initialize_animations() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing animations.");

    initialize_walking_animations();
    initialize_idle_animations();
    initialize_attacking_animations();
    initialize_on_attack_animations();
    initialize_dying_animations();

    /* Ends debugger that represents the end of the method. */
    DEBUG("Animations initializated.");
}

/**
 * @brief Initialize Scorpion's walking animation.
 *
 * Define scorpion's animation to the left and the right when it is walking.
 *
 * @return void.
 */

void Scorpion::initialize_walking_animations(){
    const int walking_sprite_lines = 1;
    const int walking_sprite_columns = 5;
    const double walking_duration = 0.9;

    engine::Animation* walking_left_animation = nullptr; /**< Animation.
    Animation that represents scorpion's walk to the left. */

    /* Creates scorpion's walk movement animation to the left. */
    walking_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_walking_left.png",
        walking_sprite_lines, walking_sprite_columns, walking_duration, "LEFT"
    );

    /* Adds scorpion's walk animation to the left. */
    add_animation("walking_left_animation", walking_left_animation);

    engine::Animation* walking_right_animation = nullptr; /**< Animation.
    Animation that represents scorpion's walk to the right. */

    /* Creates scorpion's walk movement animation to the right. */
    walking_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_walking_right.png",
        walking_sprite_lines, walking_sprite_columns, walking_duration, "RIGHT"
    );

    /* Adds scorpion's walk animation to the right. */
    add_animation("walking_right_animation", walking_right_animation);
}

/**
 * @brief Activate the idle animation as the actual.
 *
 * Activate the idle right animation and sets as the actual animation of
 * the scorpion.
 *
 * @param idle_right_animation animation object which contains an
 * idle animation.
 *
 * @return void.
 */

void Scorpion::activate_idle_animation(engine::Animation* idle_right_animation){
    /* Sets scorpion's idle animation to define when its stopped. */
    idle_right_animation->activate();
    set_actual_animation(idle_right_animation);
}

/**
 * @brief Initialize Scorpion's idle animation.
 *
 * Define Scorpion's animation to the left and the right when it is in a
 * idle states.
 *
 * @return void.
 */

void Scorpion::initialize_idle_animations(){
    const int idle_sprite_lines = 1;
    const int idle_sprite_columns = 2;
    const double idle_duration = 0.9;

    engine::Animation* idle_left_animation = nullptr; /**< Animation.
    Animation that represents scorpion's idle to the left. */

    /* Creates scorpion's idle animation to the left. */
    idle_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_idle_left.png",
        idle_sprite_lines, idle_sprite_columns, idle_duration, "LEFT"
    );

    /* Adds scorpion's idle animation to the left. */
    add_animation("idle_left_animation", idle_left_animation);

    engine::Animation* idle_right_animation = nullptr; /**< Animation.
    Animation that represents scorpion's idle to the right. */

    /* Creates scorpion's idle animation to the right. */
    idle_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_idle_right.png",
        idle_sprite_lines, idle_sprite_columns, idle_duration, "RIGHT"
    );

    /* Adds scorpion's idle animation to the right. */
    add_animation("idle_right_animation", idle_right_animation);

    activate_idle_animation(idle_right_animation);
}

/**
 * @brief Inicialize Scorpion's on attack animation.
 *
 * Define Scorpion's animation to the left and the right when it is
 * under attack.
 *
 * @return void.
 */

void Scorpion::initialize_on_attack_animations(){
    const int on_attack_sprite_lines = 1;
    const int on_attack_sprite_columns = 2;
    const double on_attack_duration = 0.8;

    engine::Animation* on_attack_left_animation = nullptr; /**< Animation.
    Animation that represents scorpion's on attack to the left.  */

    /* Creates scorpion's animation to the left, when it take some damage. */
    on_attack_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_on_attack_left.png",
        on_attack_sprite_lines, on_attack_sprite_columns, on_attack_duration,
        "LEFT"
    );

    /* Adds scorpion's under attack animation to the left. */
    add_animation("on_attack_left_animation", on_attack_left_animation);

    engine::Animation* on_attack_right_animation = nullptr; /**< Animation.
    Animation that represents scorpion's on attack to the right. */

    /* Creates scorpion's animation to the right, when it take some damage. */
    on_attack_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_on_attack_right.png",
        on_attack_sprite_lines, on_attack_sprite_columns, on_attack_duration,
        "RIGHT"
    );

    /* Adds scorpion's under attack animation to the right. */
    add_animation("on_attack_right_animation", on_attack_right_animation);
}

/**
 * @brief Initialize Scorpion's attacking animations.
 *
 * Define Scorpion's animation to the left and the right when it is
 * attacking.
 *
 * @return void.
 */

void Scorpion::initialize_attacking_animations(){
    const int attacking_sprite_lines = 1;
    const int attacking_sprite_columns = 5;
    const double attacking_duration = 0.7;

    engine::Animation* attacking_left_animation = nullptr; /**< Animation.
     Animation that represents scorpion's attack to the left. */

    /* Creates scorpion's attack animation to the left. */
    attacking_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_attacking_left.png",
        attacking_sprite_lines, attacking_sprite_columns, attacking_duration,
        "LEFT"
    );

    /* Adds scorpion's attacking animation to the left. */
    add_animation("attacking_left_animation", attacking_left_animation);

    engine::Animation* attacking_right_animation = nullptr; /**< Animation.
    Animation that represents scorpion's attack to the right. */

    /* Creates scorpion's attack animation to the right. */
    attacking_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_attacking_right.png",
        attacking_sprite_lines, attacking_sprite_columns, attacking_duration,
        "RIGHT"
    );

    /* Adds scorpion's attacking animation to the right. */
    add_animation("attacking_right_animation", attacking_right_animation);
}

/**
 *
 *
 *
 *
 *
 * @return void.
 */

void define_final_left_animation(engine::Animation* dying_left_animation){
    /* Initialize booleans that references the scorpion's death animation
    process, to the left. */
    dying_left_animation->is_a_final_animation = true;
    dying_left_animation->in_loop = false;
}

/**
 * @brief Define Scorpion's final right animation.
 *
 * Sets the dying right animation as the final animation of the scorpion,
 * that works when it's dying.
 *
 * @param dying_left_animation animation object which contains a dying
 * animation.
 *
 * @return void.
 */

void define_final_right_animation(engine::Animation* dying_right_animation){
    /* Initialize booleans that references the scorpion's death animation
    process, to the right. */
    dying_right_animation->is_a_final_animation = true;
    dying_right_animation->in_loop = false;
}

/**
 * @brief Initialize Scorpion's dying animation.
 *
 * Define Scorpion's animation to the left and the right when it is dying.
 *
 * @return void.
 */

void Scorpion::initialize_dying_animations(){
    const int dying_sprite_lines = 1;
    const int dying_sprite_columns = 5;
    const double dying_duration = 0.8;

    engine::Animation* dying_left_animation = nullptr; /**< Animation.
    Animation that represents scorpion's death to the left. */

    /* Creates scorpion's death animation to the left. */
    dying_left_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_dying_left.png",
        dying_sprite_lines, dying_sprite_columns, dying_duration, "LEFT"
    );

    define_final_left_animation(dying_left_animation);

    /* Adds scorpion's dying animation to the left. */
    add_animation("dying_left_animation", dying_left_animation);

    engine::Animation* dying_right_animation = nullptr; /**< Animation.
    Animation that represents scorpion's death to the right. */

    /* Creates scorpion's death animation to the right. */
    dying_right_animation = create_animation(
        "../assets/images/sprites/enemies/scorpion/scorpion_dying_right.png",
        dying_sprite_lines, dying_sprite_columns, dying_duration, "RIGHT"
    );

    define_final_right_animation(dying_right_animation);

    /* Adds scorpion's dying animation to the right. */
    add_animation("dying_right_animation", dying_right_animation);
}

/**
 * @brief Initialize physics on Scorpion.
 *
 * This method allow that the Scorpion turns collidable.
 *
 * @return void.
 */

void Scorpion::initialize_as_physicable() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing scorpion as physicable.");

    engine::Physics *physics = nullptr; /**< Physics.
    Gets a physics instance to scorpion of a game just initialized. */

    /* Changes physics of an object catched by an instance,
    turning it collidable. */
    physics = engine::Physics::get_instance();
    physics->add_physicable(this);
    collidable = true;

    /* Ends debugger that represents the end of the method. */
    DEBUG("Scorpion is now collidable.");
}

/**
 * @brief Initialize Scorpion's hitbox when it isn't attacking.
 *
 *  Creates the scorpion hitbox when it isn't attacking.
 *
 * @param game Game object that permits get a renderer when the game is
 * running.
 *
 * @return void.
 */

void Scorpion::initialize_scorpion_hitbox(engine::Game game){
    engine::Hitbox* scorpion_hitbox = nullptr; /**< Hitbox.
    Initialize scorpion's hitbox with its height and width. */

    scorpion_hitbox = new engine::Hitbox(
        "scorpion_hitbox",
        this->get_position(),
        std::make_pair(40, 312),
        std::make_pair(180, 8),
        game.get_renderer()
    );

    /* Adds scorpion's hitbox component. */
    add_component(scorpion_hitbox);
}

/**
 * @brief Initialize Scorpion's hitbox when it is attacking.
 *
 *  Creates the scorpion hitbox when it is attacking.
 *
 * @param game Game object that permits get a renderer when the game is
 * running.
 *
 * @return void.
 */

void Scorpion::initialize_scorpion_attack_hitbox(engine::Game game){
    engine::Hitbox* scorpion_attack = nullptr; /**< Hitbox.
    Initialize scorpion's hitbox when its attack. */

    scorpion_attack = new engine::Hitbox(
        "scorpion_attack",
        this->get_position(),
        std::make_pair(5, 200),
        std::make_pair(283, 10),
        game.get_renderer()
    );

    /* Adds scorpion's attack hitbox component .*/
    add_component(scorpion_attack);
}

/**
 * @brief Initialize Scorpion's hitboxes.
 *
 * Initializes Scorpion instance hitboxes.
 *
 * @return void.
 */

void Scorpion::initialize_hitboxes() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing scorpion's hitbox.");

    engine::Game& game = engine::Game::get_instance(); /**< Game.
    Gets an instance of a game just initializated. */

    initialize_scorpion_hitbox(game);
    initialize_scorpion_attack_hitbox(game);

    /* Ends debugger that represents the end of the method. */
    DEBUG("Scorpion's hitbox initialized");
}

/**
 * @brief Initialize Scorpion's state map.
 *
 * Initialize a normal state for the scorpion.
 *
 * @return void.
 */

void Scorpion::initialize_state_map() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing scorpion's state.");
    /* Sets a normal state to scorpion's states. */
    states.set_state("ACTION_STATE", "NORMAL");
    /* Ends debugger that represents the end of the method. */
    DEBUG("Scorpion's state initialized.");
}

/**
 *
 * @brief Initialize Scorpion's attack audio.
 *
 * Creates an audio for scorpion attack animation an set duration.
 *
 * @return void.
 */

void Scorpion::initialize_scorpion_attacking_audio(){
    engine::Audio * scorpion_attacking = nullptr; /**< Audio.
    Sound that represents when scorpion is attacking. */

    /* Creates scorpion's sound when it's attacking. */
    scorpion_attacking = new engine::Audio(
        "attack",
        "../assets/audios/effects_songs/ataque_insetos.wav",
        engine::Audio::CHUNK);

    set_duration_scorpion_attacking(scorpion_attacking);

    add_component(scorpion_attacking);
}

/**
 * @brief Set the duration of the scorpion's attacking audio.
 *
 * Define a duration an sets on the Scorpion's audio object when it is
 * attacking.
 *
 * @param scorpion_attacking audio object that contains the scorpion's sound
 * when it is attacking.
 *
 * @return void.
 */

void set_duration_scorpion_attacking(engine::Audio* scorpion_attacking){
    const double duration_attacking = 0.7;

    /* Sets the duration of sound when it's attacking. */
    scorpion_attacking->set_duration(duration_attacking);
}

/**
 * @brief Initialize Scorpion's on attack audio.
 *
 * Creates an audio for scorpion on attack animation an set duration.
 *
 * @return void.
 */

void Scorpion::initialize_scorpion_on_attack_audio(){
    engine::Audio * scorpion_on_attack = nullptr; /**< Audio.
    Sound that represents when scorpion is on attack. */

    /* Creates scorpion's sound when it's hitted. */
    scorpion_on_attack = new engine::Audio(
        "hit_me",
        "../assets/audios/effects_songs/inseto_apanhando.wav",
        engine::Audio::CHUNK);

    set_duration_scorpion_on_attack(scorpion_on_attack);

    add_component(scorpion_on_attack);
}

/**
 * @brief Set the duration of the scorpion's under attack audio.
 *
 * Define a duration an sets on the Scorpion's audio object when it is
 8 under attack.
 *
 * @param scorpion_on_attack audio object that contains the scorpion's sound
 * when it is under attack.
 *
 * @return void.
 */

void set_duration_scorpion_on_attack(engine::Audio* scorpion_on_attack){
    const double on_attack_duration = 0.8;

    /* Sets the duration of sound when it's hitted. */
    scorpion_on_attack->set_duration(on_attack_duration);
}

/**
 * @brief Initialize scorpion's audio effects.
 *
 * Initialize audio effects when a scorpion is attacking or when is on attack.
 *
 * @return void.
 */

void Scorpion::initialize_audio_effects() {
    /* Starts debugger to accompany the method's development. */
    DEBUG("Initializing audio effects.");

    initialize_scorpion_attacking_audio();
    initialize_scorpion_on_attack_audio();

    /* Ends debugger that represents the end of the method. */
    DEBUG("Audio effects initialized.");
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
    std::string event_name = ""; /**< String.
    Gets an event catched by the scorpion. */

    /* Gets event related with the scorpion. */
    event_name = game_event.game_event_name;

    int actual_position = 0; /**< Integer.
    Define the actual position of the scorpion on the screen. */

    const int distance_to_move = 10;

    /* Check if the scorpion gets an event to move to the left direction. */
    if (event_name == "MOVE_LEFT"
        && !engine::GameObject::on_limit_of_level) {

        /* The scorpion increments its actual position. */
        actual_position = get_position_x();
        set_position_x(actual_position + distance_to_move);
    }
    /* Check if the scorpion gets an event to move to the right direction. */
    else if (event_name == "MOVE_RIGHT"
              && !engine::GameObject::on_limit_of_level) {

        /* The scorpion decrements its actual position. */
        actual_position = get_position_x();
        set_position_x(actual_position - distance_to_move);
    }
    /* Concludes that the event is empty. */
    else {
        /* Event name is not found. */
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
    LittleGirl* little_girl = nullptr; /**< LittleGirl.
    Gets as observable that tells when little_girl is next. */

    little_girl = dynamic_cast<LittleGirl *>(game_object);

    /* Notify if little_girl exists, moving to her direction. */
    if (little_girl) {
        /* The scorpion moves in direction of the girl. */
        move(little_girl);
    }
    else {
        /* The scorpion stays in the same place. */
    }
}

/**
 * @brief Verifies if the girl and the scorpion are in the same nivel.
 *
 * Verifies if the girl isn't above an below the scorpion.
 *
 * @param scorpion_position_y measure that informs the scorpion position in the
 * Y axis.
 * @param girl_position_y measure that informs the girl position in the Y axis.
 *
 * @return void.
 */

void Scorpion::verifies_same_nivel(float scorpion_position_y,
    float girl_position_y){
    const int height_difference = 132;

    /* Verifies if the scorpion and the girl is at the same height. */
    if (scorpion_position_y + height_difference == girl_position_y) {
        /* The scorpion is in the same position that the girl. */
        same_nivel = true;
    }
    else {
        /* The scorpion isn't in the same position that the girl. */
        same_nivel = false;
    }
}

/**
 * @brief Verifies if the actual animation is finished.
 *
 * Define a normal state if the Scorpion's actual animation is finished.
 *
 * @return void.
 */

void Scorpion::verifies_actual_animation(){
    /* Verifies if the actual animation of the scorpion is finished. */
    if(get_actual_animation()->is_finished) {
        /* Set scorpion's actual state with a normal state. */
        states.set_state("ACTION_STATE","NORMAL");
    }
    else {
        /* The scorpion's actual animation is not finished yet. */
    }
}

/**
 * @brief Verifies the distance of the scorpion from the girl in the left
 * direction.
 *
 * Sets an animation according with the distance from the girl and the fields
 * vision of the scorpion.
 *
 * @param distance_from_girl the distance of the scorpion from the girl
 * in pixels.
 * @param left_vision_area field vision of the scorpion in the left direction.
 *
 * @return void.
 */

void Scorpion::verifies_left_distance_from_girl(int distance_from_girl,
    const int left_vision_area){
    /* Check if the girl is next or far away to the scorpion. */
    if (distance_from_girl >= left_vision_area) {
        /* Updates the X position of the scorpion, making it walking.*/
        set_position_x(get_position_x() - (same_nivel? 8 : 3));
        /* Initiates the animation that show the scorpion
        walking to the left. */
        set_actual_animation(animations["walking_left_animation"]);
    }
    else {
        /* Check if the scorpion and the girl is in the same nivel.*/
        if (same_nivel) {
            /* Calls the method that build the attack action. */
            attack();
        }
        else {
            /* The girl is not in the same nivel that the scorpion.*/
        }
    }
}

/**
 * @brief Verifies the distance of the scorpion from the girl in the right
 * direction.
 *
 * Sets an animation according with the distance from the girl and the fields
 * vision of the scorpion.
 *
 * @param distance_from_girl the distance of the scorpion from the girl
 * in pixels.
 * @param right_vision_area field vision of the scorpion in the right direction.
 *
 * @return void.
 */

void Scorpion::verifies_right_distance_from_girl(int distance_from_girl,
    const int right_vision_area){
    /* Check if the girl is in the fields vision of the scorpion. */
    if (distance_from_girl >= right_vision_area) {
        /* Updates the X position of the scorpion, making it walking.*/
        set_position_x(get_position_x() + (same_nivel? 8 : 3));
        /* Initiates the animation that show the scorpion
        walking to the right. */
        set_actual_animation(animations["walking_right_animation"]);
    }
    else {
        /* Check if the scorpion and the girl is in the same nivel. */
        if (same_nivel) {
            /* Calls the method that build the attack action. */
            attack();
        }
        else {
            /* The girl is not in the same nivel that the scorpion.*/
        }
    }
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
    /* Gets Y positions of the scorpion and of the girl. */
    float scorpion_position_y = 0;
    scorpion_position_y = get_position_y();

    float girl_position_y = 0;
    girl_position_y = girl->get_position_y();

    verifies_same_nivel(scorpion_position_y, girl_position_y);

    /* Verifies if the scorpion is dying. */
    if (get_state("ACTION_STATE") == "DYING") {
        return;
    }
    else {
        /* The scorpion still alive. */
    }

    verifies_actual_animation();

    /* Verifies if the scorpion is on attack. */
    if(get_state("ACTION_STATE") == "ON_ATTACK") {
        return;
    }
    else {
        /* The scorpion isn't under attack. */
    }

    /* Gets X positions of the scorpion and of the girl and initializes
    they distance between them. */
    int distance_from_girl = 0;

    float scorpion_position = 0;
    scorpion_position = get_position_x();

    float girl_position = 0;
    girl_position = girl->get_position_x();

    /* Verifies the scorpion position on the X axis to define
    the scorpion's state. */
    if (scorpion_position > girl_position) {
        /* Sets scorpion's state to looking to the left. */
        states.set_state("X_STATE","LOOKING_LEFT");
        /* Calculates the distance between the scorpion and the girl. */
        distance_from_girl = scorpion_position - girl_position;

        const int max_left_area = 300;
        const int left_vision_area = 50;

        /* Check if the girl is too far away behind the scorpion. */
        if (distance_from_girl > max_left_area) {
            /* Sets a idle state to scorpion's state. */
            set_actual_animation(animations["idle_left_animation"]);
        }
        /* Verifies if the girl is in the fields vision of the scorpion. */
        else {
            /* Sets a normal state to scorpion's states. */
            states.set_state("ACTION_STATE","NORMAL");

            verifies_left_distance_from_girl(distance_from_girl,
                left_vision_area);
        }
    }
    else {
        /* Sets scorpion's state to looking to the right. */
        states.set_state("X_STATE","LOOKING_RIGHT");
        distance_from_girl = girl_position - scorpion_position;

        const int max_right_area = 588;
        const int right_vision_area = 200;

        /* Check if the scorpion is to far away in front of scorpion. */
        if (distance_from_girl > max_right_area) {
            /* Sets a idle state to scorpion's state. */
            set_actual_animation(animations["idle_right_animation"]);
        }
        else {

            verifies_right_distance_from_girl(distance_from_girl,
                right_vision_area);
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
    Platform* platform = nullptr; /**< Platform.
    References the map where is happening the collision. */
    platform = dynamic_cast<Platform *>(other);

    LittleGirl* little_girl = nullptr; /**< LittleGirl.
    References to LittleGirl object. */
    little_girl = dynamic_cast<LittleGirl *>(other);

    engine::Hitbox* my_hitbox = nullptr; /**< Hitbox.
    References to scorpion's hitbox. */
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);

    engine::Hitbox* other_hitbox = nullptr; /**< Hitbox.
    References to girl's hitbox. */
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

    const double stop_speed = 0.0;
    const int plataform_height = 312;

    /* Check if the scorpion and the girl are on collision. */
    if (get_speed_y() >= 0
        && platform
        && my_hitbox->get_name() == "scorpion_hitbox") {

        /* Stops the scorpion. */
        set_speed_y(stop_speed);
        set_position_y(other_hitbox->get_coordinates().second
                            - plataform_height);
    }
    else {
        /* The scorpion isn't colliding with the girl. */
    }

    /* Check if the girl is attacking the scorpion. */
    if (little_girl
        && little_girl->get_state("ACTION_STATE") == "ATTACKING"
        && my_hitbox->get_name() == "scorpion_attack"
        && little_girl->get_actual_animation()->actual_column == 2
        && get_state("X_STATE") != little_girl->get_state("X_STATE")) {

        /* Check if the scorpion is under attack. */
        if (get_state("ACTION_STATE") == "ON_ATTACK") {
            return;
        }
        else {
            on_attack(other);
        }
    }
    else {
        /* The girl is not attacking the scorpion. */
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
    DEBUG("The scorpion is attacking.");
    /* Sets a state that represents when scorpion is attacking. */
    states.set_state("ACTION_STATE","ATTACKING");
    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the scorpion. */

    actual_x_state = get_state("X_STATE");

    /* Check if the scorpion is looking to the left. */
    if (actual_x_state == "LOOKING_LEFT") {
        /* Initiates the animation that attacking left. */
        set_actual_animation(animations["attacking_left_animation"]);
        INFO("The scorpion is attacking to the left.");
    }
    /* Check if the scorpion is looking to the right. */
    else if (actual_x_state == "LOOKING_RIGHT") {
        /* Initiates the animation that attacking right. */
        set_actual_animation(animations["attacking_right_animation"]);
        INFO("The scorpion is attacking to the right.");
    }
    else {
        /* Warns if the game if not found Scorpion's actual state. */
        WARN("Scorpion's actual state is not found.");
    }

    /* Starts scorpion's sound attack. */
    play_song("attack");

    DEBUG("The scorpion stop to attack.");
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
    DEBUG("The scorpion is under attack.");
    /* Sets a state that represents when scorpion is under attack. */
    states.set_state("ACTION_STATE","ON_ATTACK");
    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the scorpion. */

    actual_x_state = get_state("X_STATE");

    /* Damage received by the scorpion. */
    const int damage = 15;
    hit(game_object, damage);
    INFO("The scorpion take 15 of damage.");

    /* Verifies if the scorpion is alive. */
    if (is_alive()) {
        /* Condition that verifies if the scorpion is looking to the left. */
        if (actual_x_state == "LOOKING_LEFT") {
            /* Initiates the animation that show the scorpion
            being hitted left. */
            set_actual_animation(animations["on_attack_left_animation"]);
            INFO("The scorpion continues alive looking to the left.");
        }
        /* Condition that verifies if the scorpion is looking to the right. */
        else if (actual_x_state == "LOOKING_RIGHT") {
            /* Initiates the animation that show the scorpion
            being hitted right. */
            set_actual_animation(animations["on_attack_right_animation"]);
            INFO("The scorpion continues alive looking to the right.");
        }
        else {
            /* Warns if the Scorpion's actual state is not found. */
            WARN("The actual state of the scorpion is invalid.");
        }

        /* Starts song when the scorpion is under attack. */
        play_song("hit_me");
    } else {
        /* Informs that the scorpion is dead. */
        INFO("The scorpion is dead.");
    }

    DEBUG("The scorpion is no longer under attack.");
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
    DEBUG("The scorpion is dying.");

    std::string actual_x_state = ""; /**< String.
    Gets the actual state of the scorpion. */

    actual_x_state = get_state("X_STATE");

    /* Check if the scorpion is looking to the left. */
    if (actual_x_state == "LOOKING_LEFT") {
        /* Sets a state that represents when scorpion is dead. */
        states.set_state("ACTION_STATE", "DYING");
        /* Initiates the animation that show the scorpion dying to the left.*/
        set_actual_animation(animations["dying_left_animation"]);
        INFO("The scorpion die looking to the left.");
    }
    /* Check if the scorpion is looking to the right. */
    else if (actual_x_state == "LOOKING_RIGHT") {
        /* Sets a state that represents when scorpion is dead. */
        states.set_state("ACTION_STATE", "DYING");
        /* Initiates the animation that show the scorpion dying to the right.*/
        set_actual_animation(animations["dying_right_animation"]);
        INFO("The scorpion die looking to the right.");
    }
    else {
        /* Warns if not found Scorpion's actual state is not found. */
        WARN("The actual state of the scorpion is not found.");
    }
    /* Starts song when the scorpion is about to die. */
    play_song("hit_me");

    /* Finishes debugger informing that the scorpion is dead. */
    DEBUG("The scorpion died.");
}
