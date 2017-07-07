#include "../include/button.hpp"

using namespace mindscape;

void Button::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "CHANGE_SCENE" ||
  event_name == "PLAY_GAME" ||
  event_name == "PAUSE_GAME"){
    action->execute(param);
  }
}

void Button::set_action(Action *p_action, std::string p_param){
  action = p_action;
  param = p_param;
}
