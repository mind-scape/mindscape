#include <Game.hpp>

using namespace engine;

Game * Game::Getinstance(){
  if(instance != NULL){
    return instance;
  }else{
    instance = new GAME("Mind Scape",std::make_pair(600,600));
    return 
  }
}

void Game::run(){
}

