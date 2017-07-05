#include <iostream>
#include <unordered_map>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/text.hpp"
#include "../engine/include/scene.hpp"
#include "../engine/include/level.hpp"
#include "../engine/include/physics.hpp"
#include "../engine/include/animation.hpp"
#include "mindscape_scenes.hpp"
#include "globals.hpp"
#include "background.hpp"
#include "fox.hpp"
#include "select_arrow.hpp"
#include "button.hpp"
#include "level_factory.hpp"
#include "spider.hpp"
#include "scorpion.hpp"
#include "star.hpp"

using namespace engine;

int main(int,char**){
  Game& game = Game::initialize(globals::game_name, globals::window_size);


  Level* level1 = create_level_1(game);
  Level * menu = create_main_menu(game);


  game.add_scene("menu", menu);
  game.add_scene("first level", level1);
  game.change_scene("menu");

  game.run();
  return 0;
}
