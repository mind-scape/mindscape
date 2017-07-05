#ifndef TEXT_H
#define TEXT_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include "color.hpp"
#include <string>

namespace engine{
  class Text : public Component{
    private:
      std::string text;
      std::string font_path;
      int font_size;
      Color color;
      Color background_color;
      int weigth;
      int heigth;

      SDL_Texture *texture;
      TTF_Font *font;
      SDL_Renderer *renderer;

    public:
      Text(
        SDL_Renderer* p_renderer,
        std::string name,
        std::pair<int, int> displacement,
        int priority,
        std::string p_text,
        std::string p_font_path,
        int p_font_size,
        Color p_color = Color(),
        Color p_bg_color = Color(0x00, 0x00, 0x00, 0x00))
        :text(p_text),
        font_path(p_font_path),
        font_size(p_font_size),
        color(p_color),
        background_color(p_bg_color),
        texture(NULL),
        font(NULL),
        renderer(p_renderer),
        Component(name, displacement, true, priority){}
      ~Text(){}

      bool load();
      void free();
      void draw(int, int);
  };
}
#endif
