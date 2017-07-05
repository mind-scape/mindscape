#include "enemy.hpp"

using namespace mindscape;

void Enemy::update_HP(int HP_update){
  HP+=HP_update;
}

int Enemy::get_HP(){
  return HP;
}
