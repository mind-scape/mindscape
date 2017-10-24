/**
* @file scene.cpp
* @brief Purpose: Contains methods that ensure correct scene handling.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "scene.hpp"
#include "physics.hpp"
#include <algorithm>

using namespace engine;
/**
* @brief Compares scenes priority.
*
* Different scenes may have different priorities
*
* @param first GameObject
* @param second GameObject
* @return bool that is true if the priority of the first is smaller than the second.
*/
bool compare_scene(engine::GameObject* a, GameObject* b) {
    return a->priority < b->priority;
}
/**
* @brief Adds an object to the scene
*
* The object, in order to be seen, must be added to the scene
*
* @param GameObject that will be added to the scene
* @return Scene containing the added object.
*/
void Scene::add_object(engine::GameObject* object) {
    objects.push_back(object);
    sort(objects.begin(), objects.end(), compare_scene);
}
/**
* @brief Gets an object by giving its name.
*
* Simplifies object searching
*
* @param std::string containing the name of the object.
* @return returns the GameObject if it was found or NULL if it wasn't.
*/
GameObject *Scene::get_object_by_name(std::string name) {
    for (auto game_object : objects) {
        if (name == game_object->name) {
            return game_object;
        }
        else {
            /* Do nothing */
        }
    }
    
    return NULL;
}
/**
* @brief Activates a game object and adds a listener to notify other objects.
*
* When the object is activated, the others must be notified.
*
* @param GameObject that will be activated
* @return void.
*/
void Scene::activate_game_object(GameObject *go) {
    go->activate();
    EventHandler::add_listener(go);
}
/**
* @brief Deactivated a game object and adds a listener to notify other objects.
*
* When the object is deactivated, the others must be notified.
*
* @param std::string containing the name of the game object that will be deactivated.
* @return void.
*/
void Scene::deactivate_game_object(std::string game_object_name) {
    int counter = 0;
    
    for (auto go : objects) {
        if (go->name == game_object_name) {
            go->deactivate();
            EventHandler::remove_listener(go);
            objects.erase(objects.begin() + counter);
    
            break;
        }
        else {
            /* Do nothing */
        }
        counter++;
    }
}
/**
* @brief Deactivates a scene and adds a listener to notify other objects.
*
* When the scene is deactivated, the others must be notified
*
* @return void.
*/
void Scene::deactivate() {
    for (auto go : objects) {
        go->deactivate();
    }
    EventHandler::listeners.clear();
}
/**
* @brief Activates a scene and adds a listener to notify other objects.
*
* When the scene is Activated, the others must be notified
*
* @return void.
*/
void Scene::activate() {
    for (auto go : objects) {
        activate_game_object(go);
    }
}
/**
* @brief Runs collisions that may occur
*
* The objects in the game must present collision behavior
*
* @return void.
*/
void Scene::run_collisions() {
    for (auto go : objects) {
        if (go->collidable) {
            for (auto another_go : objects) {
                go->collide(another_go);
            }
        }
        else {
            /* Do nothing */
        }
    }
}
/**
* @brief Updates the game objects states
*
* The game objects must have its states updated when necessary
*
* @return void.
*/
void Scene::update_game_objects_states() {
    for (auto go : objects) {
        go->update_state();
    }
}
/**
* @brief Updates the scene.
*
* All the method related to physics must be activated at once every scene update
*
* @return void.
*/
void Scene::update() {
    Physics *physics = Physics::get_instance();
    physics->act();

    run_collisions();
    update_game_objects_states();
}