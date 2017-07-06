#include "../include/clown.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Clown::Clown(
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
    initialize_as_physicable();
    initialize_audio_effects();
};


void Clown::initialize_audio_effects(){
}

void Clown::initialize_animations(){
  engine::Animation* clown_idle = create_animation(
      "../assets/images/sprites/enemies/clown/clown_idle.png",
      1, 15, 3.0, "LEFT"
      );
  clown_idle->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );

  add_animation("clown_idle",clown_idle);
  clown_idle->activate();
  set_actual_animation(clown_idle);
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
    std::make_pair(320, 320),
    std::make_pair(320, 320),
    std::make_pair(0, 0)
  );

  return animation;
}

void Clown::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Clown::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* foot_hitbox = new engine::Hitbox(
    "foot_hitbox",
    this->get_position(),
    std::make_pair(40, 312),
    std::make_pair(180,8),
    game.get_renderer()
  );

  engine::Hitbox* attack_hitbox = new engine::Hitbox(
    "attack_hitbox",
    this->get_position(),
    std::make_pair(5, 200),
    std::make_pair(283,10),
    game.get_renderer()
  );

  add_component(foot_hitbox);
  add_component(attack_hitbox);
}

void Clown::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void Clown::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - 10);
  }
}

void Clown::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    attack(little_girl);
  }
}

void Clown::attack(engine::GameObject* little_girl){
  int clown_position = get_position_x();
  int little_girl_position = little_girl->get_position_x();
  int distance_from_girl = clown_position - little_girl_position; 

  if(distance_from_girl < 650){
    attack_animation_trigger += 1;
    if(attack_animation_trigger == 40){
      states.set_state("ACTION_STATE","ATTACKING");
      attack_normally_1();
      //std::cout << "Random Ataque" << std::endl;
    }else if(attack_animation_trigger == 80){
      states.set_state("ACTION_STATE","ATTACKING");
      //std::cout << "Ataque 444" << std::endl;
      attack_animation_trigger = 0;
    }
    states.set_state("ACTION_STATE","NORMAL");
  }
}

void Clown::attack_normally_1(){
  if(goops_counter == 0){
    engine::GameObject* goop = new Goop("goop",std::make_pair(180,180),60);
    engine::Game::get_instance().get_actual_scene()->add_object(goop);
    engine::Game::get_instance().get_actual_scene()->activate_game_object(goop);
    goop->load();
    goops_counter += 1;
    goop->set_speed_x(-7.0);
  }
}

void Clown::on_attack(){
}

void Clown::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "foot_hitbox"){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 312);
  }
}
