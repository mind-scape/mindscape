/** 
 * @file hud_girl.hpp
 * @brief Purpose: Contains methods to game class' management.
 * 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef HUD_GIRL_H
#define HUD_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "platform.hpp"
#include "../engine/include/observable.hpp"
#include "little_girl.hpp"
#include "star.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape{
  
    /** 
     * @brief A Hud Girl class.
     * 
     * The class Hud Girl has attributes and methods for the Little Girl's 
     * health bar.
     */ 
    class HudGirl : public engine::GameObject {
        private:
            void initialize_animations();
            engine::Image* create_image();
            
            engine::Animation* create_animation(
                std::string path,
                int sprite_lines,
                int sprite_columns,
                double duration,
                std::string direction
            );

        public:
            HudGirl(std::string name, std::pair<int, int> position, 
                    int priority);
            ~HudGirl(){};

            void notify(engine::Observable*);
    };
}

#endif
