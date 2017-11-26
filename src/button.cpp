/**
* @file button.cpp
* @brief Purpose: Contains the methods related to the menu buttons.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "button.hpp"

using namespace mindscape;
/**
* @brief Pauses or plays the game or changes the scene.
*
* The button may have different actions depending on the event that occured
*
* @param GameEvent containing the game event that was triggered by a button
* @return void.
*/
void Button::on_event(GameEvent game_event) {
  	std::string event_name = game_event.game_event_name;

  	if (event_name == "CHANGE_SCENE" ||
  		event_name == "PLAY_GAME" ||
  		event_name == "PAUSE_GAME") {
    	action->execute(param);
  	}
}
/**
* @brief Sets an action for the button.
*
* Every button must present an action when pressed
*
* @param Action* containing the reference of an action
* @param std::string containing the name of the action
* @return void.
*/
void Button::set_action(Action *p_action, std::string p_param) {
  	action = p_action;
  	param = p_param;
}
