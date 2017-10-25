/**
* @file background.hpp
* @brief Purpose: Contains the Background class declaration.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
//TODO discover how overwrite static attribute

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "globals.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
    /**
    * @brief A Background class.
    *
    * A class responsible to ensure background handling.
    *
    */
    class Background : public engine::GameObject {
        private:
            int paralax = 0; /**< Integer. Defines the paralax value to create
                                 visual effect*/

        public:
            Background(
                std::string name, /**< String. Name of the background file*/
                std::pair<int, int> position, /**< Pair<int, int>. Position of 
                                                the background*/
                int priority /**< Priority of the background .*/
            )
            :engine::GameObject(
                name, 
                position, 
                priority,
                {
                {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
                {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"}
                }
            ){
            };

            ~Background(){};
            
            void on_event(GameEvent game_event);
            
            void set_paralax(int);
            
            int get_paralax();
    };
}

#endif
