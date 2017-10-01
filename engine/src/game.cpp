/**
 * @file game.cpp
 * @brief Purpose: Contains methods that create and specify a hitbox.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "game.hpp"
#include "time.hpp"
#include <iostream>
#include <cstdio>
#include <unistd.h>

using namespace engine;

Game* Game::instance = nullptr;

/**
 * @brief shows which function has an error and exits.
 *
 * @params function that has an error.
 * @return void.
 */
void throw_error(const char* function) {
    printf("Something's wrong in %s\n", function);

    exit(-1);
}

/**
 * @brief Checks if an instance was created.
 *
 * In cases when dont have an instance created, it is alerted to create one and exits.
 *
 * @return Returns the instance.
 */
Game& Game::get_instance() {
    if (!instance) {
        fprintf(stderr, "You should initialize instance first");

        exit(1);
    }

    return *instance;
}

/**
 * @brief Initializes an instance if one does not exist.
 *
 * @params p_name name of the game.
 * @params p_dimensions dimensions of the window.
 * @return Returns an instance created.
 */
Game& Game::initialize(std::string p_name, std::pair<int, int> p_dimensions) {
    if (!instance) {
        instance = new Game();
        instance->set_information(p_name, p_dimensions);
        instance->init();
    }

    return *instance;
}

/**
 * @brief Initializes the game.
 *
 * initializes all that need in background,
 * video, audio before the start the window. And treats the erros.
 *
 * @return void.
 */
void Game::init() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        throw_error("SDL_Init");
    }

    int img_flags = 0;
    img_flags = IMG_INIT_PNG;

    if (!(IMG_Init(IMG_INIT_PNG) & img_flags)) {
        throw_error("IMG_Init");
    }

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 512 ) < 0 ) {
        printf("SDL_mixer could not initialize! SDL_mixer Error:%s\n", Mix_GetError());
    }

    if (TTF_Init() == -1) {
        throw_error("TTF_Init");
    }

    window = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,window_dimensions.first,
        window_dimensions.second,SDL_WINDOW_SHOWN);

    if (!window) {
    throw_error("SDL_CreateWindow");
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED
       | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        throw_error("SDL_CreateRenderer");
    }
}

/**
 * @brief Load the media based its scene.
 *
 * @return void.
 */
void Game::load_media() {
    actual_scene->load();
    loaded_media = true;
}

/**
 * @brief Closes the game.
 *
 * Closes the game, destroying its renderer, window, functions of the game and medias.
 *
 * @return void.
 */
void Game::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = NULL;
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

/**
 * @brief This method is a test to know if media is loaded.
 *
 * @return Returns the situation of media.
 */
bool Game::is_media_loaded() {
    return loaded_media;
}

void Game::run() {
    state = RUNNING;

    if (is_media_loaded()) {
        SDL_Event e;

        EventHandler event_handler = EventHandler();

        Time::init();

        while (state != QUIT) {
            unsigned now = Time::time_elapsed();
            event_handler.dispatch_pending_events(now);

            if (state != PAUSED) {
                actual_scene->update();
            }

            SDL_SetRenderDrawColor(renderer, 0xE2, 0xAC, 0xF3, 0x00);
            SDL_RenderClear(renderer);
            actual_scene->draw();
            SDL_RenderPresent(renderer);
        }
    }

    else {
        printf("Medias could not be loaded\n");
    }

    close();
}

/**
 * @brief Sets the name and the dimensions of the window.
 *
 * @params p_name the name of the game.
 * @params p_dimensions this params refers to a dimension os the window.
 * @return void.
 */
void Game::set_information(std::string p_name,std::pair<int,int> p_dimensions) {
    set_name(p_name);
    set_window_dimensions(p_dimensions);
}

/**
 * @brief Changes the scene.
 *
 * Changes the scene based in its level and in its actual scene.
 * Loads the media based in this.
 *
 * @params level pointer to know which scene will be loaded.
 * @return void.
 */
void Game::change_scene(Scene *level) {
    if (actual_scene) {
        actual_scene->deactivate();
        actual_scene->free();
        delete actual_scene;
    }

    level->activate();
    actual_scene = level;

    load_media();
}

/**
 * @brief This Routine set the game background color.
 *
 * It is important to use RGBA to change the opacity of the background.
 * R (red) G (green) B (blue) is the regular colors and the A is the opacity nivel.
 *
 * @param integer containing the quantity of the red color to be set to the background.
 * @param integer containing the quantity of the green color to be set to the background.
 * @param integer containing the quantity of the blue color to be set to the background.
 * @param integer containing the quantity of the Alpha (A) opacity to be set to the background.
 * @return void.
 */
void Game::set_game_background_color(int R, int G, int B, int A) {
    game_background_color = Color(R, G, B, A);
}

/**
 * @brief This Routine set the name of the game.
 *
 * @param string containing the game name to be set.
 * @return void.
 */
void Game::set_name(std::string p_name) {
    name = p_name;
}

/**
 * @brief This method get the current game name.
 *
 * @return string that contains the game name.
 */
std::string Game::get_name() {
    return name;
}

/**
 * @brief This method set the window dimensions.
 *
 * it is important to scale the window on the player screen and no errors happen.
 *
 * @param map that contains two integer that will set the width and the height.
 * @return void.
 */
void Game::set_window_dimensions(std::pair<int, int> p_window_dimensions) {
    window_dimensions = p_window_dimensions;
}

/**
 * @brief This method get the window dimensions.
 *
 * It is important to resize the window dimensions accordingly the dimensions that need to run the game without bugs.
 * @return map that contains the window dimensions.
 */
std::pair<int, int> Game::get_window_dimensions() {
    return window_dimensions;
}

/**
 * @brief This method set the current game state.
 *
 * @param state that contains the game state.
 * @return void.
 */
void Game::set_state(State p_state) {
    state = p_state;
}

/**
 * @brief This method get the current game state.
 *
 * It is important to know what the game state to run the game.
 *
 * @return state of the game.
 */
Game::State Game::get_state() {
    return state;
}

/**
 * @brief This method get the renderer of the game.
 *
 * it is most important because it's the contact of the software with the user.
 * It is one the principals parts to load and close the game.
 *
 * @return renderer of the game.
 */
SDL_Renderer * Game::get_renderer() {
    return renderer;
}

/**
 * @brief This method get the current scene of the game.
 *
 * It is important to load the media of the game
 *
 *
 */
Scene* Game::get_actual_scene() {
    return actual_scene;
}
