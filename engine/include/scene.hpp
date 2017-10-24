/**
* @file scene.hpp
* @brief Purpose: Contains the Scene class declaration.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#ifndef SCENE_H
#define SCENE_H

#include "SDL2basics.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
#include "event_handler.hpp"

namespace engine {
    /**
    * @brief A Scene class.
    *
    * A class responsible to ensure scene handling.
    *
    */
    class Scene {
        private:
            void run_collisions(void);
            
            void update_game_objects_states();

        protected:
            std::vector<GameObject*> objects;

        public:
            Scene() {};
            
            ~Scene() {};

            void add_object(GameObject* object);

            GameObject *get_object_by_name(std::string);
            
            virtual void draw() {};
            
            virtual void load() {};
            
            virtual void free() {};
            
            void activate_game_object(GameObject *);
            
            void deactivate_game_object(std::string name);
            
            void deactivate();
            
            void activate();
            
            void update();
    };
}

#endif
