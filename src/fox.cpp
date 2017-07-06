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
  states.set_state("Y_STATE","FALLING");
  states.set_state("ACTION_STATE","NORMAL");
}

void Fox::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    girl_hp = little_girl->get_hp();
    if(girl_hp < 90 && get_star_count() == 3){
      must_give_hp_to_girl = true;
    }
    if(must_give_hp_to_girl){
      if(get_hp()+30 > 90){
        little_girl->set_hp(90);
      }else{
        little_girl->set_hp(little_girl->get_hp()+30);
      }
      must_give_hp_to_girl = false;
      animation_hud_fading = true;
    }
    if(little_girl->get_position_y() + 70 == get_position_y()){
      move(little_girl);
    }else if(little_girl && little_girl->get_position_y() + 70 != get_position_y() &&
      little_girl->get_state("Y_STATE") == "ON_GROUND" && get_state("Y_STATE") == "ON_GROUND"){
      jump(little_girl);
    }else if(little_girl->get_state("Y_STATE") != "ON_GROUND" && get_state("Y_STATE") == "ON_GROUND"){
      set_speed_x(0.0);
    }
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
  }else if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level && actual_action_state == "NORMAL"){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level && actual_action_state == "NORMAL"){
    set_position_x(get_position_x() - 10);
  }
}

void Fox::move(engine::GameObject* girl){
  float fox_position = get_position_x();
  float girl_position = girl->get_position_x();
  int distance_from_girl;

  if(fox_position > girl_position){
    states.set_state("X_STATE","LOOKING_LEFT");
    distance_from_girl = fox_position - girl_position;

    if(distance_from_girl <= 200){
      set_actual_animation(animations["idle_left_animation"]);
      set_speed_x(0);
    }else if(distance_from_girl > 200 && distance_from_girl <= 400){
      set_actual_animation(animations["running_left_animation"]);
      set_speed_x(-6);
    }else if(distance_from_girl > 400){
      set_actual_animation(animations["running_left_animation"]);
      set_speed_x(-14);
    }
  }else{
    states.set_state("X_STATE","LOOKING_RIGHT");
    distance_from_girl = girl_position - fox_position;

    if(distance_from_girl <= 100){
      set_actual_animation(animations["idle_right_animation"]);
      set_speed_x(0);
    }
    else if(distance_from_girl > 100 && distance_from_girl <= 350){
      set_actual_animation(animations["running_right_animation"]);
      set_speed_x(6);
    }else if(distance_from_girl > 350){
      set_actual_animation(animations["running_right_animation"]);
      set_speed_x(14);
    }
  }
}

void Fox::jump(GameObject *little_girl){
  if(get_state("Y_STATE") != "JUMPING" && get_state("Y_STATE") != "FALLING"){
    states.set_state("Y_STATE", "JUMPING");

    if(little_girl->get_state("X_STATE") == "LOOKING_LEFT"){
      set_actual_animation(animations["jumping_left_animation"]);
    }else if(little_girl->get_state("X_STATE") == "LOOKING_RIGHT"){
      set_actual_animation(animations["jumping_right_animation"]);
    }

    follow_jump(little_girl);
  }else{
    if(get_position_x() > little_girl->get_position_x()){ //girl on left
      states.set_state("X_STATE","LOOKING_LEFT");
    }else{ //girl on right
      states.set_state("X_STATE","LOOKING_RIGHT");
    }
  }
}

void Fox::follow_jump(GameObject *little_girl){
  engine::Physics *physics = engine::Physics::get_instance();
  float gravity = physics->get_gravity();
  float number_of_sprites = 11.755; //time
  float final_y = little_girl->get_position_y();
  float final_x = little_girl->get_position_x();
  float throw_speed_y = calculate_vy_jump(final_y, gravity, number_of_sprites);
  float throw_speed_x = calculate_vx_jump(final_x, gravity, number_of_sprites);
  set_speed_y(throw_speed_y);
  set_speed_x(throw_speed_x);
}

float Fox::calculate_vy_jump(float final_y, float gravity, float jump_time){
  float initial_y = (float) get_position_y();
  float throw_speed_y;
  float delta_y = final_y - initial_y;
  throw_speed_y = ((gravity*jump_time/2.0) + (delta_y/jump_time));
  return throw_speed_y;
}

float Fox::calculate_vx_jump(float final_x, float gravity, float jump_time){
  float throw_speed_x;
  float initial_x = (float) get_position_x();
  float delta_x = final_x - initial_x;
  throw_speed_x = delta_x/(jump_time*2);
  return throw_speed_x;
}

void Fox::update_state(){
  std::string actual_x_state = get_state("X_STATE");

  if(get_speed_x() == 0.0 && get_speed_y() == 0.0){
    if(actual_x_state == "LOOKING_RIGHT"){
      set_actual_animation(animations["idle_right_animation"]);
    }else if(actual_x_state == "LOOKING_LEFT"){
      set_actual_animation(animations["idle_left_animation"]);
    }
  };
  if(get_speed_y() == 0.0){
    states.set_state("Y_STATE","ON_GROUND");
  }
}

void Fox::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  Star* star = dynamic_cast<Star *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 110);
  }else if(star){
    if(get_star_count() != 3){
      star->play_song("got_me");
      star->set_actual_animation(star->animations["star_fading"]);
      star->deactivate_components();
      set_star_count(get_star_count() + 1);
    }
  }
}

bool Fox::get_animation_hud_fading(){
  return animation_hud_fading;
}

void Fox::set_animation_hud_fading(bool bol){
  animation_hud_fading = bol;
}

int Fox::get_star_count(){
  return star_count;
}

void Fox::set_star_count(int quantity){
  star_count = quantity;
}
