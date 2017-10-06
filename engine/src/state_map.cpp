/**
 * @file state_map.cpp
 * @brief Purpose: Contains methods to change a state of the game or the 
 * characters.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/ master/LICENSE.md
 */


#include "../include/state_map.hpp"

using namespace engine;

/**
 * @brief Set a state to the game or characters.
 *
 * 	This method was implemented to set an state to the game or the 
 * characters that have an animation, where can be on attack, attacking
 * dying, normal, looking left, looking right, falling, jumping, refuted,
 * on ground, vulnerable, and others.
 *
 * @param state_name Description's name of state defined by other classes 
 * method.
 * @param state_value Description's value type represented by a string and 
 * defined by other classes method.
 * @return void.
 */

void StateMap::set_state (std::string state_name, std::string state_value) {
  	states[state_name] = state_value;
}

/**
 * @brief Get state of the game and characters.
 *
 * 	This method was implemented to get an actual state of the game or the
 * characters that have an animation.
 *
 * @param state_name Description's name of the actual state.
 * @return string The return is a string of a determined state.
 */

std::string StateMap::get_state (std::string state_name) {
  	return states[state_name];
}