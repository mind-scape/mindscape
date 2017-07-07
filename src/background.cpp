#include "../include/background.hpp"

using namespace mindscape;

void Background::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + paralax);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - paralax);
  }
}

void Background::set_paralax(int p_paralax){
  if(p_paralax > 10 || p_paralax < 0)
    paralax = 10;
  else
    paralax = p_paralax;
}


int Background::get_paralax(){
  return paralax;
}
