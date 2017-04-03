#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2basics.hpp>

namespace engine{
    
  class Texture{
    public:
      Texture(){}  
      ~Texture()

      bool loadImageFromFile( std::string image_path, SDL_Renderer * renderer );
      int setWidth();
      int setHeight();
      void free();

    private:
      int width;
      int height;

      SDL_Texture * texture;
        
  } 

}
