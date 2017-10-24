/**
* @file physics.cpp
* @brief Purpose: Keep methods that are related to any physical action.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "physics.hpp"

using namespace engine;

float Physics::gravity = 1.0;
Physics *Physics::instance = 0;
std::vector<GameObject *> Physics::physicables = {};

/**
* @brief Creates a Physics object instance.
*
* Physics object is required to ensure physical simulation
*
* @return Physics instance
*/
Physics *Physics::get_instance() {
	if (!instance) {
		instance = new Physics();
	}

	return instance;
}

/**
* @brief Calculates the speed of an object
*
* The objects of the game may require speed variations.
*
* @param std::pair with the current speed
* @return std::pair with the new speed.
*/
std::pair<float, float> Physics::calculate_speed(std::pair<float, float> speed) {
	std::pair<float, float> new_speed (0.0, 0.0);

	new_speed.first = speed.first;
	new_speed.second = speed.second + gravity;

	return new_speed;
}
/**
* @brief Calculates the position of an object.
*
* With speed, the position of the game objects must change.
*
* @param std::pair with the current position of the object
* @param std::pair with the current speed of the object
* @return std::pair with the new position of the object.
*/
std::pair<float, float> Physics::calculate_position(std::pair<float, float> position, std::pair<float, float> speed) {
	std::pair<float, float> new_position (0.0, 0.0);

	new_position.first = position.first + speed.first;
	new_position.second = position.second + speed.second;

	return new_position;
}
/**
* @brief Updates the speed of a game object.
*
* The speed must be set to the game object to ensure that the changes will be reflected on the gameplay
*
* @param the GameObject instance that will have its speed updated
* @return void.
*/
void Physics::update_speed(GameObject *game_object) {
	std::pair<float, float> old_speed = game_object->get_speed();
	std::pair<float, float> new_speed = calculate_speed(old_speed);

	game_object->set_speed(new_speed);
}
/**
* @brief Updates the position of a game object.
*
* The position must be set to the game object to ensure that the changes will be reflected on the gameplay
*
* @param the GameObject instance that will have its position updated
* @return void.
*/
void Physics::update_position(GameObject *game_object) {
	std::pair<float, float> speed = game_object->get_speed();
	std::pair<float, float> old_position = game_object->get_position();
	std::pair<float, float> new_position = calculate_position(old_position, speed);

	game_object->set_position(new_position);
}
/**
* @brief Updates speed and position of a game object.
*
* Since speed and position are mostly updated at the same time, the method does both at once
*
* @param the game object that will have its speed and position updated
* @return void.
*/
void Physics::act_on(GameObject *game_object) {
	update_speed(game_object);
	update_position(game_object);
}
/**
* @brief Ensures that the game object will be affected by the physics engine.
*
* The object must me physicable to be affected by physical simulation
*
* @param the game object that will be affected
* @return void.
*/
void Physics::add_physicable(GameObject *game_object) {
	physicables.push_back(game_object);
}
/**
* @brief Ensures that the physical actions will affect all active objects.
*
* If the object is active, it must be affected by physical actions
*
* @return void.
*/
void Physics::act() {
	for (auto game_object : physicables) {
		if (game_object->is_active()) {
			act_on(game_object);
		}
	}
}
/**
* @brief Getter method for gravity.
*
* Makes gravity variable available outside the Engine
*
* @return float with the gravity value.
*/
float Physics::get_gravity() {
	return gravity;
}
