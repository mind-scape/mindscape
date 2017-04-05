#include <Game.hpp>

using namespace engine;

Game * Game::Getinstance(){
  return instance;
}

bool Game::GameInit(){
  bool result = true;

  if(SDL_INIT(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0){
    window = SDL_CreateWindow(game_name,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,window_dimension.width,window_dimension.height,SDL_WINDOW_SHOWN);
    if(window != NULL){
      renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
      if(render != NULL){
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        if(!(IMG_INIT(IMG_INIT_PNG|IMG_INIT_BMP) & ){
          printf("SDL_image could not initialize some resources! SDL_image Error: %s",IMG_GetError());
          result = false;
        }
      }else{
        printf("Renderer could not be created! Got error: %s\n")
      }
    }else{
      printf("Window could not be created! Got error: %s\n", SDL_GetError()")
      result = false;
    }
  }else{
    printf("SDL could not initialize video or audio! Got error: %s\n",SDL_GetError());
    result = false;
  }

  return result;
}

void Game::Close(){
  //TODO add steps to deallocate all rendered textures

  SDL_DestroyRendere(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();
}
