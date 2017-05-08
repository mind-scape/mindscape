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

using namespace engine;

int main(int,char**){
  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.game_init();
  std::pair<int, int> place (0, 0);
  std::pair<int, int> anotherplace (100, 100);
  std::pair<int, int> whfirstimage (600, 800);
  std::pair<int, int> whsecondimage (108, 140);
  std::pair<int, int> titleplace (0, 400);
  Image* images1 = new Image(game.renderer, "../assets/images/scott.png", place, true, whfirstimage);
  Image* images2 = new Image(game.renderer, "../assets/images/background.png", place, true, whsecondimage);
  Audio* music = new Audio("../assets/audios/loop1-1.mp3", Audio::audio_type::music);
  Text* title = new Text("MindScape", "../assets/fonts/FFF_Tusj.ttf", 120, game.renderer);
  GameObject* boy = new GameObject("boy", anotherplace);
  GameObject* background = new GameObject("background", place);
  GameObject* audio_loop = new GameObject("audio_loop", place);
  GameObject* title_menu = new GameObject("title", titleplace);
  boy->add_component("image", images1);
  background->add_component("image", images2);
  audio_loop-> add_component("audio", music);
  title_menu-> add_component("title_menu", title);

  Level* level1 = new Level();
  level1->add_object("boy", boy);
  level1->add_object("background", background);
  level1->add_object("audio_loop", audio_loop);
  level1->add_object("title", title_menu);
  game.add_scene("first level", level1);
  game.change_scene(level1);
  game.run();

  return 0;
}
