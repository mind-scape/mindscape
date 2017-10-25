/** 
 * @file component.cpp
 * @brief Contains methods to component class' management. This methods can control the entire 
 * component object, naming the component, setting the priority, verifing activation and displacing. 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "component.hpp"

using namespace engine;

/**
 * @brief This Routine verifys if the component is active or deactive.
 * 
 * In order to know what to render and to minimize the use of memory is necessary to identify if the component is
 * active or deactive.
 *  
 * @return The active state of that component, can be true meaning that the component is active or false meaning
 * that the component is false.
 */
bool Component::is_active() {
	return active;
}


/**
 * @brief This Routine activate the current component.
 * 
 * Is important to manage components activating them or deactivating to get a better game performace.
 *  
 * @return void.
 */
void Component::activate() {
	active = true;
}

/**
 * @brief This Routine deactivate the current component.
 * 
 * Is important to manage components activating them or deactivating to get a better game performace.
 *  
 * @return void.
 */
void Component::deactivate() {
	active = false;
}

/**
 * @brief This Routine get the current component displacement.
 * 
 * This will show were the component is on screen.
 *  
 * @return pair of integer containig the X and Y of screen where the component is.
 */
std::pair<int, int> Component::get_displacement() {
	return displacement;
}

/**
 * @brief This Routine set the current component displacement.
 * 
 * This will place the component on screen in a X and Y coordenate.
 * 
 * @param pair of integers containing the postion to displace the component. 
 * @return void.
 */
void Component::set_displacement(std::pair<int, int> p_displacement) {
	displacement = p_displacement;
}

/**
 * @brief This Routine get the current component priority.
 * 
 * Is important to know the priority in order to run physics and render this component.
 *  
 * @return integer with the layer of priority of that component.
 */
int Component::get_priority() {
	return priority;
}

/**
 * @brief This Routine set the current component priority.
 * 
 * Is important to set the priority in order to run physics and render this component. If is necessary to render one image in 
 * front of one animation this can be use to layer them.
 *  
 * @param integer containing the priority to be set to the component.
 * @return void.
 */
void Component::set_priority(int p_priority) {
	priority = p_priority;
}

/**
 * @brief This Routine get the current component name.
 * 
 * Is important to identify component by name, because one game object can have mode than one component and 
 * his name is the ID.
 *  
 * @return string with the component name.
 */
std::string Component::get_name() {
	return name;
}

/**
 * @brief This Routine set the current component name.
 * 
 * Is important to identify component by name, because one game object can have mode than one component and 
 * his name is the ID.
 *  
 * @param string containing the component name to be set.
 * @return void.
 */
void Component::set_name(std::string p_name) {
	name = p_name;
}
