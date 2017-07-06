#include "../include/clown.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Clown::Clown(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :Boss(
    name,
    position,
    priority,
    100
  ){
    initialize_boss_parts();
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
};

void Clown::initialize_boss_parts(){
  Enemy* body = new Enemy("body",std::make_pair(1800,180),60,150);
  body->translations = {
    {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
    {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
  };
  Enemy* goop = new Enemy("goop",std::make_pair(300,180),60,0);

  set_boss_part("body",body);
  set_boss_part("goop",goop);
}

void Clown::initialize_animations(){
    std::map<std::string,Enemy *> boss_parts = get_boss_parts();

    engine::Animation* clown_idle = create_animation(
      "../assets/images/sprites/enemies/clown/clown_idle.png",
      1, 15, 3.0, "LEFT"
    );
    clown_idle->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
    );

    engine::Animation* clown_goop = create_animation(
      "../assets/images/sprites/enemies/clown/clown_goop.png",
      1, 1, 3.0, "LEFT"
    );
    clown_goop->set_values(
      std::make_pair(135, 70),
      std::make_pair(135, 70),
      std::make_pair(0, 0)
    );

    boss_parts["body"]->add_animation("clown_idle",clown_idle);
    boss_parts["goop"]->add_animation("clown_goop",clown_goop);

    clown_idle->activate();
    clown_goop->activate();
    
    boss_parts["body"]->set_actual_animation(clown_idle);
    boss_parts["goop"]->set_actual_animation(clown_goop);
}

engine::Animation* Clown::create_animation(
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
    std::make_pair(100, 100),
    std::make_pair(100, 100),
    std::make_pair(0, 0)
  );

  return animation;
}

void Clown::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* clown_hitbox = new engine::Hitbox(
    "clown_hitbox",
    this->get_position(),
    std::make_pair(40, 312),
    std::make_pair(180,8),
    game.get_renderer()
  );

  add_component(clown_hitbox);
}

void Clown::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void Clown::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name; 
  std::string actual_action_state = states.get_state("ACTION_STATE");
  Enemy* body = get_boss_parts()["body"];

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level && actual_action_state == "NORMAL"){
    body->set_position_x(body->get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level && actual_action_state == "NORMAL"){
    body->set_position_x(body->get_position_x() - 10);
  }
}

void Clown::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    attack(little_girl);
  }
}

void Clown::attack(engine::GameObject* little_girl){
  int clown_position = get_boss_parts()["body"]->get_position_x();
  int little_girl_position = little_girl->get_position_x();
  int distance_from_girl = clown_position - little_girl_position; 

  if(distance_from_girl < 650){
    attack_animation_trigger += 1;
    if(attack_animation_trigger == 10){
      states.set_state("ACTION_STATE","ATTACKING");
      //std::cout << "Random Ataque" << std::endl;
    }else if(attack_animation_trigger == 20){
      states.set_state("ACTION_STATE","ATTACKING");
      //std::cout << "Ataque 444" << std::endl;
      attack_animation_trigger = 0;
    }
    states.set_state("ACTION_STATE","NORMAL");
  }
}

void Clown::on_attack(){
}

void Clown::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);
}

void Clown::activate(){
  std::map<std::string,Enemy*> boss_parts = get_boss_parts();
  for(auto boss_part : boss_parts){
    boss_part.second->activate();
  }
}

void Clown::draw(){
  std::map<std::string,Enemy*> boss_parts = get_boss_parts();
  for(auto boss_part : boss_parts){
    boss_part.second->draw();
  }
}

void Clown::load(){
  std::map<std::string,Enemy*> boss_parts = get_boss_parts();
  for(auto boss_part : boss_parts){
    boss_part.second->load(); 
  }
}
/*
float Clown::calculate_goop_vy(float final_y, float gravity, float jump_time){
  float initial_y = (float) get_position_y();
  float throw_speed_y;
  float delta_y = final_y - initial_y;
  throw_speed_y = ((gravity*jump_time/2.0) + (delta_y/jump_time));
  return throw_speed_y;
}

float Clown::calculate_goop_vx(float final_x, float gravity, float jump_time){
  float throw_speed_x;
  float initial_x = (float) get_position_x();
  float delta_x = final_x - initial_x;
  throw_speed_x = delta_x/(jump_time*2);
  return throw_speed_x;
}
*/
