#include <iostream>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "globals.hpp"
#include "level_factory.hpp"

using namespace mindscape;

int main(int,char**){
  engine::Game& game = engine::Game::initialize(globals::game_name, globals::window_size);

  LevelFactory *level_factory = new LevelFactory();
  engine::Level* menu = level_factory->fabricate_level("/opt/mindscape/data/menu.dat");
  game.change_scene(menu);

  game.run();
  return 0;
}
