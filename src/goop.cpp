#include "../include/goop.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Goop::Goop(
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
      {engine::KeyboardEvent::UP,"JUMP"},
      {engine::KeyboardEvent::DOWN,"CROUCH"},
    };
    initialize_as_physicable();
};

void Goop::initialize_animations(){
  engine::Animation* goop = create_animation(
      "../assets/images/sprites/enemies/clown/clown_goop.png",
      1, 1, 3.0, "LEFT"
      );
  goop->set_values(
      std::make_pair(135, 70),
      std::make_pair(135, 70),
      std::make_pair(0, 0)
      );
      
  add_animation("goop",goop);
  goop->activate();
  set_actual_animation(goop);
}

engine::Animation* Goop::create_animation(
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

void Goop::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Goop::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* goop_hitbox = new engine::Hitbox(
    "goop_hitbox",
    this->get_position(),
    std::make_pair(10, 60),
    std::make_pair(60,8),
    game.get_renderer()
  );
  goop_hitbox->initialize();

  add_component(goop_hitbox);
}

void Goop::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
  states.set_state("Y_STATE","ON_GROUND");
}

void Goop::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  static float speed_x = get_speed_x();

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_speed_x(speed_x + 5);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_speed_x(speed_x - 5);
  }
}

void Goop::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "goop_hitbox"){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 30);
    states.set_state("Y_STATE","ON_GROUND");
    //engine::Game::get_instance().get_actual_scene()->deactivate_game_object("goop");
    free();
  }
}


