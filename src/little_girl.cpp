#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include "../include/scorpion.hpp"
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
    initialize_audio_effects();
    initialize_as_physicable();
};

void LittleGirl::initialize_state_map(){
  states.set_state("X_STATE","LOOKING_RIGHT");
  states.set_state("Y_STATE","FALLING");
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

void LittleGirl::initialize_audio_effects(){

  engine::Audio * little_girl_steps = new engine::Audio("../assets/audios/effects_songs/menina_passos_rapido.wav", engine::Audio::CHUNK);
  add_component(little_girl_steps);

}

void LittleGirl::initialize_animations(){
  engine::Animation* running_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_running_right.png",
      1,9,0.9, "RIGHT"
      );

  engine::Animation* running_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_running_left.png",
      1, 9, 0.9, "LEFT"
      );

  engine::Animation* idle_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_idle_right.png",
      1, 10, 1.5, "RIGHT"
      );

  engine::Animation* idle_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_idle_left.png",
      1, 10, 1.5, "LEFT"
      );

  engine::Animation* jumping_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_jumping_right.png",
      1, 5, 1.5, "RIGHT"
      );

  engine::Animation* jumping_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_jumping_left.png",
      1, 5, 1.5, "LEFT"
      );

  engine::Animation* attacking_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_attacking_right.png",
      1, 5, 0.5, "RIGHT"
      );
  attacking_right_animation->in_loop = false;

  engine::Animation* attacking_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_attacking_left.png",
      1, 5, 0.5, "LEFT"
      );
  attacking_left_animation->in_loop = false;

  engine::Animation* on_attack_right_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_on_attack_right.png",
      1, 3, 0.8, "RIGHT"
      );

  engine::Animation* on_attack_left_animation = create_animation(
      "../assets/images/sprites/little_girl/little_girl_on_attack_left.png",
      1, 3, 0.8, "LEFT"
      );

  add_animation("running_right_animation",running_right_animation);
  add_animation("running_left_animation",running_left_animation);
  add_animation("idle_right_animation",idle_right_animation);
  add_animation("idle_left_animation",idle_left_animation);
  add_animation("jumping_right_animation",jumping_right_animation);
  add_animation("jumping_left_animation",jumping_left_animation);
  add_animation("omelete1",attacking_right_animation);
  add_animation("omelete2",attacking_left_animation);
  add_animation("on_attack_right_animation",on_attack_right_animation);
  add_animation("on_attack_left_animation",on_attack_left_animation);
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

  Platform* platform = dynamic_cast<Platform *>(other);
  Scorpion* scorpion = dynamic_cast<Scorpion *>(other);
  Spider* spider = dynamic_cast<Spider *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform){ //if she is falling on a platform
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 180);
  }
  if(scorpion &&
     scorpion->get_state("ACTION_STATE") == "ATTACKING" &&
     other_hitbox->get_name() == "scorpion_attack" &&
     scorpion->get_actual_animation()->actual_column == 1){
    on_attack();
    set_hp(get_hp()-1);
  }
  if(spider &&
     spider->get_state("ACTION_STATE") == "ATTACKING" &&
     other_hitbox->get_name() == "spider_attack" &&
     spider->get_actual_animation()->actual_column == 3){
    on_attack();
    set_hp(get_hp()-1);
  }
}

void LittleGirl::on_event(GameEvent game_event){

  engine::Audio* little_girl_steps = dynamic_cast<engine::Audio *>(audios[0]);

  std::string event_name = game_event.game_event_name;

  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");

  if(event_name == "JUMP" && actual_y_state != "JUMPING"){
    jump(actual_x_state);
  }else if(event_name == "MOVE_LEFT"){
    move_left(actual_x_state,actual_y_state);
   little_girl_steps->play_effect();
  }else if(event_name == "MOVE_RIGHT"){
    move_right(actual_x_state,actual_y_state);
    little_girl_steps->play_effect();
  }else if(event_name == "ATTACK" && actual_action_state != "ATTACKING"){
    attack(actual_x_state);
  }else if(actual_action_state == "NORMAL" && actual_y_state == "ON_GROUND");{
    // std::cout << "\n XABLAAAAAAAU \n" << std::endl;
    // little_girl_steps->pause_music();
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

    set_speed_x(0.1);
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

    set_speed_x(-0.1);
  }else if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT"){
    states.set_state("X_STATE","LOOKING_LEFT");
    set_actual_animation(animations["jumping_left_animation"]);
  }
}

void LittleGirl::attack(std::string actual_x_state){
  states.set_state("ACTION_STATE","ATTACKING");
  if(actual_x_state == "LOOKING_RIGHT"){
    set_actual_animation(animations["omelete1"]);
  }else if(actual_x_state == "LOOKING_LEFT"){
    set_actual_animation(animations["omelete2"]);
  }
}

void LittleGirl::on_attack(){
  std::string actual_x_state = states.get_state("X_STATE");
  states.set_state("ACTION_STATE","ON_ATTACK");
  if(actual_x_state == "LOOKING_LEFT"){
    set_actual_animation(animations["on_attack_left_animation"]);
  }else if(actual_x_state == "LOOKING_RIGHT"){
    set_actual_animation(animations["on_attack_right_animation"]);
  }
}

void LittleGirl::update_state(){
  //Should be implemented
  if(get_actual_animation() == animations["omelete1"] || get_actual_animation() == animations["omelete2"]){
  }

  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
  std::string actual_action_state = states.get_state("ACTION_STATE");

  if(actual_action_state == "ATTACKING" || actual_action_state == "ON_ATTACK"){
    if(get_actual_animation()->is_finished){
      states.set_state("ACTION_STATE","NORMAL");
    }else{
       return;
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

  set_position_x(get_position_x() + get_speed_x());
  set_speed_x(0.0);
}
