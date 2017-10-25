/**
 * @file hud_girl.cpp
 * @brief Purpose: Contains methods to game class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/hud_girl.hpp"
#include "../engine/include/log.hpp"

using namespace mindscape;

/**
 * @brief Class Contructor.
 *
 * Sets Hud Girl's firsts informations (attributes' values).
 * (Hud Girl: Girl's health bar).
 *
 * @param name Hud Girl's name(name of the object).
 * @param position Hud Girl's coordinates in the game's map.
 * @param priority Hud Girl's priority in game's execution.
 * @return void.
 */
HudGirl::HudGirl(
    std::string name,
    std::pair<int, int> position,
    int priority)
    :engine::GameObject(
        name,
        position,
        priority,
        {
            //No engine Keyboard Event needed.
        }
    ) {

        initialize_animations();
};

/**
 * @brief Notifies Hud Girl of Girl's state.
 *
 * Verifies Girl's state and sets hp' animation depending of the quantity of
 *  life of the Girl.
 *
 * @param game_object Object for observe game's situation,
 * in this case, the Girl.
 * @return void.
 */
void HudGirl::notify(engine::Observable* game_object) {
    DEBUG("Started: HudGirl notify()");

    LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(game_object);

    if (little_girl) {
        float reducer_percentage = 0;
        int bar_size = 0;
        engine::Image* bar = nullptr;

        reducer_percentage = little_girl->get_hp()/90.0;
        bar_size = reducer_percentage * 180;
        bar = dynamic_cast<engine::Image *>(images[0]);

        bar->set_values(
            std::make_pair(bar_size, 10),
            std::make_pair(180, 10),
            std::make_pair(0, 0)
        );
    }

    DEBUG("Ended: HudGirl notify()");
}

/**
 * @brief Initiates Hud Girl's animation.
 *
 * Initiates Hud Girl's sprites(health bar with right hp).
 *
 * @return void.
 */
void HudGirl::initialize_animations() {
    DEBUG("Started: HudGirl initialize_animations()");

    engine::Image* hp = nullptr;
    hp = create_image();
    add_component(hp);

    engine::Animation* girl_hp = nullptr;
    girl_hp = create_animation(
        "../assets/images/sprites/hud/hud_girl.png",
        1,1,0.9, "RIGHT"
    );
    add_animation("girl_hp", girl_hp);
    girl_hp->activate();
    set_actual_animation(girl_hp);

    DEBUG("Ended: HudGirl initialize_animations()");
}


/**
 * @brief Creates Health bar's animation.
 *
 * Creates Health bar's animation.
 *
 * @return void.
 */
engine::Image* HudGirl::create_image() {
    DEBUG("Started: HudGirl create_image() - health_bar");

    engine::Game& game = engine::Game::get_instance();
    engine::Image* health_bar = nullptr;

    health_bar = new engine::Image(game.get_renderer(),
    "../assets/images/sprites/sprites_test/health_bar.jpg",
    true, std::make_pair(74, 64), 70);

    health_bar->set_values(
        std::make_pair(180, 10),
        std::make_pair(180, 10),
        std::make_pair(0, 0)
    );

    return health_bar;

    DEBUG("Ended: HudGirl create_image() - health_bar");
}

/**
 * @brief Creates Hud Girl's animation.
 *
 * Creates all Hud Girl's animation based on Hud Girl's sprites.
 *
 * @param image_path Path of the Hud Girl's sprite.
 * @param sprite_lines Line of the Hud Girl's sprite.
 * @warning Limitations of sprite_lines and sprite_columns are
 * 1 to the quantity of lines/columns in the image.
 * @param sprite_columns Column of the Girl's sprite needed.
 * @param duration Duration of the Hud Girl's image to show up.
 * @param direction Direction of the Hud Girl's image.
 * @return engine::Animation* The animation constructed.
 */
engine::Animation* HudGirl::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction) {
    DEBUG("Started: HudGirl create_animation()");

    engine::Game& game = engine::Game::get_instance();
    engine::Animation* animation = nullptr;
    animation = new engine::Animation(
        game.get_renderer(),
        // Hud Girl image path
        path,
        // is_active
        false,
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

    animation->set_values(
        std::make_pair(266, 90),
        std::make_pair(266, 90),
        std::make_pair(0, 0)
    );

  return animation;

  DEBUG("Ended: HudGirl create_animation()");
}
