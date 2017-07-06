#include "action.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "level_factory.hpp"
#include <iostream>

using namespace mindscape;

void Action::execute(std::string param){
  switch(command){
    case CHANGE_SCENE:
      LevelFactory *level_factory = new LevelFactory();
      engine::Level* level = level_factory->fabricate_level(param);
      engine::Game* game = &(engine::Game::get_instance());
      game->change_scene(level);
      break;
  }
}
