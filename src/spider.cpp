#include "../include/spider.hpp"
#include "../include/platform.hpp"
#include "../include/little_girl.hpp"

using namespace mindscape;

void Spider::on_event(GameEvent game_event){
  engine::LittleGirl* girl = engine::LittleGirl::get_instance();
  std::cout << "Posicao da aranha: " << get_position().first << std::endl;
  std::string event = game_event.game_event_name;

  if(event == "Update"){
    if(get_position().first - girl->get_position().first < 300){
      if(get_position().first > girl->get_position().first){
      set_position(std::make_pair(get_position().first - 1, get_position().second));
      }else{
        set_position(std::make_pair(get_position().first + 1, get_position().second));
      }
    }
  }else if(event == "MOVE_LEFT"){
      set_position(std::make_pair(get_position().first + 10, get_position().second));
  }else if(event == "MOVE_RIGHT"){
    set_position(std::make_pair(get_position().first - 10, get_position().second));
  }
}

void Spider::update(unsigned delta){
  printf("Ainda existo!\n");
}

void Spider::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  engine::Platform* p = dynamic_cast<engine::Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){
    set_speed(std::make_pair(get_speed_x(), 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 280));
  }
}
