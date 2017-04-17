#include <iostream>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/image.hpp"
#include "../include/globals.hpp"

using namespace engine;

int main(int,char**){
  
  Game::instance.set_information(globals::game_name,globals::window_size);
  Game::instance.run();

  return 0;
}
