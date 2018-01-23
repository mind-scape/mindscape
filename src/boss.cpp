/**
* @file boss.cpp
* @brief Purpose: Contains methods that allow boss handling.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "boss.hpp"

using namespace mindscape;
/**
* @brief Creates a boss.
*
* In order to be visible and interactable, the boss must exist
*
* @param std::string containing the boss name
* @param Enemy* containing the reference of the boss
* @return void.
*/
void Boss::set_boss_part(std::string boss_part_name, Enemy* boss_part_reference){
    boss_parts[boss_part_name] = boss_part_reference;
}
/**
* @brief Getter for boss' parts.
*
* If the boss' parts are needed, there must be a getter for it
*
* @return std::map<std::string, Enemy*> containing the boss' parts.
*/
std::map<std::string,Enemy*> Boss::get_boss_parts(){
    return boss_parts;
}

