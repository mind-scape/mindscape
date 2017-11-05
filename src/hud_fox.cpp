/** 
 * @file hud_fox.cpp
 * @brief Purpose: Contains methods to game class' management.
 * 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#include "../include/hud_fox.hpp"
#include "../engine/include/log.hpp"

using namespace mindscape;

/**
 * @brief Class Contructor.  
 * 
 * Sets Hud Fox's firsts informations (attributes' values).
 * (Hud Fox: Fox's health bar).  
 *
 * @param name Hud Fox's name(name of the object).
 * @param position Hud Fox's coordinates in the game's map.
 * @param priority Hud Fox's priority in game's execution.  
 * @return void.
 */
HudFox::HudFox(
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
        initialize_zero_star_animations();
        initialize_one_star_animations();
        initialize_two_star_animations();
        initialize_three_star_animations();
        initialize_fading_star_animations();
        initialize_audio_effects();
};

/**
 * @brief Initiates Hud Fox's sound effect.  
 * 
 * Sets sound effect of heart.
 * @return void.
 */
void HudFox::initialize_audio_effects() {
    
    DEBUG("Started");
    
    /* Initiates sound effect */
    engine::Audio * take_this_hp = nullptr;
    take_this_hp = new engine::Audio(
        "heart", "../assets/audios/effects_songs/mindscape_heart.wav", 
        engine::Audio::CHUNK);
    
    /* Set duration of the sound effect and add component in game */
    const int sound_duration = 1; /**< Integer. Duration of the sound effect in seconds*/
    take_this_hp->set_duration(sound_duration);
    add_component(take_this_hp);

    DEBUG("Ended");
}

/**
 * @brief Notifies Hud Fox of Fox's state.  
 * 
 * Verifies Fox's state and sets stars' animation depending of the quantity of
 *  stars collected.
 *
 * @param game_object Object for observe game's situation, 
 * in this case, the Fox.
 * @return void.
 */
void HudFox::notify(engine::Observable* game_object) {
    
    Fox* fox = nullptr;
    fox = dynamic_cast<Fox *>(game_object);

    if(fox) {
    /* If the fox exists */ 
        bool give_hp = false; /*< Boolean. Boolean that defines if 
        hp is being given or not */
        give_hp = fox->get_animation_hud_fading();
        
        engine::Animation* actual = NULL;
        actual = get_actual_animation();
        
        if(actual == animations["three_star_fading"]) {
        /* If stars are fading */    
            if(actual->is_finished) {   
            /* If stars already faded */
                give_hp = false;
                const int default_star_count = 0; /**< Integer.
                Default star count. Range 0-3*/
                fox->set_star_count(default_star_count);
                set_actual_animation(animations["zero_star"]);
            }

            else {
                /* Do nothing */
            }
        }

        else {
        /* If the animation is not stars fading */  
            int count = 0; /*< Integer. Number of stars */
            count = fox->get_star_count();
             
            if(count == 0) {
            /* If there are no stars */
                if(!(get_actual_animation() == animations["zero_star"])) {
                    set_actual_animation(animations["zero_star"]);
                }

                else {
                    /* Do nothing */
                }
            }

            else if(count == 1) {
            /* If there is one star */    
                if(!(get_actual_animation() == animations["one_star"])){
                    set_actual_animation(animations["one_star"]);
                }

                else {
                    /* Do nothing */
                }
            }

            else if(count == 2) {
            /* If there are two stars */    
                if(!(get_actual_animation() == animations["two_star"])) {
                    set_actual_animation(animations["two_star"]);
                }

                else {
                    /* Do nothing */
                }
            }

            else if(count == 3 && !give_hp) {
            /* If there are three stars and is not giving hp */
                if(!(get_actual_animation() == animations["three_star"])) {
                    set_actual_animation(animations["three_star"]);
                } 
                else {
                    /* Do nothing */
                }
            }

            else if(count == 3 && give_hp) {
            /* If there are three stars and is giving hp */
                fox->set_animation_hud_fading(false);
                set_actual_animation(animations["three_star_fading"]);
                play_song("heart");
            }

            else {
                /* Do nothing */
            }
        }
    }

    else {
        /* Do nothing */
        WARN("HudFox: Fox IS NULL");
    }

}

/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates zero star Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_zero_star_animations() {

    DEBUG("Started");
    const int default_sprite_line = 1; /**< Integer. Default sprite line, RANGE 1 */
    const int default_sprite_column = 1;  /**< Integer. Default sprite column, RANGE 1 */
    const double default_animation_duration = 0.9;  /**< Double. Default animation 
    duration in seconds */


    engine::Animation* fox_zero_star = nullptr;
    fox_zero_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_0.png",
        default_sprite_line, default_sprite_column, default_animation_duration,
        "RIGHT"
    );
    add_animation("zero_star", fox_zero_star);
        
    fox_zero_star->activate();
    set_actual_animation(fox_zero_star);

}

