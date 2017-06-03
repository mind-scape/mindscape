#include "../include/button.hpp"

void Button::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "ENTER"){
    engine::Game* game = &(engine::Game::get_instance());
    game->change_scene("first level");
  }
}

void Button::update(){}
