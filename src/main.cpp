#include <iostream>
#include <unordered_map>
#include <string>
#include "../include/platform.hpp"
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
#include "../include/select_arrow.hpp"
#include "../include/button.hpp"

using namespace engine;

int main(int,char**){


  Game& game = Game::get_instance();
  game.set_information(globals::game_name,globals::window_size);
  game.game_init();

  /************************LEVEL*1**********************************************/
  std::pair<int, int> place (416, 335);
  std::pair<int, int> anotherplace (0, 0);
  std::pair<int, int> anotherotherplace (250,400);

  Image* images1 = new Image(game.renderer, "../assets/images/menina_correndo_direita.png", true, std::make_pair(0, 0), 2);
  Image* images2 = new Image(game.renderer, "../assets/images/scene_1_red.png", true, std::make_pair(0, 0), 2);
  Image* images3 = new Image(game.renderer, "../assets/images/menina_correndo_esquerda.png",

  false, std::make_pair(0, 0), 2);

  Image* images4 = new Image(game.renderer, "../assets/images/raposa_correndo_direita.png", true, std::make_pair(0, 0), 2);
  Image* images5 = new Image(game.renderer, "../assets/images/raposa_correndo_esquerda.png", false, std::make_pair(0, 0), 2);
  Image* images6 = new Image(game.renderer, "../assets/images/plataforma.png", true, std::make_pair(0,0), 2);

  images1-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));
  images2-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images3-> set_values(std::make_pair(192, 192), std::make_pair(192, 192), std::make_pair(0, 0));
  images4-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));
  images5-> set_values(std::make_pair(120, 120), std::make_pair(120, 120), std::make_pair(0, 0));
  images6-> set_values(std::make_pair(507, 256), std::make_pair(507, 256), std::make_pair(0, 0));

  GameObject* little_girl = new LittleGirl("little_girl", place, 52);
  little_girl->hitbox = {
    .x = little_girl->position.first,
    .y = little_girl->position.second,
    .w = 50,
    .h = 1
  };
  little_girl->collidable = true;

  GameObject* background = new Background("background", anotherplace, 1);
  GameObject* fox = new Fox("fox", anotherotherplace, 52);

  GameObject* platform = new Platform("platform", std::make_pair(400, 250), 2);
  platform->hitbox = {
    .x = platform->position.first + 70,
    .y = platform->position.second + 35,
    .w = 270,
    .h = 10
  };

  little_girl->add_component("image", images1);
  little_girl->add_component("image", images3);
  background->add_component("image", images2);
  fox->add_component("image",images4);
  fox->add_component("image",images5);
  platform->add_component("image", images6);

  Level* level1 = new Level();

  level1->add_object(little_girl);
  level1->add_object(fox);
  level1->add_object(background);
  level1->add_object(platform);
  level1->activate_game_object("little_girl");
  level1->activate_game_object("background");
  level1->activate_game_object("fox");
  level1->activate_game_object("platform");
  /********************************************************************************/

  /**********************MAIN*MEUNU********************************************/

  Level * menu = new Level();

  Image *m_background = new Image(game.renderer, "../assets/images/menu_screen.jpg", true, std::make_pair(0,0),1);
  m_background->set_values(std::make_pair(1024,576), std::make_pair(1024,576), std::make_pair(0,0));
  GameObject* menu_background = new GameObject("menu_background", std::make_pair(0,0),1,{});
  menu_background->add_component("menu_background", m_background);

  Text* sel = new Text(">", "../assets/fonts/FFF_Tusj.ttf", 35, game.renderer);
  GameObject* select = new SelectArrow("select", std::make_pair(425,275),2);
  select->add_component("select", sel);

  Text* title = new Text("MindScape", "../assets/fonts/FFF_Tusj.ttf", 90, game.renderer);
  GameObject* game_title = new GameObject("game_title", std::make_pair(280, 30),2,{});
  // game_title->add_component("game_title", title);

  Text* text_start = new Text("Iniciar", "../assets/fonts/FFF_Tusj.ttf", 35, game.renderer);
  GameObject* start = new Button("start", std::make_pair(450, 275), 2);
  start->add_component("start", text_start);

  // Text* text_instructions= new Text("Ajuda", "../assets/fonts/FFF_Tusj.ttf", 35, game.renderer);
  // GameObject* instructions = new GameObject("instructions", std::make_pair(450, 310),2);
  // instructions->add_component("instructions", text_instructions);
  //
  // Text* text_credits= new Text("Creditos", "../assets/fonts/FFF_Tusj.ttf", 35, game.renderer);
  // GameObject* credits = new GameObject("credits", std::make_pair(450, 345),2);
  // credits->add_component("credits", text_credits);
  //
  // Text* text_exit = new Text("Sair", "../assets/fonts/FFF_Tusj.ttf", 35, game.renderer);
  // GameObject* exit = new GameObject("exit", std::make_pair(450, 380),2);
  // exit ->add_component("exit", text_exit);

  Audio* music = new Audio("../assets/audios/mindscape_open3.wav", Audio::audio_type::music);
  GameObject * menu_loop =  new GameObject("menu_loop", std::make_pair(0,0),1,{});
  menu_loop->add_component("menu_loop", music);

  menu->add_object(select);
  menu->activate_game_object("select");
  menu->add_object(start);
  menu->activate_game_object("start");
  // menu->add_object(instructions);
  // menu->activate_game_object("instructions");
  // menu->add_object(credits);
  // menu->activate_game_object("credits");
  // menu->add_object(exit);
  // menu->activate_game_object("exit");
  menu->add_object(game_title);
  menu->activate_game_object("game_title");
  menu->add_object(menu_background);
  menu->activate_game_object("menu_background");
  menu->add_object(menu_loop);
  menu->activate_game_object("menu_loop");

  /********************************************************************************/

  game.add_scene("menu", menu);
  game.add_scene("first level", level1);
  game.change_scene("menu");

  game.run();
  return 0;
}
