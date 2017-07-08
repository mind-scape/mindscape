#include "../include/clown.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/game.hpp"
#include "level_factory.hpp"
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
  engine::Animation* idle_animation = create_animation(
      "../assets/images/sprites/enemies/clown/clown_idle.png",
      1, 15, 3.0, "LEFT"
      );
  idle_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );

  engine::Animation* on_attack_animation = create_animation(
      "../assets/images/sprites/enemies/clown/clown_on_attack.png",
      1, 4, 0.4, "LEFT"
      );
  on_attack_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );
  on_attack_animation->in_loop = false;

  engine::Animation* dying_animation = create_animation(
      "../assets/images/sprites/enemies/clown/clown_dying.png",
      1, 5, 0.9, "LEFT"
      );
  dying_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );
  dying_animation->in_loop = false;
  dying_animation->is_a_final_animation = true;

  engine::Animation* attacking_animation = create_animation(
      "../assets/images/sprites/enemies/clown/clown_attacking.png",
      1, 6, 1.5, "LEFT"
      );
  attacking_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );

  engine::Animation* idle_vulnerable_animation = create_animation(
      "../assets/images/sprites/enemies/clown/clown_vulnerable_idle.png",
      1, 15, 3.0, "LEFT"
      );
  idle_vulnerable_animation->set_values(
      std::make_pair(448, 448),
      std::make_pair(448, 448),
      std::make_pair(0, 0)
      );

  add_animation("idle_animation",idle_animation);
  add_animation("on_attack_animation",on_attack_animation);
  add_animation("dying_animation",dying_animation);
  add_animation("attacking_animation",attacking_animation);
  add_animation("idle_vulnerable_animation",idle_vulnerable_animation);
  idle_animation->activate();
  set_actual_animation(idle_animation);
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
    std::make_pair(160, 380),
    std::make_pair(180,20),
    game.get_renderer()
  );

  engine::Hitbox* attack_hitbox = new engine::Hitbox(
    "attack_hitbox",
    this->get_position(),
    std::make_pair(120, 170),
    std::make_pair(100,25),
    game.get_renderer()
  );

  engine::Hitbox* head_hitbox = new engine::Hitbox(
    "head_hitbox",
    this->get_position(),
    std::make_pair(120, 90),
    std::make_pair(110,110),
    game.get_renderer()
  );

  add_component(foot_hitbox);
  add_component(attack_hitbox);
  add_component(head_hitbox);
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
  std::string actual_action_state = get_state("ACTION_STATE");

  if(actual_action_state == "VULNERABLE"){
    if(get_actual_animation()->is_finished){
      set_actual_animation(animations["idle_vulnerable_animation"]);
    }
    vulnerable_counter++;
    if(vulnerable_counter >= 600){
      states.set_state("ACTION_STATE","NORMAL");
      set_actual_animation(animations["idle_animation"]);
      vulnerable_counter = 0;
    }else{
      return;
    }
  }
  if(actual_action_state == "DYING") return;
  if(actual_action_state == "ON_ATTACK" || actual_action_state == "ATTACKING"){
    if(get_actual_animation()->is_finished){
      states.set_state("ACTION_STATE","NORMAL");
      set_actual_animation(animations["idle_animation"]);
    }else{
      return;
    }
  }

  int clown_position = get_position_x();
  int little_girl_position = little_girl->get_position_x();
  int distance_from_girl = clown_position - little_girl_position;

  if(distance_from_girl < 650){
    attack_animation_trigger += 1;
    if(attack_animation_trigger == 90){
      states.set_state("ACTION_STATE","ATTACKING");
      set_actual_animation(animations["attacking_animation"]);

      int clown_attack_option = rand() % 1000;

      if(clown_attack_option < 300){
        basic_attack();
      }else if(clown_attack_option >= 300 && clown_attack_option < 700){
        double_attack();
      }else{
        serial_attack();
      }

      attack_animation_trigger = 0;
    }
  }
}

