#include "../include/uncle.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Uncle::Uncle(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :Enemy(
    name,
    position,
    priority,
    100
  ){
    initialize_boss_parts();
    //initialize_state_map();
    //initialize_hitboxes();
    //initialize_animations();
    //initialize_audio_effects();
};

void Uncle::initialize_boss_parts(){
  Enemy *head = new UncleHead("head",std::make_pair(900,-100),7);

  set_game_object_part("head",head);
}

void Uncle::initialize_audio_effects(){
}

void Uncle::initialize_animations(){
}

void Uncle::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* head_hitbox = new engine::Hitbox(
    "head_hitbox",
    this->get_position(),
    std::make_pair(160, 380),
    std::make_pair(180,20),
    game.get_renderer()
  );

  add_component(head_hitbox);
}

void Uncle::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void Uncle::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - 10);
  }
}

void Uncle::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    attack(little_girl);
  }
}

void Uncle::attack(engine::GameObject* little_girl){
  std::string actual_action_state = get_state("ACTION_STATE");

  if(actual_action_state == "DYING") return;
  if(actual_action_state == "ON_ATTACK" || actual_action_state == "ATTACKING"){
    if(get_actual_animation()->is_finished){
      states.set_state("ACTION_STATE","NORMAL");
      set_actual_animation(animations["idle_animation"]);
    }else{
      return;
    }
  }

}

void Uncle::basic_attack(){
}

void Uncle::on_attack(engine::GameObject *game_object){
  states.set_state("ACTION_STATE","ON_ATTACK");
  
  hit(game_object, 1);
  if(is_alive()){
    set_actual_animation(animations["on_attack_animation"]);
    //play_song("hit_me");
  }
}

void Uncle::die(engine::GameObject *game_object){
  std::string actual_x_state = get_state("X_STATE");
  states.set_state("ACTION_STATE", "DYING");
  set_actual_animation(animations["dying_animation"]);
  //play_song("hit_me");
}

void Uncle::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(little_girl &&
     little_girl->get_state("ACTION_STATE") == "ATTACKING" &&
     my_hitbox->get_name() == "head_hitbox" &&
     little_girl->get_actual_animation()->actual_column == 2
     && get_state("X_STATE") != little_girl->get_state("X_STATE")){
      if(get_state("ACTION_STATE") == "ON_ATTACK") return;
      else on_attack(other);
  }
}
