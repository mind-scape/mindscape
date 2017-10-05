/**
 * @file image.hpp
 * @brief Purpose: Contains methods for managing game images
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>
#include <iostream>

namespace engine {
    /**
     * @brief A Image class
     *
     * The Image class is responsible for rendering images and textures of the game
     */

    class Image : public Component {
    public:
        SDL_Texture* texture; /**< texture from type SDL_Texture */
        SDL_Renderer* renderer; /**< renderer  from type SDL_Renderer */

        std::string image_path; /**< path of the image */

        std::pair<int, int> dimension_on_screen; /**< pair of x and y on screen dimensions */
        std::pair<int, int> dimensionOnTexture; /**< pair of dimensions on the texture */
        std::pair<int, int> coordinatesOnTexture; /**< coordinates on the texture */

        Image(SDL_Renderer* p_renderer, std::string path, bool is_active,
              std::pair<int, int> displacement, int priority
        )

                :renderer(p_renderer),
                 texture(NULL),
                 image_path(path),
                 Component("image", displacement, is_active, priority){
        }

        ~Image(){
        }

        void set_values(
                std::pair<int, int> dimension_on_screen,
                std::pair<int, int> dimensionOnTexture,
                std::pair<int, int> coordinatesOnTexture
        );

        bool load();

        int get_width();

        int get_height();

        void free();

        void draw(int x, int y);
    };
}

#endif
