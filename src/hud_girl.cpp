#include "../include/hud_girl.hpp"

using namespace mindscape;

HudGirl::HudGirl(){
  initialize_animations();
}

void HudGirl::notify(engine::Observable* game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    // implement
  }
}

void HudGirl::on_event(GameEvent event){
}

void HudGirl::initialize_animations(){
}
