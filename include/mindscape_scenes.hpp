#ifndef MINDSCAPE_SCENES_H
#define MINDSCAPE_SCANES_H

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

namespace engine{

Level * create_level_1(Game game){
  std::pair<int, int> anotherplace (0, 0);
  std::pair<int, int> anotherotherplace (250,400);
  game.set_game_background_color(0xEB, 0xA7, 0xFC, 0xFF);

  Image* images2 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/1.png", true, std::make_pair(0, 0), 1);
  Image* images9 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/2.png", true, std::make_pair(0, 0), 1);
  Image* images8 = new Image(game.get_renderer(), "../assets/images/scenes/test_scene/3.png", true, std::make_pair(0, 0), 1);

  images2-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images9-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));
  images8-> set_values(std::make_pair(1024, 576), std::make_pair(1024, 576), std::make_pair(0, 0));

  mindscape::Background* background = new mindscape::Background("background", anotherplace, 1);
  mindscape::Background* background2 = new mindscape::Background("background2", anotherplace, 2);
  GameObject* background3 = new mindscape::Background("background3", anotherplace, 3);

  background->add_component(images2);
  background2->add_component(images9);
  background3->add_component(images8);

  GameObject* star = new mindscape::Star("star", std::make_pair(700, 520), 20);
  GameObject* star2 = new mindscape::Star("star2", std::make_pair(750, 520), 20);
  GameObject* star3 = new mindscape::Star("star3", std::make_pair(800, 520), 20);
  GameObject* star4 = new mindscape::Star("star4", std::make_pair(850, 520), 20);
  GameObject* star5 = new mindscape::Star("star5", std::make_pair(900, 520), 20);
  GameObject* star6 = new mindscape::Star("star6", std::make_pair(950, 520), 20);

  mindscape::LevelFactory *level_factory = new mindscape::LevelFactory();
  Level* level1 = level_factory->fabricate_level("data/1.level.dat");

  level1->add_object(star);
  level1->activate_game_object(star);
  level1->add_object(star2);
  level1->activate_game_object(star2);
  level1->add_object(star3);
  level1->activate_game_object(star3);
  level1->add_object(star4);
  level1->activate_game_object(star4);
  level1->add_object(star5);
  level1->activate_game_object(star5);
  level1->add_object(star6);
  level1->activate_game_object(star6);


  return level1;
}


Level * create_main_menu(Game game){


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

  Audio* music = new Audio("../assets/audios/background_songs/mindscape_open3.wav", Audio::MUSIC);
  GameObject * menu_loop =  new GameObject("menu_loop", std::make_pair(0,0),1,{});
  music->set_music_volume(30);
  menu_loop->add_component(music);



  menu->add_object(select);
  menu->activate_game_object(select);
  menu->add_object(start);
  menu->activate_game_object(start);
  menu->activate_game_object(game_title);
  menu->add_object(menu_background);
  menu->activate_game_object(menu_background);
  menu->add_object(menu_loop);
  menu->activate_game_object(menu_loop);

  return menu;
}

}

#endif