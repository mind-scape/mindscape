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

// Level * main_menu(Game game){

    //Higth, Weigths, Positions
    // std::pair<int, int> bg_dimensions(1280,960);
    // std::pair<int, int> bg_position(0,0);
    // std::pair<int, int> title_position(350,050);
    //
    // //Components
    // Image* bg_menu = new Image(game.renderer, "../assets/images/menu_screen.jpg", bg_position, true, bg_dimensions);
    // Text* title_menu = new Text("MindScape", "../assets/fonts/FFF_Tusj.ttf", 120, game.renderer);
    // Audio* music = new Audio("../assets/audios/loop1-1.mp3", Audio::audio_type::music);
    //
    // //Game Objects
    // GameObject* background = new GameObject("background_menu", bg_position);
    // GameObject* audio_loop = new GameObject("audio_loop", bg_position);
    // GameObject* title = new GameObject("title_menu", title_position);
    //
    // //Constituting game objects
    // background->add_component("bg_image", bg_menu);
    // audio_loop-> add_component("audio", music);
    // title-> add_component("title_menu", title_menu);
    //
    // Level* main_menu = new Level();
    //
    // main_menu->add_object("title_menu", title);
    // main_menu->add_object("bg_menu", background);
    // main_menu->add_object("audio_loop", audio_loop);
    //
    // return main_menu;
    //
// }

int main(int,char**){
  // Game& game = Game::get_instance();
  // game.set_information(globals::game_name,globals::window_size);
  // game.game_init();

  /*
  std::pair<int, int> place (0, 0);
  std::pair<int, int> anotherplace (100, 100);
  std::pair<int, int> whfirstimage (600, 800);
  std::pair<int, int> whsecondimage (108, 140);
  std::pair<int, int> titleplace (0, 400);
  Image* images1 = new Image(game.renderer, "../assets/images/scott.png", place, true, whfirstimage);
  Image* images2 = new Image(game.renderer, "../assets/images/background.png", place, true, whsecondimage);
  GameObject* boy = new GameObject("boy", anotherplace);
  GameObject* background = new GameObject("background", place);
  */
  // std::pair<int, int> place (100, 500);
  // std::pair<int, int> anotherplace (0, 0);
  // std::pair<int, int> whfirstimage (720, 1280);
  // std::pair<int, int> whsecondimage (108, 140);
  // Image* images1 = new Image(game.renderer, "../assets/images/scott.png", place, true, std::make_pair(108, 140), std::make_pair(108, 140), anotherplace);
  // Image* images2 = new Image(game.renderer, "../assets/images/hdcenario.jpg", place, true, std::make_pair(720, 1280), std::make_pair(720, 1280), anotherplace);
  // GameObject* boy = new GameObject("boy", place);
  // GameObject* background = new GameObject("background", anotherplace);
  // boy->add_component("image", images1);
  // background->add_component("image", images2);
  //
  //
  // Level* level1 = new Level();
  // menu = main_menu(game);
  //
  // level1->add_object("boy", boy);
  // level1->add_object("background", background);
  // game.add_scene("first level", level1);
  //
  // Level* menu = new Level();
  // menu = main_menu(game);
  //
  // game.add_scene("main_menu", menu);
  // game.change_scene(game);
  // game.run();

  return 0;
}
