#include "../include/uncle_head.hpp"
#include "../include/little_girl.hpp"
#include <stdlib.h>

using namespace mindscape;

UncleHead::UncleHead(
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
//    initialize_hitboxes();
    initialize_animations();
    initialize_audio_effects();
};


void UncleHead::initialize_audio_effects(){
  /*
  engine::Audio * scorpion_attacking = new engine::Audio(
  "attack",
  "../assets/audios/effects_songs/ataque_insetos.wav", engine::Audio::CHUNK);
  scorpion_attacking->set_duration(0.7);

  engine::Audio * scorpion_on_attack = new engine::Audio(
  "hit_me",
  "../assets/audios/effects_songs/inseto_apanhando.wav", engine::Audio::CHUNK);
  scorpion_on_attack->set_duration(0.8);

  add_component(scorpion_attacking);
  add_component(scorpion_on_attack);
  */
}

void UncleHead::initialize_animations(){
  engine::Animation* idle_animation = create_animation(
      "../assets/images/sprites/enemies/uncle/uncle_idle.png",
      1, 4, 3.0, "LEFT"
      );
  idle_animation->set_values(
      std::make_pair(665, 484),
      std::make_pair(665, 484),
      std::make_pair(0, 0)
      );
  
  engine::Animation* attacking_animation = create_animation(
      "../assets/images/sprites/enemies/uncle/uncle_attacking.png",
      1, 1, 3.0, "LEFT"
      );
  attacking_animation->set_values(
      std::make_pair(719, 523),
      std::make_pair(719, 523),
      std::make_pair(0, 0)
      );
  attacking_animation->in_loop = false;

  add_animation("idle_animation",idle_animation);
  add_animation("attacking_animation",attacking_animation);
  idle_animation->activate();
  set_actual_animation(idle_animation);
}

engine::Animation* UncleHead::create_animation(
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

void UncleHead::initialize_hitboxes(){
  engine::Game& game = engine::Game::get_instance();
  engine::Hitbox* head_hitbox = new engine::Hitbox(
    "head_hitbox",
    this->get_position(),
    std::make_pair(160, 380),
    std::make_pair(180,20),
    game.get_renderer()
  );

  add_component(head_hitbox);
}

void UncleHead::initialize_state_map(){
  states.set_state("ACTION_STATE","NORMAL");
}

void UncleHead::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - 10);
  }
}

void UncleHead::notify(engine::Observable *game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    move(little_girl);
  }
}
/*
void UncleHead::attack(){
  states.set_state("ACTION_STATE","ATTACKING");
  std::string actual_x_state = get_state("X_STATE");
  if(actual_x_state == "LOOKING_LEFT"){
    set_actual_animation(animations["attacking_left_animation"]);
  }else if(actual_x_state == "LOOKING_RIGHT"){
    set_actual_animation(animations["attacking_right_animation"]);
  }
  play_song("attack");
}

void UncleHead::on_attack(GameObject *game_object){
  states.set_state("ACTION_STATE","ON_ATTACK");

  std::string actual_x_state = get_state("X_STATE");
  hit(game_object, 15);

  if(is_alive()){
    if(actual_x_state == "LOOKING_LEFT"){
      set_actual_animation(animations["on_attack_left_animation"]);
    }else if(actual_x_state == "LOOKING_RIGHT"){
      set_actual_animation(animations["on_attack_right_animation"]);
    }
    play_song("hit_me");
  }
}

void UncleHead::die(engine::GameObject *game_object){
  std::string actual_x_state = get_state("X_STATE");
  if(actual_x_state == "LOOKING_LEFT"){
    states.set_state("ACTION_STATE", "DYING");
    set_actual_animation(animations["dying_left_animation"]);
  }else if(actual_x_state == "LOOKING_RIGHT"){
    states.set_state("ACTION_STATE", "DYING");
    set_actual_animation(animations["dying_right_animation"]);
  }
  play_song("hit_me");
}
*/
void UncleHead::move(engine::GameObject* girl){
  //TODO Implements head movimentation
}

void UncleHead::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  //TODO Implements head collision

  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(little_girl &&
     little_girl->get_state("ACTION_STATE") == "ATTACKING" &&
     my_hitbox->get_name() == "head_hitbox" &&
     little_girl->get_actual_animation()->actual_column == 2){

    for(int i  = 0;i < 10;++i)
     std::cout << "Foi atackado bem na cara " << std::endl;
  }
}
