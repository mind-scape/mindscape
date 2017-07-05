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

mindscape::LevelFactory *level_factory = new mindscape::LevelFactory();
//  Level* level1 = level_factory->fabricate_level("../data/1.level.dat");
//
Level* menu = level_factory->fabricate_level("../data/menu.dat");
//
//  Text* title = new Text(game.get_renderer(), "mindscape_title", std::make_pair(0,0), 5, "MindScape", "../assets/fonts/FFF_Tusj.ttf", 90);
//  GameObject* game_title = new GameObject("game_title", std::make_pair(280, 30),2,{});
//  game_title->add_component(title);
//
//  Text* text_start = new Text(game.get_renderer(), "text_start", std::make_pair(0,0), 5, "Iniciar", "../assets/fonts/FFF_Tusj.ttf", 35);
//  GameObject* start = new mindscape::Button("start", std::make_pair(450, 275), 2);
//  start->add_component(text_start);
//
//  Audio* music = new Audio("../assets/audios/background_songs/mindscape_open3.wav", Audio::MUSIC);
//  GameObject * menu_loop =  new GameObject("menu_loop", std::make_pair(0,0),1,{});
//
//  menu->add_object(start);
//  menu->activate_game_object(start);
//  menu->activate_game_object(game_title);
//  menu->add_object(menu_loop);
//  menu->activate_game_object(menu_loop);
//
//  game.add_scene("menu", menu);
//  game.add_scene("first level", level1);
  game.change_scene(menu);
  //game.change_scene("first level");

  game.run();
  return 0;
}