void Clown::basic_attack(){
    clown_goops.clear();
    engine::GameObject* goop = new Goop("goop",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
    engine::Game::get_instance().get_actual_scene()->add_object(goop);
    engine::Game::get_instance().get_actual_scene()->activate_game_object(goop);
    goop->load();
    goop->set_speed_x(-30.0);
    goop->set_speed_y(-10);
    clown_goops.push_back(goop);
}

void Clown::double_attack(){
    clown_goops.clear();
    engine::GameObject* goop_5 = new Goop("goop_5",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
    engine::Game::get_instance().get_actual_scene()->add_object(goop_5);
    engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_5);
    goop_5->load();
    goop_5->set_speed_x(-7.0);
    goop_5->set_speed_y(-10);
    clown_goops.push_back(goop_5);

    engine::GameObject* goop_6 = new Goop("goop_6",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
    engine::Game::get_instance().get_actual_scene()->add_object(goop_6);
    engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_6);
    goop_6->load();
    goop_6->set_speed_x(-15.0);
    goop_6->set_speed_y(-10);
    clown_goops.push_back(goop_6);
}

void Clown::serial_attack(){
  if(clown_goops.size() > 3) clown_goops.clear();
  engine::GameObject* goop_1 = new Goop("goop_1",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
  engine::Game::get_instance().get_actual_scene()->add_object(goop_1);
  engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_1);
  goop_1->load();
  goop_1->set_speed_x(-20.0);
  goop_1->set_speed_y(-8.0);
  engine::GameObject* goop_2 = new Goop("goop_2",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
  engine::Game::get_instance().get_actual_scene()->add_object(goop_2);
  engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_2);
  goop_2->load();
  goop_2->set_speed_x(-20.0);
  goop_2->set_speed_y(-20.0);
  engine::GameObject* goop_3 = new Goop("goop_3",std::make_pair(get_position_x() + 40,get_position_y() + 150),60);
  engine::Game::get_instance().get_actual_scene()->add_object(goop_3);
  engine::Game::get_instance().get_actual_scene()->activate_game_object(goop_3);
  goop_3->load();
  goop_3->set_speed_x(-20.0);
  goop_3->set_speed_y(-25.0);

  clown_goops.push_back(goop_1);
  clown_goops.push_back(goop_2);
  clown_goops.push_back(goop_3);
}

void Clown::on_attack(engine::GameObject *game_object){
  //states.set_state("ACTION_STATE","ON_ATTACK");

  hit(game_object, 1);

  if(is_alive()){
    set_actual_animation(animations["on_attack_animation"]);
    //play_song("hit_me");
  }
}

engine::GameObject* Clown::create_goop(){
    engine::GameObject* goop = new Goop("goop",std::make_pair(885,420),60);
    engine::Game::get_instance().get_actual_scene()->add_object(goop);
    engine::Game::get_instance().get_actual_scene()->activate_game_object(goop);
    goop->load();
    return goop;
}

void Clown::die(engine::GameObject *game_object){
  std::string actual_x_state = get_state("X_STATE");
  states.set_state("ACTION_STATE", "DYING");
  set_actual_animation(animations["dying_animation"]);
  //play_song("hit_me");

  LevelFactory *level_factory = new LevelFactory();
  engine::Game* game = &(engine::Game::get_instance());
  level_factory->update_level(
    dynamic_cast<engine::Level *>(game->get_actual_scene()),
    "../data/win.dat"
  );

  game->set_state(engine::Game::PAUSED);
}

void Clown::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  Platform* platform = dynamic_cast<Platform *>(other);
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(other);
  Goop* goop = dynamic_cast<Goop *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && platform && my_hitbox->get_name() == "foot_hitbox"){
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 380);
  }if(little_girl &&
     little_girl->get_state("ACTION_STATE") == "ATTACKING" &&
     my_hitbox->get_name() == "attack_hitbox" &&
     little_girl->get_actual_animation()->actual_column == 2
     && get_state("X_STATE") != little_girl->get_state("X_STATE")
      && get_state("ACTION_STATE") == "VULNERABLE"){
        if(get_state("ACTION_STATE") == "ON_ATTACK") return;
        else on_attack(other);
  }if(goop){
    if(get_state("ACTION_STATE") == "NORMAL" && goop->get_state("ACTION_STATE") == "REFUTED"
      && my_hitbox->get_name() == "head_hitbox"){
        refuted_goop_hits++;
        goop->set_actual_animation(goop->animations["goop_squash_animation"]);
        goop->set_speed_x(0.0);
        if(refuted_goop_hits >= 20){
          states.set_state("ACTION_STATE","VULNERABLE");
          set_actual_animation(animations["idle_vulnerable_animation"]);
          refuted_goop_hits = 0;
          //engine::Game::get_instance().get_actual_scene()->deactivate_game_object(goop->name);
          //goop->free();
        }
    }
  }
}
