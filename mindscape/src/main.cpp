#include <iostream>
#include <unordered_map>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/scene.hpp"
#include "../engine/include/level.hpp"
#include "../include/globals.hpp"

using namespace engine;

int main(int,char**){
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.game_init();
  std::pair<int, int> place (0, 0);
  std::pair<int, int> anotherplace (100, 100);
  std::pair<int, int> whfirstimage (600, 800);
  std::pair<int, int> whsecondimage (108, 140);
  Image* images1 = new Image(game.renderer, "../assets/images/scott.png", place, true, whfirstimage);
  Image* images2 = new Image(game.renderer, "../assets/images/background.png", place, true, whsecondimage);
  Audio* music = new Audio("../assets/audio/loop1-1.mp3", "music")
  GameObject* boy = new GameObject("boy", anotherplace);
  GameObject* background = new GameObject("background", anotherplace);
  boy->add_component("image", images1);
  background->add_component("image", images2);

  Level* level1 = new Level();
  level1->add_object("boy", boy);
  level1->add_object("background", background);
  game.add_scene("first level", level1);
  game.change_scene(level1);
  game.run();

  return 0;
}
