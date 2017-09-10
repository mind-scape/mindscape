/**
 * @file persistence_map.cpp
 *
 * @brief Purpose: Contains methods to map state
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "persistence_map.hpp"

using namespace engine;

/**
 * @brief Unordered Map
 *
 *  Method responsible for ordered the state map of an object
 *
 * @param id object id
 * @return void
 */
std::unordered_map < std::string,
        std::string > PersistenceMap::get_object_by_id(std::string id) {
    int iid = std::stoi(id);

    return persistence_map[iid];
}

/**
 * @brief Insert Object
 *
 * Method Responsible for insert a map state in an object
 *
 * @param object object of the game
 *
 * @return void
 */
void PersistenceMap::insert_object(std::unordered_map<std::string,
        std::string> object) {
    persistence_map.push_back(object);
}

/**
 * @brief Insert object data
 *
 * Method responsible to insert the data in the object of the game
 *
 * @param id of the object
 * @param key key for the data
 * @param data of the object
 *
 * @return void
 */
void PersistenceMap::insert_object_data(std::string id, std::string key,
                                        std::string data) {
    int iid = std::stoi(id);

    persistence_map[iid][key] = data;
}

/**
 * @brief Get Object Data
 *
 * Responsible for get the data of the object.
 *
 * @param id of the object
 * @param key for the data
 * @return void
 */
std::string PersistenceMap::get_object_data(std::string id, std::string key) {
    int iid = std::stoi(id);

    return persistence_map[iid][key];
}
