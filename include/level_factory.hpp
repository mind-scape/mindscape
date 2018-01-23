/**
 * @file level_factory.hpp
 * @brief Purpose: Contains methods to game class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#ifndef LEVEL_FACTORY_H
#define LEVEL_FACTORY_H

#include "game_object_factory.hpp"
#include "../engine/include/level.hpp"
#include "../engine/include/game_object.hpp"
#include <string>

namespace mindscape {

    /**
     * @brief A Level Factory class.
     *
     * The class Level Factory is responsable of contruct the level element's as
     * object's dimention, displacement and coordinates.
     */
    class LevelFactory {
        public:
            /* Constructor and Desctructor */
            LevelFactory(){};
            ~LevelFactory(){};

            /* Loop method */
            void update_level(engine::Level *, std::string);

            /* Engine methods */
            std::vector<engine::GameObject *> execute_dat(engine::Level *,
                std::string);
            engine::Level * fabricate_level(std::string);
            engine::Level * fabricate_menu();
            engine::Level * fabricate_game_over();
    };
}

#endif
