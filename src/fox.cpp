#include "../include/fox.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/physics.hpp"

//TODO generalize methos create_animation in GOs

using namespace mindscape;

Fox::Fox(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :engine::GameObject(
    name,
    position,
    priority,
    {
      {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
      {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
      {engine::KeyboardEvent::UP,"JUMP"},
      {engine::KeyboardEvent::DOWN,"CROUCH"},
    }
  ){
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
    initialize_as_physicable();
};

void Fox::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* fox_hitbox = new engine::Hitbox(
    "fox_hitbox",
    this->get_position(),
    std::make_pair(0, 110),
    std::make_pair(120, 10),
    game.get_renderer()
  );
  add_component(fox_hitbox);
}

void Fox::initialize_state_map(){
  states.set_state("X_STATE","LOOKING_RIGHT");
  states.set_state("Y_STATE","ON_GROUND");
  states.set_state("ACTION_STATE","STOPPED");
}

void Fox::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    move(little_girl);
  }
}

void Fox::initialize_animations(){
  engine::Animation* running_right_animation = create_animation(
      "../assets/images/sprites/fox/fox_running_right.png",
      1,9,0.9, "RIGHT"
      );

  engine::Animation* running_left_animation = create_animation(
      "../assets/images/sprites/fox/fox_running_left.png",
      1, 9, 0.9, "LEFT"
      );

  engine::Animation* idle_right_animation = create_animation(
      "../assets/images/sprites/fox/fox_idle_right.png",
      1, 10, 1.5, "RIGHT"
      );

  engine::Animation* idle_left_animation = create_animation(
      "../assets/images/sprites/fox/fox_idle_left.png",
      1, 10, 1.5, "LEFT"
      );

  engine::Animation* jumping_right_animation = create_animation(
      "../assets/images/sprites/fox/fox_jumping_right.png",
      1, 4, 1.5, "RIGHT"
      );

  engine::Animation* jumping_left_animation = create_animation(
      "../assets/images/sprites/fox/fox_jumping_left.png",
      1, 4, 1.5, "LEFT"
      );

  add_animation("running_right_animation",running_right_animation);
  add_animation("running_left_animation",running_left_animation);
  add_animation("idle_right_animation",idle_right_animation);
  add_animation("idle_left_animation",idle_left_animation);
  add_animation("jumping_right_animation",jumping_right_animation);
  add_animation("jumping_left_animation",jumping_left_animation);
  idle_right_animation->activate();
  set_actual_animation(idle_right_animation);
}

engine::Animation* Fox::create_animation(
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
      std::make_pair(120, 120),
      std::make_pair(120, 120),
      std::make_pair(0, 0)
      );

  return animation;
}

void Fox::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void Fox::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");

  if(event_name == "JUMP"){
      //state == "JUMPING";
  }else if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level && actual_action_state == "STOPPED"){
    //set_actual_animation(animations["idle_left_animation"]);
    set_position_x(get_position_x() + 10);

  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level && actual_action_state == "STOPPED"){
    //set_actual_animation(animations["idle_right_animation"]);
    set_position_x(get_position_x() - 10);
  }
}

void Fox::move(engine::GameObject* girl){
  float fox_position = get_position_x();
  float girl_position = girl->get_position_x();
  int distance;

  //little_girl on left
  if(fox_position > girl_position){
    //little_girl far from spider
    states.set_state("X_STATE","LOOKING_LEFT");
    distance = fox_position - girl_position;

    if(distance <= 200){
      set_actual_animation(animations["idle_left_animation"]);
    }else if(distance > 200 && distance <= 400){
      set_actual_animation(animations["running_left_animation"]);
      set_position_x(get_position_x() - 3);
    }else if(distance > 400){
      set_actual_animation(animations["running_left_animation"]);
      set_position_x(get_position_x() - 5);
    }
    //little_girl on right
  }else{
    //little_girl far from spider
    states.set_state("X_STATE","LOOKING_RIGHT");
    distance = girl_position - fox_position;

    if(distance <= 100){
      set_actual_animation(animations["idle_right_animation"]);
    }
    else if(distance > 100 && distance <= 350){
      set_actual_animation(animations["running_right_animation"]);
      set_position_x(get_position_x() + 3);
    }else if(distance > 350){
      set_actual_animation(animations["running_right_animation"]);
      set_position_x(get_position_x() + 5);
    }
  }
}

void Fox::update_state(){
  /*
  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");

  if(get_speed_x() == 0.0 && get_speed_y() == 0.0 && actual_action_state == "NORMAL"){
    if(actual_x_state == "LOOKING_RIGHT"){
      set_actual_animation(animations["idle_right_animation"]);
    }else if(actual_x_state == "LOOKING_LEFT"){
      set_actual_animation(animations["idle_left_animation"]);
    }
  }  
  */
}

void Fox::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  mindscape::Platform* p = dynamic_cast<Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){
    set_speed(std::make_pair(get_speed_x(), 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 110));
  }
}
