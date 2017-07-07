#include "game.hpp"
#include "time.hpp"
#include <iostream>
#include <cstdio>
#include <unistd.h>

using namespace engine;

Game* Game::instance = NULL;

void throw_error(const char* function){
  printf("Something's wrong in %s\n", function);
  exit(-1);
}

Game& Game::get_instance(){
  if(!instance){
    fprintf(stderr, "You should initialize instance first");
    exit(1);
  }

  return *instance;
}

Game& Game::initialize(std::string p_name, std::pair<int, int> p_dimensions){
  if(!instance){
    instance = new Game();
    instance->set_information(p_name, p_dimensions);
    instance->init();
  }

  return *instance;
}

void Game::init(){
  int img_flags = IMG_INIT_PNG;

  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
    throw_error("SDL_Init");
  }
  if(!(IMG_Init(IMG_INIT_PNG) & img_flags)){
    throw_error("IMG_Init");
  }

  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 512 ) < 0 ){
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
  }

  if(TTF_Init() == -1){
    throw_error("TTF_Init");
  }

  window = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_UNDEFINED,
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

void Game::load_media(){
  actual_scene->load();
  loaded_media = true;
}

void Game::close(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}

bool Game::is_media_loaded(){
  return loaded_media;
}

void Game::run(){
  state = RUNNING;

  if(is_media_loaded()){

    SDL_Event e;
    EventHandler event_handler = EventHandler();
    Time::init();

    while(state != QUIT){

      unsigned now = Time::time_elapsed();
      event_handler.dispatch_pending_events(now);

      if(state != PAUSED)
        actual_scene->update();

      SDL_SetRenderDrawColor(renderer, 0xE2, 0xAC, 0xF3, 0x00);
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

void Game::set_information(std::string p_name,std::pair<int,int> p_dimensions){
  set_name(p_name);
  set_window_dimensions(p_dimensions);
}

void Game::change_scene(Scene *level){
  if(actual_scene){
    actual_scene->deactivate();
    actual_scene->free();
    delete actual_scene;
  }
  level->activate();
  actual_scene = level;
  load_media();
}

void Game::set_game_background_color(int R, int G, int B, int A){
  game_background_color = Color(R, G, B, A);
}

void Game::set_name(std::string p_name){
  name = p_name;
}

std::string Game::get_name(){
  return name;
}

void Game::set_window_dimensions(std::pair<int, int> p_window_dimensions){
  window_dimensions = p_window_dimensions;
}

std::pair<int, int> Game::get_window_dimensions(){
  return window_dimensions;
}

void Game::set_state(State p_state){
  state = p_state;
}

Game::State Game::get_state(){
  return state;
}

SDL_Renderer * Game::get_renderer(){
  return renderer;
}

Scene* Game::get_actual_scene(){
  return actual_scene;
}
