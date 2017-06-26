#include "../include/spider.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;


void Spider::on_event(GameEvent game_event){
  move(game_event);
  attack();
}

void Spider::attack(){
  states.set_state("FIGHT_STATE","ATTACKING");
  // implement animation logic here
}

void Spider::move(GameEvent game_event){
  engine::LittleGirl* girl = engine::LittleGirl::get_instance();
  std::string event = game_event.game_event_name;
  float spider_position = get_position().first;
  float girl_position = girl->get_position().first;

  if(event == "Update"){
    states.set_state("FIGHT_STATE","NORMAL");
    if(spider_position > girl_position && spider_position - girl_position <= 300){
      set_position(std::make_pair(get_position().first - 1, get_position().second));
    }else if(girl_position > spider_position && girl_position - spider_position <= 588){
      set_position(std::make_pair(get_position().first + 1, get_position().second));
    }
  }else if(event == "MOVE_LEFT" && !GameObject::on_limit_of_level){
      set_position(std::make_pair(get_position().first + 10, get_position().second));
  }else if(event == "MOVE_RIGHT" && !GameObject::on_limit_of_level){
    set_position(std::make_pair(get_position().first - 10, get_position().second));
  }
}

void Spider::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  engine::Platform* p = dynamic_cast<engine::Platform *>(other);
  engine::LittleGirl* l = dynamic_cast<engine::LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){
    set_speed(std::make_pair(get_speed_x(), 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 280));
  }else if(p_my_hitbox->get_name() == "spider_attack" && l && get_state("FIGHT_STATE") == "ATTACKING"){
    l->set_hp(l->get_hp()-30);
  }
}