/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates on star Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_one_star_animations() {

    DEBUG("Started");
    const int default_sprite_line = 1; /**< Integer. Default sprite line, RANGE 1 */
    const int default_sprite_column = 1;  /**< Integer. Default sprite column, RANGE 1 */
    const double default_animation_duration = 0.9;  /**< Double. Default animation 
    duration in seconds */
    
    engine::Animation* fox_one_star = nullptr;
    fox_one_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_1.png",
        default_sprite_line, default_sprite_column, default_animation_duration,
        "RIGHT"
    );
    add_animation("one_star", fox_one_star);
}
/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates two star Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_two_star_animations() {

    DEBUG("Started");
    const int default_sprite_line = 1; /**< Integer. Default sprite line, RANGE 1 */
    const int default_sprite_column = 1;  /**< Integer. Default sprite column, RANGE 1 */
    const double default_animation_duration = 0.9;  /**< Double. Default animation 
    duration in seconds */

    engine::Animation* fox_two_star = nullptr;
    fox_two_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_2.png",
        default_sprite_line, default_sprite_column, default_animation_duration,
        "RIGHT"
    );
    add_animation("two_star", fox_two_star);
}

/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates three Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_three_star_animations() {

    DEBUG("Started");
    const int default_sprite_line = 1; /**< Integer. Default sprite line, RANGE 1 */
    const int default_sprite_column = 1;  /**< Integer. Default sprite column, RANGE 1 */
    const double default_animation_duration = 0.9;  /**< Double. Default animation 
    duration in seconds */    
    engine::Animation* fox_three_star = nullptr;
    fox_three_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_3.png",
        default_sprite_line, default_sprite_column, default_animation_duration,
        "RIGHT"
    );
    add_animation("three_star", fox_three_star);
}

/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates fading star Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_fading_star_animations() {

    DEBUG("Started");
    const int default_sprite_line = 1; /**< Integer. Default sprite line, RANGE 1 */
    const int sprite_columns_tree_star = 4; /**< Default sprite column of tree 
    star fading */
    const double duration_tree_star = 1.0; /**< Default duration of tree 
    star fading in seconds */

    engine::Animation* fox_three_star_fading = nullptr;
    fox_three_star_fading = create_animation(
        "../assets/images/sprites/hud/hud_fox_3_animation.png",
        default_sprite_line, sprite_columns_tree_star, duration_tree_star,
        "RIGHT"
    );
    fox_three_star_fading->in_loop = false;
    add_animation("three_star_fading", fox_three_star_fading);

    DEBUG("Ended");
}

/**
 * @brief Creates Hud Fox's animation.  
 * 
 * Creates all Hud Fox's animation based on Hud Fox's sprites.
 *
 * @param image_path Path of the Hud Fox's sprite. 
 * @param sprite_lines Line of the Hud Fox's sprite. 
 * @warning Limitations of sprite_lines and sprite_columns are
 * 1 to the quantity of lines/columns in the image.
 * @param sprite_columns Column of the Fox's sprite needed.
 * @param duration Duration of the Hud Fox's image to show up.
 * @param direction Direction of the Hud Fox's image.
 * @return engine::Animation* The animation constructed.
 */
engine::Animation* HudFox::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction) {

    DEBUG("Started");
    engine::Game& game = engine::Game::get_instance();
    
    /* Constants for default animation creation */
    const bool default_is_active = false;
    const std::pair<int, int> default_displacement = std::make_pair(0, 0);
    const int default_priority = 1;
    const bool default_in_loop = true;
    
    engine::Animation* animation = nullptr;
    animation = new engine::Animation(
        game.get_renderer(),
        path, 
        default_is_active,               
        default_displacement, 
        default_priority,                    
        sprite_lines,         
        sprite_columns,    
        duration,            
        default_in_loop,                 
        direction            
    );


    /* Defaults dimensions and coordinates of hud fox in pixels */
    const std::pair<int, int> default_dimensions_hud_fox = 
        std::make_pair(170, 78);
    const std::pair<int, int> coordinates_on_texture_hud_fox = 
        std::make_pair(0, 0);

    animation->set_values(
        default_dimensions_hud_fox,
        default_dimensions_hud_fox ,
        coordinates_on_texture_hud_fox
    );

    DEBUG("Ended");
    
    return animation;
}
