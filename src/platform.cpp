#include "../include/platform.hpp"

using namespace engine;

void Platform::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !GameObject::on_limit_of_level){
    set_position(std::make_pair(get_position().first + 10, get_position().second));
  }else if(event_name == "MOVE_RIGHT" && !GameObject::on_limit_of_level){
    set_position(std::make_pair(get_position().first - 10, get_position().second));
  }
}
