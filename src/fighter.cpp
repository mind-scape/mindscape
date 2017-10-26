/** 
 * @file fighter.cpp
 * @brief Purpose: Contains methods to game class' management.
 * 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "fighter.hpp"

using namespace mindscape;

/**
 * @brief Reduces the character life.  
 * 
 * Which time the character is damaged the method is called, 
 * and it loses its life.
 *  
 * @param killer object who causes damage to the character.
 * @param lost_hp quantity of damage caused in character's life.
 * @fn die() documented in src/.cpp of clow, dark_girl, little_girl, scorpion, 
 * spider and uncle.  
 * @return void.
 */
void Fighter::hit(engine::GameObject *killer, int lost_hp){
    hitpoints -= lost_hp;

    if(hitpoints <= 0) {
        die(killer);
    }
}

/**
 * @brief Increases the character life.  
 * 
 * Which time the character gains life(hp) bonus, this method is called and
 * increases its life, respecting the life's limit.
 * 
 * @param p_hitpoints quantity of hp gained.
 * @return void.
 */
void Fighter::heal(int p_hitpoints){
    hitpoints += p_hitpoints;

    if(hitpoints > max_hitpoints) {
        hitpoints = max_hitpoints;
    }
}

/**
 * @brief Gets the character's life.  
 * 
 * Gets the value of the current character's life.
 * @return int.
 */
int Fighter::get_hp(){
    return hitpoints;
}

/**
 * @brief Sets the character's life.  
 * 
 * Sets the value of the current character's life.
 * @param hp quantity of life.
 * @return void.
 */
void Fighter::set_hp(int hp){
    hitpoints = hp;
}

/**
 * @brief Verify if the character is full.  
 * 
 * Verify if the character's life is in the maximum.
 * @return bool True if the life is full, false if it is not.
 */
bool Fighter::is_life_full(){
    return hitpoints == max_hitpoints;
}

/**
 * @brief Verify if the character is alive.  
 * 
 * Verify if the character's life is smaller than zero.
 * @return bool True if the life is smaller than zero, false if it is not.
 */
bool Fighter::is_alive(){
    return hitpoints > 0;
}
