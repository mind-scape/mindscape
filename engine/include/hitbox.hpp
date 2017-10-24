/**
 * @file hitbox.hpp
 * @brief Purpose: Contains classes to define methods management of the hitboxes.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef HITBOX_H
#define HITBOX_H

#include <string>
#include <iostream>

#include "SDL2basics.hpp"
#include "component.hpp"

namespace engine {

    /**
     * @brief A Hitbox class.
     *
     * The class hitbox has atributtes and methods for all types of hitboxes.
     * That need information about width, height, coordinates, displacement and
     * others.
     */
    class Hitbox : public Component {
        private:
            SDL_Rect hitbox; /**< SDL_Rect. A rectangle hitbox. */
            bool draw_hitbox; /**< bool. If the hitbox is drawn. */
            SDL_Texture* texture; /**< SDL_Texture. A group of pixels. */
            SDL_Renderer* renderer; /**< SDL_Renderer. Instance of the main SDL_Renderer */

        public:
            Hitbox(
                std::string name,
                std::pair<int, int> go_coordinates,
                std::pair<int, int> displacement,
                std::pair<int, int> dimensions,
                SDL_Renderer* p_render,
                bool active = true,
                int priority = 5)

            :hitbox({go_coordinates.first + displacement.first,
                go_coordinates.second + displacement.second, dimensions.first,
                dimensions.second}), draw_hitbox(true), renderer(p_render),
                Component(name, displacement, active, priority){

            };

            ~Hitbox() {

            };

            std::pair<int, int> get_dimensions();

            void set_dimensions(std::pair<int, int>);

            bool collides_with(Hitbox*);

            void set_displacement(std::pair<int, int>, std::pair<int, int>);

            std::pair<int, int> get_coordinates();

            void update(std::pair<int, int>);

            void draw();

            void initialize();

            bool wanna_draw_hitbox();
    };
}

#endif
