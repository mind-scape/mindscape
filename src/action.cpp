#include "action.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "level_factory.hpp"
#include <iostream>

using namespace mindscape;

void Action::execute(std::string param){
  engine::Game* game = &(engine::Game::get_instance());
  if(command == Action::CHANGE_SCENE){
    LevelFactory *level_factory = new LevelFactory();
    engine::Level* level = level_factory->fabricate_level(param);
    game->change_scene(level);
    game->set_state(engine::Game::RUNNING);
for(int i = 0; i < 10; i++) std::cout << "ENTROU NO CHANGE" << std::endl;

  }else if(command == Action::PAUSE_GAME){
    game->set_state(engine::Game::PAUSED);
for(int i = 0; i < 10; i++) std::cout << "ENTROU NO PAUSE" << std::endl;

  }else if(command == Action::PLAY_GAME){
for(int i = 0; i < 10; i++) std::cout << "ENTROU NO PLAY" << std::endl;
    game->set_state(engine::Game::RUNNING);
  }
}
