#include "../include/enemy.hpp"
#include "../include/platform.hpp"

using namespace game;

void Enemy::update(unsigned delta){
  if(!on_floor) speed.second += 0.02 * delta;
  if(speed.second > 1){
    speed.second = 1;
  }
  if(speed.second >= 0){
    state = "FALLING";
  }
  position.second += speed.second * delta;
  if(position.second >= 335){
    position.second = 335;
    speed.second = 0;
    state = "GROUND";
  }
  on_floor = false;
}
