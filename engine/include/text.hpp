#ifndef TEXT_H
#define TEXT_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include "color.hpp"
#include <string>

namespace engine{

    class Text : public Component{

    private:

        std::string text_for_view;
        std::string text_font_path;
        int text_font_size;
        Color text_color;
        Color text_background_color;
        int text_weigth;
        int text_heigth;

        SDL_Texture * text_texture;
        TTF_Font * text_font;
        SDL_Renderer* renderer;

    public:

        Text(std::string text,
                std::string font_path,
                int font_size,
                SDL_Renderer* p_renderer,
                Color t_color = Color(),
                Color t_bg_color =Color(0x00, 0x00, 0x00, 0x00))

            : text_for_view(text), text_font_path(font_path),text_font_size(font_size),
              renderer(p_renderer), text_color(t_color), text_background_color(t_bg_color),
              text_texture(NULL), text_font(NULL),
              text_weigth(0), text_heigth(0) {    printf("\nError in the text_texture :%s\n", SDL_GetError());
}

        ~Text(){}

        //bool init();
        //bool shutdown();

        bool load();
        void free();
        void draw(int posX, int posxY);


        //inline void enable_high_quality() {text_high_quality = true}
        //inline void disable_high_quality() {text_high_quality = false}

    };


}


#endif