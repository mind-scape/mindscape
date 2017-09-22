/**
 * @file game.hpp
 * @brief Purpose: Contains classes to define methods management of the game.cpp.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef GAME_H
#define GAME_H

#include "SDL2basics.hpp"
#include <string>
#include <unordered_map>
#include "image.hpp"
#include "audio.hpp"
#include "text.hpp"
#include "event_handler.hpp"
#include "scene.hpp"
#include "color.hpp"
#include "hitbox.hpp"

namespace engine {

    class Scene;
    class EventHandler;

    /**
     * @brief A Hitbox class.
     *
     * This class is a model that contains all specifications of the game.
     * What is necessary to load, pause and quit the game.
     * All of attributes is too important to start the game, renderer, and resize the window.
     */
    class Game {

    public:
        typedef enum {
            RUNNING, PAUSED, QUIT

        } State;

    private:
        static Game* instance;

        std::string name;
        std::pair<int,int> window_dimensions;
        Color game_background_color = Color(0xAA, 0xAA, 0xAA, 0xAA);
        State state;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Scene* actual_scene;

        bool loaded_media = false;

        Game() {};

        void init();
        void set_information(std::string,std::pair<int,int>);

    public:
        ~Game() {};

        static Game& get_instance();
        static Game& initialize(std::string, std::pair<int, int>);

        void run();
        void close();
        void load_media();
        bool is_media_loaded();
        void change_scene(Scene *);

        void set_game_background_color(int R, int G, int B, int A);
        void set_name(std::string);
        void set_window_dimensions(std::pair<int, int>);
        std::pair<int, int> get_window_dimensions();
        void set_state(State);

        std::string get_name();
        State get_state();
        SDL_Renderer *get_renderer();
        Scene* get_actual_scene();

  };

}

#endif
