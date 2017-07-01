#include "../include/spider.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

Spider::Spider(
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

void Spider::initialize_animations(){
    engine::Animation* spider_left = create_animation(
      "../assets/images/sprites/enemies/spider/spider_walking_left.png",
      1, 4, 0.9, "LEFT"
    );

    engine::Animation* spider_right = create_animation(
      "../assets/images/sprites/enemies/spider/spider_walking_right.png",
      1, 4, 0.9, "RIGHT"
    );

    add_animation("walking_right", spider_left);
    add_animation("walking_left", spider_right);
    spider_left->activate();
    set_actual_animation(spider_left);
}

engine::Animation* Spider::create_animation(
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
    std::make_pair(288, 288),
    std::make_pair(288, 288),
    std::make_pair(0, 0)
  );

  return animation;
}

void Spider::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Spider::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* spider_hitbox = new engine::Hitbox(
    "spider_hitbox",
    this->get_position(),
    std::make_pair(60, 280),
    std::make_pair(180, 8),
    game.get_renderer()
  );

  engine::Hitbox* spider_attack = new engine::Hitbox(
    "spider_attack",
    this->get_position(),
    std::make_pair(5, 200),
    std::make_pair(283,10),
    game.get_renderer()
  );

  add_component(spider_attack);
  add_component(spider_hitbox);
}

void Spider::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void Spider::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - 10);
  }

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

// TODO: the movements are stopped when too close. In that time, spider must attack.
void Spider::move(engine::GameObject* girl){
  float spider_position = get_position_x();
  float girl_position = girl->get_position_x();

  //little_girl on left
  if(spider_position > girl_position){
    //little_girl far from spider
    if(spider_position - girl_position <= 300){
      states.set_state("ACTION_STATE","NORMAL");
      if(spider_position - girl_position >= 50){
        set_actual_animation(animations["walking_right"]);
        set_position_x(get_position_x() - 1);
        //little_girl close of spider
      }
    }
  //little_girl on right
}else{
    //little_girl far from spider
    if(girl_position - spider_position <= 588){
      if(girl_position - spider_position >= 150){
        set_actual_animation(animations["walking_left"]);
        set_position_x(get_position_x() + 1);
        //little_girl close of spider
      }    //little_girl close of spider
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
