/**
 * @file level.hpp
 * @brief Purpose: Contains level methods
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>
#include "scene.hpp"
#include "clown.hpp"

namespace engine {
    /**
     * @brief A Level class
     *
     * This class is dedicated to controlling the level at which the
     * character is playing.
     */

    class Level : public Scene {
    public:
        Level(){};
        ~Level(){};

        void load();
        void free();
        void draw();
    };

}

#endif
