#include <iostream>
#include <unordered_map>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/text.hpp"
#include "../engine/include/scene.hpp"
#include "../engine/include/level.hpp"
#include "../include/globals.hpp"
#include "../include/little_girl.hpp"

using namespace engine;

int main(int,char**){
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.game_init();

  std::pair<int, int> place (400, 335);
  std::pair<int, int> anotherplace (0, 0);
  Image* images1 = new Image(game.renderer, "../assets/images/menina_correndo_direita.png", true, std::make_pair(0, 0));
  Image* images2 = new Image(game.renderer, "../assets/images/scene_1_red.png", true, std::make_pair(0, 0));
  Image* images3 = new Image(game.renderer, "../assets/images/menina_correndo_esquerda.png", false, std::make_pair(0, 0));

  images1-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));
  images2-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images3-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));

  GameObject* little_girl = new LittleGirl("little_girl", place);
  GameObject* background = new GameObject("background", anotherplace);
  little_girl->add_component("image", images1);
  little_girl->add_component("image", images3);
  background->add_component("image", images2);

  Level* level1 = new Level();

  level1->add_object("little_girl", little_girl);
  level1->add_object("background", background);
  level1->activate_game_object("little_girl");
  level1->activate_game_object("background");
  game.add_scene("first level", level1);

  game.change_scene(level1);
  game.run();
  return 0;
}
