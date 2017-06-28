#include "../include/scorpion.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Scorpion::Scorpion(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :Enemy(
    name,
    position,
    priority
  ){
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
    initialize_as_physicable();
};

void Scorpion::initialize_animations(){
    engine::Animation* scorpion_left = create_animation(
      "../assets/images/sprites/enemies/scorpion/scorpion_walking_left.png",
      1, 5, 0.9, "LEFT"
    );

    engine::Animation* scorpion_right = create_animation(
      "../assets/images/sprites/enemies/scorpion/scorpion_walking_right.png",
      1, 5, 0.9, "RIGHT"
    );

    add_animation("walking_right", scorpion_left);
    add_animation("walking_left", scorpion_right);
    scorpion_left->activate();
    set_actual_animation(scorpion_left);

}

engine::Animation* Scorpion::create_animation(
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
    std::make_pair(0, 0), // displcement
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

void Scorpion::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Scorpion::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* scorpion_hitbox = new engine::Hitbox(
    "scorpion_hitbox",
    this->get_position(),
    std::make_pair(40, 312),
    std::make_pair(180,8),
    game.get_renderer()
  );

  engine::Hitbox* scorpion_attack = new engine::Hitbox(
    "scorpion_attack",
    this->get_position(),
    std::make_pair(5, 200),
    std::make_pair(283,10),
    game.get_renderer()
  );

  add_component(scorpion_attack);
  add_component(scorpion_hitbox);
}

void Scorpion::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void Scorpion::on_event(GameEvent game_event){
  attack();
}

void Scorpion::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    move(little_girl);
  }
}

void Scorpion::attack(){
  states.set_state("ACTION_STATE","ATTACKING");
  // implement animation logic here
}

void Scorpion::move(engine::GameObject* girl){
  float scorpion_position = get_position_x();
  float girl_position = girl->get_position_x();

  //little_girl on right
  if(scorpion_position > girl_position){
    //little_girl far from scorpion
    if(scorpion_position - girl_position <= 300){
      states.set_state("ACTION_STATE","NORMAL");
      set_actual_animation(animations["walking_right"]);
      set_position_x(get_position_x() - 1);
    //little_girl close of scorpion
    }else if(!GameObject::on_limit_of_level){
      set_position_x(get_position_x() - 10);
    }
  //little_girl on left
  }else{
    //little_girl far from scorpion
    if(girl_position - scorpion_position <= 588){
      set_actual_animation(animations["walking_left"]);
      set_position_x(get_position_x() + 1);
    //little_girl close of scorpion
    }else if(!GameObject::on_limit_of_level){
      set_position_x(get_position_x() + 10);
    }
  }
}

void Scorpion::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "scorpion_hitbox"){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 312);
  }else if(p_my_hitbox->get_name() == "scorpion_attack" && little_girl && get_state("FIGHT_STATE") == "ATTACKING"){
    little_girl->set_hp(little_girl->get_hp()-30);
  }
}
