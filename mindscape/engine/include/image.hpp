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
      std::pair<int, int> dimensionOnScreen, dimensionOnTexture, coordinatesOnTexture;

      Image(SDL_Renderer* p_renderer, std::string path, bool isactive, std::pair<int, int> displacement): renderer(p_renderer),
                                                          texture(NULL),
                                                          image_path(path),
                                                          Component("image", displacement, isactive) {}

      ~Image(){}

      void set_values(std::pair<int, int> dimensionOnScreen, std::pair<int, int> dimensionOnTexture, std::pair<int, int> coordinatesOnTexture);
      bool load();
      int get_width();
      int get_height();
      void free();
      void draw(int x, int y);
  };

}

#endif
