#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2basics.hpp>

namespace engine{

  class Texture{
    public:
      Texture(SDL_Renderer* p_renderer): renderer(p_renderer){}
      ~Texture()

      bool loadImageFromFile(std::string image_path);
      int getWidth();
      int getHeight();
      void free();
      void render(int x,int y);

    private:
      int width;
      int height;

      SDL_Texture* texture;
      SDL_Renderer* renderer;
  }

}
