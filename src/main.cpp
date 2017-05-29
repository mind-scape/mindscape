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
#include "../include/background.hpp"
#include "../include/fox.hpp"

using namespace engine;

int main(int,char**){
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.game_init();

  std::pair<int, int> place (416, 335);
  std::pair<int, int> anotherplace (0, 0);
  std::pair<int, int> anotherotherplace (250,400);

  Image* images1 = new Image(game.renderer, "../assets/images/menina_correndo_direita.png", true, std::make_pair(0, 0));
  Image* images2 = new Image(game.renderer, "../assets/images/scene_1_red.png", true, std::make_pair(0, 0));
  Image* images3 = new Image(game.renderer, "../assets/images/menina_correndo_esquerda.png", false, std::make_pair(0, 0));
  Image* images4 = new Image(game.renderer, "../assets/images/raposa_correndo_direita.png", true, std::make_pair(0, 0));
  Image* images5 = new Image(game.renderer, "../assets/images/raposa_correndo_esquerda.png", false, std::make_pair(0, 0));

  images1-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));
  images2-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images3-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));
  images4-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));
  images5-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));

  GameObject* little_girl = new LittleGirl("LittleGirl", place);
  GameObject* background = new Background("Background", anotherplace);
  GameObject* fox = new Fox("Fox", anotherotherplace);
  
  little_girl->add_component("image", images1);
  little_girl->add_component("image", images3);
  background->add_component("image", images2);
  fox->add_component("image",images4);
  fox->add_component("image",images5);

  Level* level1 = new Level();

  level1->add_object("little_girl", little_girl);
  level1->add_object("fox", fox);
  level1->add_object("background", background);
  level1->activate_game_object("little_girl");
  level1->activate_game_object("background");
  level1->activate_game_object("fox");
  
game.add_scene("first level", level1);

  game.change_scene(level1);
  game.run();
  return 0;
}
