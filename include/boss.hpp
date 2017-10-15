/**
* @file boss.hpp
* @brief Purpose: Contains the Boss class declaration.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#ifndef BOSS_H
#define BOSS_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "fighter.hpp"
#include "enemy.hpp"
#include <iostream>
#include <string>
#include <map>

namespace mindscape {
    /**
    * @brief A Boss class.
    *
    * A class responsible to ensure boss handling.
    *
    */
    class Boss : public Enemy {
        private:
            std::map<std::string, Enemy*> boss_parts;

        public:
            Boss(std::string name, std::pair<int, int> position, int priority,int HP = 0)
            : Enemy(name, position, priority, HP){};
            ~Boss(){};

            std::map<std::string, Enemy*> get_boss_parts();
            void set_boss_part(std::string, Enemy*);
    };

}

#endif
