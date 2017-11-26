/**
 * @file goop.cpp
 * @brief Purpose: Contains methods to game class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "goop.hpp"
#include "platform.hpp"
#include "little_girl.hpp"
#include "log.hpp"
#include <stdlib.h>

using namespace mindscape;

/**
 * @brief Class Contructor.
 *
 * Set character Goop's firsts informations (attributes' values).
 *
 * @param name Goop's name(name of the object).
 * @param position Goop's coordinates in the game's map.
 * @param priority Goop's priority in game's execution.
 * @return void.
 */
Goop::Goop(
    std::string name,
    std::pair<int, int> position,
    int priority)
    :Enemy(
        name,
        position,
        priority,
        100
    ) {
        initialize_state_map();
        initialize_hitboxes();
        initialize_animations();
        translations = {
            {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
            {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
            {engine::KeyboardEvent::UP,"JUMP"},
            {engine::KeyboardEvent::DOWN,"CROUCH"},
        };
        initialize_as_physicable();
};

/**
 * @brief Initiates Goop's animation.
 *
 * Initiates all Goop's images.
 *
 * @return void.
 */
void Goop::initialize_animations(){
    DEBUG("Started: initialize_animation()");
    /**<
     * engine::Animation. Group of pixels that generates the image goop.
     */
    engine::Animation* goop_animation = nullptr;
    goop_animation = create_animation(
        "../assets/images/sprites/enemies/clown/clown_goop.png",
        1, 1, 3.0, "LEFT"
    );

    /*
     * This paragraph adds e activate the goop animation into the game.
     */
    goop_animation->set_values(
        std::make_pair(135, 70),
        std::make_pair(135, 70),
        std::make_pair(0, 0)
    );
    add_animation("goop_animation",goop_animation);
    goop_animation->activate();
    set_actual_animation(goop_animation);

    /**<
     * engine::Animation. Group of pixels that generates the image of the refuted goop.
     */
    engine::Animation* refuted_goop_animation = nullptr;
    refuted_goop_animation = create_animation(
        "../assets/images/sprites/enemies/clown/clown_goop_refuted.png",
        1, 1, 3.0, "LEFT"
    );

    /*
     * This paragraph set and adds the refuted goop animation into the game.
     */
    refuted_goop_animation->set_values(
        std::make_pair(135, 70),
        std::make_pair(135, 70),
        std::make_pair(0, 0)
    );
    add_animation("refuted_goop_animation",refuted_goop_animation);

    /**<
     * engine::Animation. Group of pixels that generates the image of the goop squash.
     */
    engine::Animation* goop_squash_animation = nullptr;
    goop_squash_animation = create_animation(
        "../assets/images/sprites/enemies/clown/goop_squash.png",
        1, 1, 5.0, "LEFT"
    );

    /*
     * This paragraph sets and adds the refuted goop animation into the game.
     */
    goop_squash_animation->set_values(
        std::make_pair(240, 140),
        std::make_pair(240, 140),
        std::make_pair(0, 0)
    );
    goop_squash_animation->in_loop = false;
    goop_squash_animation->is_a_final_animation = true;
    add_animation("goop_squash_animation", goop_squash_animation);

    DEBUG("Ended: initialize_animation()");
}

/**
 * @brief Creates Goop's animation.
 *
 * Creates all Goop's animation based on Goop's sprites.
 *
 * @param image_path Path of the Goop's sprite.
 * @param sprite_lines Line of the Goop's sprite.
 * @warning Limitations of sprite_lines and sprite_columns are
 * 1 to the quantity of lines/columns in the image.
 * @param sprite_columns Column of the Goop's sprite needed.
 * @param duration Duration of the Goop's image to show up.
 * @param direction Direction of the Goop's image.
 * @return engine::Animation* The animation constructed.
 */
engine::Animation* Goop::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction) {

    DEBUG("Started: create_animation() goop");

    engine::Game& game = engine::Game::get_instance(); /**< initialization of the game instance singleton */

    /**<
     * engine::Animation. Group of pixels that generates and renderer the animation.
     */
    engine::Animation* animation = nullptr;
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

  return animation;

  DEBUG("Ended: create_animation() goop")
}

/**
 * @brief Initiates Goop's physics.
 *
 * Applies physics forces in the Goop, and makes it collidable.
 *
 * @return void.
 */
void Goop::initialize_as_physicable() {
    DEBUG("Started: initialize_as_physicable()");

    engine::Physics *physics = nullptr; /**< engine::Physics. initialize the instance of the game physics. */
    physics = engine::Physics::get_instance();

    /*
     * Adds physics to goop and sets collidable
     */
    physics->add_physicable(this);

    INFO("Goop as collidable");
    collidable = true;

    DEBUG("Ended: initialize_as_physicable()");
}

/**
 * @brief Inicializes Goop Hitbox.
 *
 * Inicializes coordinates of the Goop's hitboxes.
 * @return void.
 */
void Goop::initialize_hitboxes() {
    DEBUG("Started: initialize goop add hitbox");

    engine::Game& game = engine::Game::get_instance(); /**< engine::Game. initialization of the game instance singleton */
    engine::Hitbox* goop_hitbox = nullptr; /**< engine::Hitbox. initialization the goop as hitbox */

    /*
     * Creates a new hitbox and pass all necessary attributes.
     */
    goop_hitbox = new engine::Hitbox(
        "goop_hitbox",
        this->get_position(),
        std::make_pair(10, 45),
        std::make_pair(60,8),
        game.get_renderer()
    );
    goop_hitbox->initialize();

    add_component(goop_hitbox);

    DEBUG("Ended: initialize goop add hitbox");
}

/**
 * @brief Initiates Goop's state in game's map.
 *
 * Sets Goop's coordinates in x and y axis, and Goop's action state.
 * @return void.
 */
void Goop::initialize_state_map(){
    DEBUG("Started: initialize_state_map");

    states.set_state("ACTION_STATE","NORMAL");
    states.set_state("Y_STATE","ON_GROUND");

    DEBUG("Ended: initialize_state_map");
}

/**
 * @brief Gets Goop's event.
 *
 * Gets actual animation, position and modifies position in axis x if needed.
 *
 * @param game_event Object of the current game event.
 * @return void.
 */
void Goop::on_event(GameEvent game_event) {
    DEBUG("Started: on_event()");

    std::string event_name = ""; /**< string. Initialization the goop as hitbox */
    event_name = game_event.game_event_name;

    static float speed_x = 0; /**< string. Initialization the goop as hitbox */
    speed_x = get_speed_x();

    if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {
        /* If event is move to left */
        set_speed_x(speed_x + 5);
    }

    else if(event_name == "MOVE_RIGHT" &&
            !engine::GameObject::on_limit_of_level) {
        /* If event is move to right */
        set_speed_x(speed_x - 5);
    }

    DEBUG("Ended: on_event()");
}

/**
 * @brief Describes action when the Goop collides.
 *
 * Produces the effect in Fox when it collides with another object.
 *
 * @param other Another game object.
 * @param p_my_hitbox Goop's hitbox.
 * @param p_other_object Other object's hitbox.
 * @return void.
 */
void Goop::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox,
        engine::Hitbox* p_other_hitbox) {
    DEBUG("Started: on_collision()");

    Platform* platform = nullptr; /**< Plataform. Initialization the platform (floor) */
    engine::Hitbox* my_hitbox = nullptr; /**< Hitbox. Initialization the goop hitbox */
    engine::Hitbox* other_hitbox = nullptr; /**< Hitbox. Initialization the other hitbox */

    platform = dynamic_cast<Platform *>(other);
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

    if(get_speed_y() >= 0 && platform &&
            my_hitbox->get_name() == "goop_hitbox") {

        /* If speed on the axis y is 0 or more and my_hitbox is goop hitbox. */

        set_speed_y(0.0);
        set_position_y(other_hitbox->get_coordinates().second - 30);
        states.set_state("Y_STATE","ON_GROUND");
        engine::Game::get_instance()
            .get_actual_scene()->deactivate_game_object(name);

        free();
    }

    DEBUG("Ended: on_collision()");
}
