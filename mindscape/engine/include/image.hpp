//TODO set render and another methods to private

#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include <string>

namespace engine{

  class Image : public Component{
    public:
      SDL_Texture* texture;
      SDL_Renderer* renderer;
      std::string image_path;
      int width;
      int height;

      Image(SDL_Renderer* p_renderer, std::string path): renderer(p_renderer),
                                                          texture(NULL),
                                                          image_path(path),
                                                          width(0),
                                                          height(0),
                                                          Component("image") {}
      ~Image(){}

      bool load();
      int get_width();
      int get_height();
      void free();
      void render(int x,int y,SDL_Rect* rect);
  };

}

#endif
