#include "../include/spider.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

void Spider::on_event(GameEvent game_event){
  attack();
}

void Spider::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    move(little_girl);
  }
}

void Spider::attack(){
  states.set_state("ACTION_STATE","ATTACKING");
  // implement animation logic here
}

void Spider::move(engine::GameObject* girl){
  float spider_position = get_position_x();
  float girl_position = girl->get_position_x();

  //little_girl on right
  if(spider_position > girl_position){
    //little_girl far from spider
    if(spider_position - girl_position <= 300){
      states.set_state("ACTION_STATE","NORMAL");
      set_actual_animation(animations["walking_right"]);
      set_position_x(get_position_x() - 1);
    //little_girl close of spider
    }else if(!GameObject::on_limit_of_level){
      set_position_x(get_position_x() - 10);
    }
  //little_girl on left
  }else{
    //little_girl far from spider
    if(girl_position - spider_position <= 588){
      set_actual_animation(animations["walking_left"]);
      set_position_x(get_position_x() + 1);
    //little_girl close of spider
    }else if(!GameObject::on_limit_of_level){
      set_position_x(get_position_x() + 10);
    }
  }
}

void Spider::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* p = dynamic_cast<Platform *>(other);
  LittleGirl* l = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p && my_hitbox->get_name() == "spider_hitbox"){
    set_speed(std::make_pair(get_speed_x(), 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 280));
  }else if(p_my_hitbox->get_name() == "spider_attack" && l && get_state("FIGHT_STATE") == "ATTACKING"){
    l->set_hp(l->get_hp()-30);
  }
}
