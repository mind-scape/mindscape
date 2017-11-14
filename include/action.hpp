/**
* @file action.hpp
* @brief Purpose: Contains the Action class declaration.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

namespace mindscape {
    /**
    * @brief A Action class.
    *
    * A class responsible to ensure action handling.
    *
    */
    class Action {
        public:
            /* Struct that commands */
            typedef enum {
                CHANGE_SCENE, PAUSE_GAME, PLAY_GAME
            } Command;

        private:
            Command command;

        public:
            /* Constructor and destructor */
            Action(Command p_command):command(p_command){};
            ~Action(){};

            /* Loop method */
            void execute(std::string param);
    };
}

#endif
