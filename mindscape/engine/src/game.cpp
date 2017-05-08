#include "game.hpp"
#include "time.hpp"
#include <iostream>

using namespace engine;

Game* Game::instance = NULL;

void throw_error(const char* function){
  printf("Something's wrong in %s\n", function);
  exit(-1);
}

Game& Game::get_instance(){
  if(!instance){
    instance = new Game();
  }
  return *instance;
}

void Game::game_init(){
  int img_flags = IMG_INIT_PNG;

  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
    throw_error("SDL_Init");
  }
  if(!(IMG_Init(IMG_INIT_PNG) & img_flags)){
    throw_error("IMG_Init");
  }

  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 512 ) < 0 )
  {
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
  }

    if(TTF_Init() == -1)
  {
    throw_error("TTF_Init");
  }

  window = SDL_CreateWindow(game_name.c_str(),SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,window_dimensions.first,
      window_dimensions.second,SDL_WINDOW_SHOWN);
  if(!window){
    throw_error("SDL_CreateWindow");
  }
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(!renderer){
    throw_error("SDL_CreateRenderer");
  }
}

bool Game::load_media(){
  for(auto scene : scenes){
    scene.second->load();
  }
  return true;
}

void Game::close(){
  //TODO add steps to deallocate all rendered textures
  // images[1]->free();
  // images[2]->free();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}

void Game::run(){
  int right_cont = 0, left_cont = 0;

  std::pair<int,int> pos; pos.first =240;pos.second = 350;

  if(load_media()){
    bool quit_event = false;

    SDL_Event e;
    while(!quit_event){
      while(SDL_PollEvent( &e ) != 0){
        if(e.type == SDL_QUIT){
          quit_event = true;
        }
      }

      //unsigned now = time::time_elapsed();
      SDL_SetRenderDrawColor(renderer,0xAA, 0xAA, 0xAA, 0xAA);
      SDL_RenderClear(renderer);
      actual_scene->draw();
      SDL_RenderPresent(renderer);
    }
  }
  else{
    printf("Medias could not be loaded\n");
  }

  close();
}

void Game::set_information(std::string name,std::pair<int,int> dimensions){
  game_name = name;
  window_dimensions = dimensions;
}

void Game::add_scene(std::string name, Scene* scene){
  scenes.insert({name, scene});
}

void Game::change_scene(Scene* scene){
  actual_scene = scene;
}
