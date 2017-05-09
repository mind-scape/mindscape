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


      // int width;
      // int height;

      Image(SDL_Renderer* p_renderer, std::string path, std::pair<int, int> place, bool isactive, std::pair<int, int> wh, std::pair<int, int> dimTex, std::pair<int, int> corTex): renderer(p_renderer),
                                                          texture(NULL),
                                                          image_path(path),
                                                          dimensionOnScreen(wh),
                                                          dimensionOnTexture(dimTex),
                                                          coordinatesOnTexture(corTex),
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
