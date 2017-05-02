#include <iostream>
#include <unordered_map>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/scene.hpp"
#include "../engine/include/level.hpp"
#include "../include/globals.hpp"

using namespace engine;

int main(int,char**){
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);

  Image* images1 = new Image(game.renderer, "../assets/images/scott.png");
  Image* images2 = new Image(game.renderer, "../assets/images/background.png");
  GameObject* boy = new GameObject("boy");
  GameObject* background = new GameObject("background");
  boy->add_component(images1);
  background->add_component(images2);

  Level* level1 = new Level();
  level1->add_object("boy", boy);
  level1->add_object("background", background);
  game.add_scene("first level", level1);


  game.run();

  return 0;
}
