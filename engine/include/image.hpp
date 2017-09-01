#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>
#include <iostream>

namespace engine {

    class Image : public Component {
        public:
            SDL_Texture* texture;
            SDL_Renderer* renderer;

            std::string image_path;

            std::pair<int, int> dimension_on_screen;
            std::pair<int, int> dimension_on_texture;
            std::pair<int, int> coordinates_on_texture;

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
                std::pair<int, int> dimension_on_texture,
                std::pair<int, int> coordinates_on_texture
            );

            bool load();

            int get_width();

            int get_height();

            void free();

            void draw(int x, int y);
  };
}

#endif
