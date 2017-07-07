#include "../include/arm.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Arm::Arm(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :Enemy(
    name,
    position,
    priority,
    100
  ){
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
    translations = {
      {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
      {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
    };
    initialize_as_physicable();
};

void Arm::initialize_animations(){
  engine::Animation* arm_animation = create_animation(
      "../assets/images/sprites/enemies/arm/right_arm.png",
      1, 1, 3.0, "LEFT"
      );
  arm_animation->set_values(
      std::make_pair(135, 70),
      std::make_pair(135, 70),
      std::make_pair(0, 0)
      );

  engine::Animation* arm_animation = create_animation(
      "../assets/images/sprites/enemies/arm/left_arm.png",
      1, 1, 3.0, "LEFT"
      );
  arm_animation->set_values(
      std::make_pair(135, 70),
      std::make_pair(135, 70),
      std::make_pair(0, 0)
      );

  add_animation("arm_animation",arm_animation);
  arm_animation->activate();
  set_actual_animation(arm_animation);
}

engine::Animation* Arm::create_animation(
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

void Arm::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Arm::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* arm_hitbox = new engine::Hitbox(
    "arm_hitbox",
    this->get_position(),
    std::make_pair(10, 45),
    std::make_pair(60,8),
    game.get_renderer()
  );
  arm_hitbox->initialize();

  add_component(arm_hitbox);
}

void Arm::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
  states.set_state("Y_STATE","ON_GROUND");
}

void Arm::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    //set_speed_x(speed_x + 5);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    //set_speed_x(speed_x - 5);
  }
}

void Arm::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "arm_hitbox"){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 30);
    states.set_state("Y_STATE","ON_GROUND");
    engine::Game::get_instance().get_actual_scene()->deactivate_game_object(name);
    free();
  }
}
