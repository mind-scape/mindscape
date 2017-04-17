#include <iostream>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/image.hpp"
#include "../include/globals.hpp"

using namespace engine;

int main(int,char**){
  
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.run();

  return 0;
}
