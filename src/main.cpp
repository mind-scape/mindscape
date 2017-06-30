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

  /************************LEVEL*1**********************************************/
  std::pair<int, int> anotherplace (0, 0);
  std::pair<int, int> anotherotherplace (250,400);
  game.set_game_background_color(0xEB, 0xA7, 0xFC, 0xFF);

  Image* images2 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/1.png", true, std::make_pair(0, 0), 1);
  Image* images9 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/2.png", true, std::make_pair(0, 0), 1);
  Image* images8 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/3.png", true, std::make_pair(0, 0), 1);

  Animation* images4 = new Animation(game.get_renderer(), "../assets/images/sprites/fox/fox_running_right.png", true, std::make_pair(0, 0),1,1,9,0.9,true,"RIGHT");
  Animation* images5 = new Animation(game.get_renderer(), "../assets/images/sprites/fox/fox_running_left.png", false, std::make_pair(0, 0),1,1,9,0.9,true,"LEFT");

  images2-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images9-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images8-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));

  images4-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));
  images5-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));

  mindscape::Background* background = new mindscape::Background("background", anotherplace, 1);
  mindscape::Background* background2 = new mindscape::Background("background2", anotherplace, 2);
  GameObject* background3 = new mindscape::Background("background3", anotherplace, 3);

  background->paralax = 2;
  background2->paralax = 4;

  GameObject* fox = new mindscape::Fox("fox", anotherotherplace, 4);

  background->add_component(images2);
  background2->add_component(images9);
  background3->add_component(images8);

  fox->add_component(images4);
  fox->add_component(images5);
  GameObject* star = new mindscape::Star("star", std::make_pair(600, 400), 20);

  mindscape::LevelFactory *level_factory = new mindscape::LevelFactory();
  Level* level1 = level_factory->fabricate_level("data/1.level.dat");

  level1->add_object(fox);
  level1->add_object(star);
  level1->add_object(background);
  level1->add_object(background2);
  level1->add_object(background3);
  level1->activate_game_object(star);
  level1->activate_game_object(fox);
  level1->activate_game_object(background);
  level1->activate_game_object(background2);
  level1->activate_game_object(background3);
  /********************************************************************************/

  /**********************MAIN*MEUNU********************************************/

  Level * menu = new Level();

  Image *m_background = new Image(game.get_renderer(), "../assets/images/scenes/main_menu/menu_screen2.jpg", true, std::make_pair(0,0),1);
  m_background->set_values(std::make_pair(1024,576), std::make_pair(1024,576), std::make_pair(0,0));
  GameObject* menu_background = new GameObject("menu_background", std::make_pair(0,0),1,{});
  menu_background->add_component(m_background);

  Text* sel = new Text(">", "../assets/fonts/FFF_Tusj.ttf", 35, game.get_renderer());
  GameObject* select = new mindscape::SelectArrow("select", std::make_pair(425,275),2);
  select->add_component(sel);

  Text* title = new Text("MindScape", "../assets/fonts/FFF_Tusj.ttf", 90, game.get_renderer());
  GameObject* game_title = new GameObject("game_title", std::make_pair(280, 30),2,{});
  game_title->add_component(title);

  Text* text_start = new Text("Iniciar", "../assets/fonts/FFF_Tusj.ttf", 35, game.get_renderer());
  GameObject* start = new mindscape::Button("start", std::make_pair(450, 275), 2);
  start->add_component(text_start);

  //Text* text_instructions= new Text("Ajuda", "../assets/fonts/FFF_Tusj.ttf", 35, game.get_renderer());
  //GameObject* instructions = new GameObject("instructions", std::make_pair(450, 310),2);
  //instructions->add_component("instructions", text_instructions);

  //Text* text_credits= new Text("Creditos", "../assets/fonts/FFF_Tusj.ttf", 35, game.get_renderer());
 // GameObject* credits = new GameObject("credits", std::make_pair(450, 345),2);
  //credits->add_component("credits", text_credits);

  //Text* text_exit = new Text("Sair", "../assets/fonts/FFF_Tusj.ttf", 35, game.get_renderer());
  //GameObject* exit = new GameObject("exit", std::make_pair(450, 380),2);
 // exit ->add_component("exit", text_exit);

  Audio* music = new Audio("../assets/audios/background_songs/mindscape_open3.wav", Audio::MUSIC);
  GameObject * menu_loop =  new GameObject("menu_loop", std::make_pair(0,0),1,{});
  menu_loop->add_component(music);



  menu->add_object(select);
  menu->activate_game_object(select);
  menu->add_object(start);
  menu->activate_game_object(start);
  //menu->add_object(instructions);
  //menu->activate_game_object("instructions");
  //menu->add_object(credits);
  //menu->activate_game_object("credits");
  //menu->add_object(exit);
  //menu->activate_game_object("exit");
  //menu->add_object(game_title);
  menu->activate_game_object(game_title);
  menu->add_object(menu_background);
  menu->activate_game_object(menu_background);
  menu->add_object(menu_loop);
  menu->activate_game_object(menu_loop);

  /********************************************************************************/

  game.add_scene("menu", menu);
  game.add_scene("first level", level1);
  game.change_scene("menu");

  game.run();
  return 0;
}
