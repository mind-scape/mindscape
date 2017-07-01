#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include "../engine/include/game.hpp"
#include <typeinfo>
#include <algorithm>

using namespace mindscape;

//TODO fix below velocity configuration

LittleGirl::LittleGirl(
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
      {engine::KeyboardEvent::F,"ATTACK"},
    }
  ){
    initialize_state_map();
    initialize_hitboxes();
    initialize_animations();
    initialize_as_physicable();
};

void LittleGirl::initialize_state_map(){
  states.set_state("X_STATE","LOOKING_RIGHT");
  states.set_state("Y_STATE","ON_GROUND");
  states.set_state("ACTION_STATE","NORMAL");
}

void LittleGirl::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* hitbox= new engine::Hitbox(
      "hitbox",
      get_position(),
      std::make_pair(60, 45),
      std::make_pair(50,140),
      game.get_renderer()
      );

  add_component(hitbox);
}

void LittleGirl::initialize_animations(){
  //Creating running right animation
  engine::Animation* running_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_running_right.png",
      1,9,0.9, "RIGHT"
      );

  //Creating running right animation
  engine::Animation* running_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_running_left.png",
      1, 9, 0.9, "LEFT"
      );

  //Creating idle right animation
  engine::Animation* idle_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_idle_right.png",
      1, 10, 1.5, "RIGHT"
      );

  //Creating idle left animation
  engine::Animation* idle_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_idle_left.png",
      1, 10, 1.5, "LEFT"
      );

  //Creating jumping right animation
  engine::Animation* jumping_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_jumping_right.png",
      1, 5, 1.5, "RIGHT"
      );

  //Creating jumping left animation
  engine::Animation* jumping_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_jumping_left.png",
      1, 5, 1.5, "LEFT"
      );

  //Creating attacking right animation
  engine::Animation* attacking_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_attacking_right.png",
      1, 5, 0.6, "RIGHT"
      );

  //Creating attacking left animation
  engine::Animation* attacking_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_attacking_left.png",
      1, 5, 0.6, "LEFT"
      );

  add_animation("running_right_animation",running_right_animation);
  add_animation("running_left_animation",running_left_animation);
  add_animation("idle_right_animation",idle_right_animation);
  add_animation("idle_left_animation",idle_left_animation);
  add_animation("jumping_right_animation",jumping_right_animation);
  add_animation("jumping_left_animation",jumping_left_animation);
  add_animation("attacking_right_animation",attacking_right_animation);
  add_animation("attacking_left_animation",attacking_left_animation);
  idle_right_animation->activate();
  set_actual_animation(idle_right_animation);
}

engine::Animation* LittleGirl::create_animation(
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
      std::make_pair(192, 192),
      std::make_pair(192, 192),
      std::make_pair(0, 0)
      );

  return animation;
}

void LittleGirl::initialize_as_physicable(){
  engine::Physics *physics = engine::Physics::get_instance();
  physics->add_physicable(this);
  collidable = true;
}

void LittleGirl::on_collision(
    engine::GameObject* other,
    engine::Hitbox* p_my_hitbox,
    engine::Hitbox* p_other_hitbox){

  Platform* p = dynamic_cast<Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){ //if she is falling on a platform
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 180);
  }
}

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");


  if(event_name == "JUMP" && actual_y_state != "JUMPING"){
    jump(actual_x_state);
  }else if(event_name == "MOVE_LEFT"){
    move_left(actual_x_state,actual_y_state);
  }else if(event_name == "MOVE_RIGHT"){
    move_right(actual_x_state,actual_y_state);
  }else if(event_name == "ATTACK" && actual_action_state != "ATTACKING"){
    attack(actual_x_state);
  }
}

void LittleGirl::jump(std::string actual_x_state){
  set_speed_y(-21);
  states.set_state("Y_STATE","JUMPING");

  if(actual_x_state == "LOOKING_RIGHT")
    set_actual_animation(animations["jumping_right_animation"]);
  else if(actual_x_state == "LOOKING_LEFT")
    set_actual_animation(animations["jumping_left_animation"]);

  engine::Animation* actual_animation = get_actual_animation();

  jumping_animation_count += 1;
  if(jumping_animation_count < 26){
    if(jumping_animation_count % 5 == 0){
      actual_animation->coordinatesOnTexture.first += 192;
      if(actual_animation->coordinatesOnTexture.first == 960){
        actual_animation->coordinatesOnTexture.first = 0;
      }
    }
  }else{
    jumping_animation_count = 26;
  }
}

void LittleGirl::move_right(std::string actual_x_state,std::string actual_y_state){
  if(actual_y_state == "ON_GROUND"){

    engine::Animation* actual_animation = get_actual_animation();

    actual_animation->coordinatesOnTexture.first += 192;

    if(actual_animation->coordinatesOnTexture.first >= 1728)
      actual_animation->coordinatesOnTexture.first = 0;
    states.set_state("X_STATE","LOOKING_RIGHT");
    set_actual_animation(animations["running_right_animation"]);

    set_speed_x(0.000000000001);
  }else if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_LEFT"){
    states.set_state("X_STATE","LOOKING_RIGHT");
    set_actual_animation(animations["jumping_right_animation"]);
  }
}

void LittleGirl::move_left(std::string actual_x_state,std::string actual_y_state){
  if(actual_y_state == "ON_GROUND"){

    engine::Animation* actual_animation = get_actual_animation();

    actual_animation->coordinatesOnTexture.first -= 192;

    if(actual_animation->coordinatesOnTexture.first <= 0)
      actual_animation->coordinatesOnTexture.first = 1536;
    states.set_state("X_STATE","LOOKING_LEFT");
    set_actual_animation(animations["running_left_animation"]);

    set_speed_x(0.000000000001);
  }else if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT"){
    states.set_state("X_STATE","LOOKING_LEFT");
    set_actual_animation(animations["jumping_left_animation"]);
  }
}

void LittleGirl::attack(std::string actual_x_state){
  states.set_state("ACTION_STATE","ATTACKING");
  if(actual_x_state == "LOOKING_RIGHT"){
    set_actual_animation(animations["attacking_right_animation"]);
  }else if(actual_x_state == "LOOKING_LEFT"){
    set_actual_animation(animations["attacking_left_animation"]);
  }
}

void LittleGirl::update_state(){
  //Should be implemented
  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");

  if(actual_action_state == "ATTACKING"){
    if(get_actual_animation()->is_finished){
      states.set_state("ACTION_STATE","NORMAL");
    }
  }
  if(get_speed_x() == 0.0 && get_speed_y() == 0.0 && actual_action_state == "NORMAL"){
    if(actual_x_state == "LOOKING_RIGHT"){
      set_actual_animation(animations["idle_right_animation"]);
    }else if(actual_x_state == "LOOKING_LEFT"){
      set_actual_animation(animations["idle_left_animation"]);
    }
    jumping_animation_count = 0;
  }
  if(get_speed_y() == 0.0){
    states.set_state("Y_STATE","ON_GROUND");
  }

  set_speed_x(0.0);
}
