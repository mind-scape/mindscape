//TODO set render and another methods to private

#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>
#include <iostream>

namespace engine{

  class Image : public Component{
    public:
      SDL_Texture* texture;
      SDL_Renderer* renderer;
      std::string image_path;
      int width;
      int height;

      Image(SDL_Renderer* p_renderer, std::string path, std::pair<int, int> place, bool isactive, std::pair<int, int> wh): renderer(p_renderer),
                                                          texture(NULL),
                                                          image_path(path),
                                                          width(wh.first),
                                                          height(wh.second),
                                                          Component("image", place, isactive) {}
      ~Image(){}

      bool load();
      int get_width();
      int get_height();
      void free();
      void draw(int x, int y);
  };

}

#endif
