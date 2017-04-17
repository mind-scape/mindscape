#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>

namespace engine{

  class Image : public Component{
    public:
      Image(SDL_Renderer* p_renderer): renderer(p_renderer),texture(NULL),width(0),height(0) {}
      ~Image(){}

      bool load(std::string image_path);
      int get_width();
      int get_height();
      void free();
      void render(int x,int y);

      SDL_Texture* texture;
      SDL_Renderer* renderer;
      int width;
      int height;
  };

}

#endif
