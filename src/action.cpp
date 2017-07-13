#include "action.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "level_factory.hpp"
#include <iostream>

using namespace mindscape;

void Action::execute(std::string param){
  engine::Game* game = &(engine::Game::get_instance());
  if(command == Action::CHANGE_SCENE){
    LevelFactory *level_factory = new LevelFactory();
    engine::Level* level = level_factory->fabricate_level(param);
    game->change_scene(level);
    game->set_state(engine::Game::RUNNING);

  }else if(command == Action::PAUSE_GAME){

    if(game->get_state() != engine::Game::PAUSED){
      engine::GameObject *pause_background = game->get_actual_scene()->get_object_by_name("pause_background");
      game->get_actual_scene()->deactivate_game_object("pause_background");
      if(pause_background)
        pause_background->free();
      
      LevelFactory *level_factory = new LevelFactory();
      level_factory->update_level(
        dynamic_cast<engine::Level *>(game->get_actual_scene()),
        "/opt/mindscape/data/pause_objects.dat"
      );
    }
    game->set_state(engine::Game::PAUSED);

  }else if(command == Action::PLAY_GAME){
    if(game->get_state() != engine::Game::PAUSED){
      engine::GameObject *pause_background = game->get_actual_scene()->get_object_by_name("pause_background");
      game->get_actual_scene()->deactivate_game_object("pause_background");
      if(pause_background)
        pause_background->free();
    }
    game->set_state(engine::Game::RUNNING);
  }
}
