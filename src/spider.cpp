#include "../include/spider.hpp"
#include "../include/platform.hpp"

using namespace game;

void Spider::on_event(GameEvent){
  //implement
}

void Spider::update(unsigned delta){
  if(!on_floor) speed.second += 0.02 * delta;
  if(speed.second > 1){
    speed.second = 1;
  }
  if(speed.second >= 0){
    state = "FALLING";
  }
  position.second += speed.second * delta;
  on_floor = false;
}

void Spider::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox){
  engine::Platform* p = dynamic_cast<engine::Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);
  if(state == "FALLING" && p){
    on_floor = true;
    speed.second = 0;
    position.second = other_hitbox->get_coordinates().second - 280;
    state = "GROUND";
  }
}
