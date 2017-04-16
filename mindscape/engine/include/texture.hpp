#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2basics.hpp"
#include <string>

namespace engine{

  class Texture{
    public:
      Texture(SDL_Renderer* p_renderer): renderer(p_renderer),texture(NULL),width(0),height(0) {}
      ~Texture(){}

      bool load_image_from_file(std::string image_path);
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
