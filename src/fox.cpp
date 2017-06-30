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
    initialize_animations();                                                    
    //initialize_as_physicable(); 
};

void Fox::initialize_state_map(){
  states.set_state("X_STATE","LOOKING_RIGHT");
  states.set_state("Y_STATE","ON_GROUND");
  states.set_state("ACTION_STATE","NORMAL");
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

 // engine::Image* moving_right_image = dynamic_cast<engine::Image*>(images[0]);
 // engine::Image* moving_left_image = dynamic_cast<engine::Image*>(images[1]);
  
  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");


  if(abs(get_position().first - 512) <= 50){
    velocity = 10;
  }else if(abs(get_position().first - 512) > 50 && abs(get_position().first -512) < 200){
    velocity = 5;
  }else if(abs(get_position().first - 512) >= 200){
    velocity = -20;
  }

  if(event_name == "JUMP"){
      //state == "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){

    set_actual_animation(animations["running_left_animation"]);

    running_left_animation_count += 1;
    if(running_left_animation_count == 7){
      actual_animation->coordinatesOnTexture.first -= 120;
      set_speed(std::make_pair(velocity, get_speed().second));
      running_left_animation_count = 0;
    }
    if(actual_animation->coordinatesOnTexture.first <= 0) actual_animation->coordinatesOnTexture.first = 960;

  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){

    set_actual_animation(animations["running_right_animation"]);

    running_right_animation_count +=1;
    if(running_right_animation_count == 7){
      set_speed(std::make_pair(-velocity, get_speed().second));
      actual_animation->coordinatesOnTexture.first += 120;
      running_right_animation_count = 0;
    }
    if(actual_animation->coordinatesOnTexture.first >= 1080) actual_animation->coordinatesOnTexture.first = 0;
  }
}

void Fox::update_state(){
  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");
}
