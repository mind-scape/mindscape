#include "../include/boss.hpp"

using namespace mindscape;

void Boss::set_boss_part(std::string boss_part_name, Enemy* boss_part_reference){
  boss_parts[boss_part_name] = boss_part_reference;
}

std::map<std::string,Enemy*> Boss::get_boss_parts(){
  return boss_parts;
}

