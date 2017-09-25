/** 
 * @file game_object.hpp
 * @brief Contains methods to game_object class' management. This methods can control the entire 
 * game object, setting the components, free them, loading and playing audio, animations, components, 
 * setting and displaying hitboxes, detecting and notifing collission with other game objects. 
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

//TODO trocar os vectors de componentes para unordered maps
//TODO acabar com o primeiro construtor e definir hit box como um componente
//TODO colocar todos os estados para usar o SATE MAP

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "SDL2basics.hpp"
#include "component.hpp"
#include "image.hpp"
#include "text.hpp"
#include "audio.hpp"
#include "hitbox.hpp"
#include "keyboard_event.hpp"
#include "state_map.hpp"
#include "animation.hpp"
#include "observer.hpp"
#include "observable.hpp"
#include "../../include/game_event.hpp"

namespace engine {

    class Animation;

    /** 
     * @brief A Game class.
     * 
     * This class can control all the components of the game object.
     * @warning Limitations: The number of game object in game is limited to the pc memory. All game object after being
     * used needs to be free.
     */
    class GameObject : public Observer, public Observable {
        private:
            std::pair<float, float> speed = std::make_pair(0.0, 0.0);
            std::pair<float, float> position = std::make_pair(0.0, 0.0);
            std::vector<Hitbox *> hitboxes;
            Animation* actual_animation = NULL;
            bool active = true;
            std::list<Observer *> observers;

            void run_collisions(GameObject *);

        protected:
            virtual void on_collision(GameObject *, Hitbox *, Hitbox *) {

            };

        public:
            static bool on_limit_of_level;
            std::string name;
            int priority;
            bool collidable;
            std::vector<Component *> audios;
            std::vector<Component *> images;
            std::vector<Component *> texts;
            std::map<std::string, Animation *> animations;
            std::map<KeyboardEvent::Key, std::string> translations;
            std::string state;
            std::string game_object_direction;
            StateMap states;

            GameObject() {

            };

            GameObject(
              std::string p_name,
              std::pair<float, float> p_position,
              int p_priority,
              std::map<KeyboardEvent::Key,std::string> p_translations,
              StateMap p_states = StateMap())

            :name(p_name),
            position(p_position),
            active(false),
            priority(p_priority),
            translations(p_translations),
            states(p_states),
            speed(std::make_pair(0.0, 0.0)) {

            };

            ~GameObject() {

            };

            bool load();
            void free();
            void draw();
            void add_component(Component *);
            void add_animation(std::string, Animation *);
            bool equals(GameObject *);
            void collide(GameObject *);
            Audio * get_audio_by_name(std::string);
            void play_song(std::string);
            void stop_song(std::string);
            void set_repetitions(std::string, int repet);
            void set_music_volume(std::string, int vol);
            void free_music(std::string);
            std::pair<float, float> get_position();
            float get_position_x();
            float get_position_y();
            void set_position(std::pair<float, float>);
            void set_position_x(float);
            void set_position_y(float);
            std::pair<float, float> get_speed();
            float get_speed_x();
            float get_speed_y();
            void set_speed(std::pair<float, float>);
            void set_speed_x(float);
            void set_speed_y(float);
            void activate();
            void deactivate();
            void deactivate_components();
            bool is_active();
            std::string get_state(std::string);
            std::vector<Hitbox*> get_hitboxes();
            void create_hitbox(std::pair<int, int>, std::pair<int, int>);
            virtual void on_event(GameEvent) {

            };
            void update_hitboxes();
            virtual void update_state();
            void set_actual_animation(Animation *);
            Animation* get_actual_animation();
            void attach_observer(Observer *);
            void detach_observer(Observer *);
            void notify_observers();
            virtual void notify(Observable *) {

            };
      };
}

#endif
