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
  Enemy* body = new Enemy("body",std::make_pair(0,0),52,150);
  Enemy* goop = new Enemy("goop",std::make_pair(0,0),52,0);

  set_boss_part("body",body);
  set_boss_part("goop",goop);
}

void Clown::initialize_animations(){
    std::map<std::string,Enemy *> boss_parts = get_boss_parts();

    engine::Animation* clown_idle = create_animation(
      "../assets/images/sprites/enemies/clown/clown_idle.png",
      1, 15, 0.9, "LEFT"
    );

    engine::Animation* clown_goop = create_animation(
      "../assets/images/sprites/enemies/scorpion/clown_goop.png",
      1, 1, 0.9, "LEFT"
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
    std::make_pair(320, 320),
    std::make_pair(320, 320),
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
}

void Clown::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    //attack little girl
  }
}

void Clown::attack(){
  states.set_state("ACTION_STATE","ATTACKING");
}

void Clown::on_attack(){
  states.set_state("ACTION_STATE","ON_ATTACK");
}

void Clown::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);
}
