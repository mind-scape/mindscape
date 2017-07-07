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
    //initialize_arms();
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
    initialize_as_physicable();
    initialize_audio_effects();
};
/*
void Uncle::initialize_arms(){
  right_arm = new Arm("right_arm",std::make_pair(get_position_x() + 40,get_position_y() + 150),60););
  engine::Game::get_instance().get_actual_scene()->add_object(right_arm);
  engine::Game::get_instance().get_actual_scene()->activate_game_object(right_arm);
  right_arm->load();
  
  left_arm = new Arm("left_arm",std::make_pair(get_position_x() + 40,get_position_y() + 150),60););
  engine::Game::get_instance().get_actual_scene()->add_object(left_arm);
  engine::Game::get_instance().get_actual_scene()->activate_game_object(left_arm);
  left_arm->load();
}
*/
void Uncle::initialize_audio_effects(){
}

void Uncle::initialize_animations(){
  engine::Animation* idle_animation = create_animation(
      "../assets/images/sprites/enemies/uncle/uncle_idle.png",
      1, 1, 3.0, "LEFT"
      );
  idle_animation->set_values(
      std::make_pair(665, 484),
      std::make_pair(665, 484),
      std::make_pair(0, 0)
      );
  
  engine::Animation* attacking_animation = create_animation(
      "../assets/images/sprites/enemies/uncle/uncle_attacking.png",
      1, 1, 3.0, "LEFT"
      );
  attacking_animation->set_values(
      std::make_pair(719, 523),
      std::make_pair(719, 523),
      std::make_pair(0, 0)
      );
  attacking_animation->in_loop = false;

  engine::Animation* dying_animation = create_animation(
      "../assets/images/sprites/enemies/uncle/uncle_dying.png",
      1, 1, 3.0, "LEFT"
      );
  dying_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );
  dying_animation->in_loop = false;
  dying_animation->is_a_final_animation = false;

  add_animation("idle_animation",idle_animation);
  add_animation("attacking_animation",attacking_animation);
  add_animation("dying_animation",dying_animation);
  idle_animation->activate();
  set_actual_animation(idle_animation);
}

engine::Animation* Uncle::create_animation(
  std::string path,
  int sprite_lines,
  int sprite_columns,
  double duration,
  std::string direction){

  engine::Game& game = engine::Game::get_instance();
  engine::Animation* animation = new engine::Animation(
    game.get_renderer(),
    path,                 // image path
    false,                // is_active
    std::make_pair(0, 0), // displacement
    1,                    // priority
    sprite_lines,         // sprite_lines
    sprite_columns,       // sprite_columns
    duration,             // duration
    true,                 // in_loop
    direction             // direction
  );

  animation->set_values(
    std::make_pair(320, 320),
    std::make_pair(320, 320),
    std::make_pair(0, 0)
  );

  return animation;
}

void Uncle::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
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
