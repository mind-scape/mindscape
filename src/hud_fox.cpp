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
        initialize_animations();
        initialize_audio_effects();
};

/**
 * @brief Initiates Hud Fox's sound effect.  
 * 
 * Sets sound effect of heart.
 * @return void.
 */
void HudFox::initialize_audio_effects() {
    engine::Audio * take_this_hp = nullptr;
    take_this_hp = new engine::Audio(
        "heart", "../assets/audios/effects_songs/mindscape_heart.wav", 
        engine::Audio::CHUNK);
    
    take_this_hp->set_duration(1);

    add_component(take_this_hp);
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
        
        bool give_hp = false; 
        give_hp = fox->get_animation_hud_fading();
        
        engine::Animation* actual = NULL;
        actual = get_actual_animation();
        
        if(actual == animations["three_star_fading"]) {
            
            if(actual->is_finished) {
                give_hp = false;
                fox->set_star_count(0);
                set_actual_animation(animations["zero_star"]);
            }
        }

        else {
            
            int count = 0;
            count = fox->get_star_count();
             
            if(count == 0) {
                
                if(!(get_actual_animation() == animations["zero_star"])) {
                    set_actual_animation(animations["zero_star"]);
                }
            }

            else if(count == 1) {
                
                if(!(get_actual_animation() == animations["one_star"])){
                    set_actual_animation(animations["one_star"]);
                }
            }

            else if(count == 2) {
                
                if(!(get_actual_animation() == animations["two_star"])) {
                    set_actual_animation(animations["two_star"]);
                }
            }

            else if(count == 3 && !give_hp) {

                if(!(get_actual_animation() == animations["three_star"])) {
                    set_actual_animation(animations["three_star"]);
                }  
            }

            else if(count == 3 && give_hp) {
                fox->set_animation_hud_fading(false);
                set_actual_animation(animations["three_star_fading"]);
                play_song("heart");
            }
        }
    }
}

/**
 * @brief Initiates Hud Fox's animation.  
 * 
 * Initiates all Hud Fox's sprites(images).
 *
 * @return void.
 */
void HudFox::initialize_animations() {

    
    engine::Animation* fox_zero_star = nullptr;
    fox_zero_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_0.png",
        1,1,0.9, "RIGHT"
    );
    add_animation("zero_star", fox_zero_star);
    
    engine::Animation* fox_one_star = nullptr;
    fox_one_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_1.png",
        1,1,0.9, "RIGHT"
    );
    add_animation("one_star", fox_one_star);
    
    engine::Animation* fox_two_star = nullptr;
    fox_two_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_2.png",
        1,1,0.9, "RIGHT"
    );
    add_animation("two_star", fox_two_star);
    
    engine::Animation* fox_three_star = nullptr;
    fox_three_star = create_animation(
        "../assets/images/sprites/hud/hud_fox_3.png",
        1,1,0.9, "RIGHT"
    );
    add_animation("three_star", fox_three_star);
    
    engine::Animation* fox_three_star_fading = nullptr;
    fox_three_star_fading = create_animation(
        "../assets/images/sprites/hud/hud_fox_3_animation.png",
        1,4,1.0, "RIGHT"
    );
    fox_three_star_fading->in_loop = false;
    add_animation("three_star_fading", fox_three_star_fading);
    
    fox_zero_star->activate();
    set_actual_animation(fox_zero_star);
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

    engine::Game& game = engine::Game::get_instance();
    
    engine::Animation* animation = nullptr;
    animation = new engine::Animation(
        game.get_renderer(),
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
        std::make_pair(170, 78),
        std::make_pair(170, 78),
        std::make_pair(0, 0)
    );

    return animation;
}
