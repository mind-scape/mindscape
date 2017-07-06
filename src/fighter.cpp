#include "fighter.hpp"

using namespace mindscape;

void Fighter::hit(engine::GameObject *killer, int lost_hp){
  hitpoints -= lost_hp;
  if(hitpoints <= 0)
    die(killer);
}

void Fighter::heal(int p_hitpoints){
  hitpoints += p_hitpoints;
  if(hitpoints > max_hitpoints)
    hitpoints = max_hitpoints;
}

int Fighter::get_hp(){
  return hitpoints;
}

void Fighter::set_hp(int hp){
  hitpoints = hp;
}

bool Fighter::is_life_full(){
  return hitpoints == max_hitpoints;
}

bool Fighter::is_alive(){
  return hitpoints > 0;
}
