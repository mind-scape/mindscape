/**
 * @file level.cpp
 *
 * @brief Purpose: Contains methods to level management
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "level.hpp"

using namespace engine;

/**
 * @brief Load the new level
 *
 * Initializes the game level
 *
 */
void Level::load() {
    for(auto game_object : objects) {
        /* loops every game object in the objects list */
        game_object->load();

        for(auto hit : game_object->get_hitboxes()) {
			/* iterates every hit in the hitboxes */
            hit->initialize();
        }
    }
}

/**
 * @brief Free method
 *
 * free the memory used to allocate the game objects
 *
 */
void Level::free() {
    for(auto game_object : objects) {
		/* iterates every game object in the objects list */
        game_object->free();
    }

    EventHandler::listeners.clear();
}

/**
 * @brief Draw Method
 *
 * Draw the game objects
 *
 */
void Level::draw() {
    for(auto game_object : objects) {
		/* iterates every game object in the objects list */
        if(game_object->is_active()) {
			/* if the game object is active */
            game_object->draw();
        }
    }
}
