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
#include <unistd.h>
#include "log.hpp"
#include <assert.h>

using namespace engine;

Game* Game::instance = NULL; /**< initialization of the game instance singleton */

/**
 * @brief shows which function has an error and exits.
 *
 * @params function that has an error.
 * @return void.
 */
void throw_error(const char* function) {
    assert(function);
    WARN(("Something's wrong in %s\n", function));
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
    DEBUG("Getting instance of game");
    assert(instance);

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
        /* if the instance is null */
        instance = new Game();
        instance->set_information(p_name, p_dimensions);
        instance->init();
        assert(instance);
    }
    else {
        /*Do nothing*/
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
    int img_flags = IMG_INIT_PNG; /**< flags for sdl image lib */

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        /* if the initialization of the video and audio doesn't work properly */
        WARN("Audio and video not initialized properly");
        throw_error("SDL_Init");
    }
    else {
        /*Do nothing*/
    }

    img_flags = IMG_INIT_PNG;

    if (!(IMG_Init(IMG_INIT_PNG) & img_flags)) {
        /* if the initialization of sdl img is not working properly */
        WARN("SDL IMG not initialized properly");
        throw_error("IMG_Init");
    }
    else {
        /*Do nothing*/
    }

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 512 ) < 0 ) {
        /* if the mix audio sdl lib is not working properly */
        WARN(("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError()));
    }
    else {
        /*Do nothing*/
    }

    if (TTF_Init() == -1) {
        /* if the ttf sdl lib is not working properly */
        WARN("TTF SDL lib not initialized properly");
        throw_error("TTF_Init");
    }
    else {
        /*Do nothing*/
    }

    window = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,window_dimensions.first,
        window_dimensions.second,SDL_WINDOW_SHOWN);

    if (!window) {
        /* if the window is null it means it didnt work well */
        WARN("Window not created");
   		throw_error("SDL_CreateWindow");
    }
    else {
        /*Do nothing*/
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED
       | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        /* if renderer is null then it was not instantiated correctly */
        WARN("Renderer is null");
        throw_error("SDL_CreateRenderer");
    }
    else {
        /*Do nothing*/
    }
}

/**
 * @brief Load the media based its scene.
 *
 * @return void.
 */
void Game::load_media() {
    actual_scene->load();
    assert(actual_scene);
    loaded_media = true;
}

/**
 * @brief This method is a test to know if media is loaded.
 *
 * @return Returns the situation of media.
 */
 bool Game::is_media_loaded() {
    assert(loaded_media == 1 || loaded_media == 0);
    return loaded_media;
}

/**
 * @brief Closes the game.
 *
 * Closes the game, destroying its renderer, window, functions of the game and medias.
 *
 * @return void.
 */
void Game::close() {
    DEBUG("Attempting to close game");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = NULL;
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

/**
 * @brief Renders a given scene.
 *
 * Given a scene, it replaces the previous with the given.
 *
 * @params SDL_Renderer* renderer that will render the new scene.
 * @params Scene* actual_scene that is the scene that will be updated.
 *
 * @return void.
 */
void renderScreen(SDL_Renderer* renderer, Scene* actual_scene) {
    assert(renderer);
    assert(actual_scene);

    const Uint8 r_value = 0xE2;
    const Uint8 g_value = 0xAC;
    const Uint8 b_value = 0xF3;
    const Uint8 a_value = 0x00;

    SDL_SetRenderDrawColor(renderer, r_value, g_value, b_value, a_value);
    SDL_RenderClear(renderer);
    actual_scene->draw();
    SDL_RenderPresent(renderer);
}

/**
 * @brief Runs the game.
 *
 * Runs the game updating the scenes and verifying the states.
 *
 * @return void.
 */
void Game::run() {
    state = RUNNING;
    DEBUG("Game is running");

    bool media_is_loaded = is_media_loaded();

    if (media_is_loaded && !media_is_loaded) {
        WARN("Failed media loaded verification");
        throw_error("Invalid bool value");
    }

    if (media_is_loaded) {
        DEBUG("Game media is loaded");
		/* if the media is already loaded */
        SDL_Event e;

        EventHandler event_handler = EventHandler();

        assert(event_handler);

        Time::init();

        while (state != QUIT) {
			/* while the state is not quit */
            unsigned now = Time::time_elapsed();
            event_handler.dispatch_pending_events(now);

            if (state != PAUSED) {
				/* if the state is different from pause state */
                actual_scene->update();
            }
            else {
                /*Do nothing*/
            }

            renderScreen(renderer, actual_scene);
        }
    }
    else {
		/* print if the medias were not yet loaded */
        WARN("Medias could not be loaded\n");
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
    assert(p_dimensions.first >= 0 && p_dimensions.second >= 0);

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
    /*Function core*/
    DEBUG("Changing scene");
    if (actual_scene) {
		/* if actual scene is not null */
        actual_scene->deactivate();
        actual_scene->free();
        delete actual_scene;
    }
    else {
        /*Do nothing*/
    }

    /*Modifies referenced parameter*/
    level->activate();
    actual_scene = level;
    load_media();
}

/**
 * @brief This method get the current scene of the game.
 *
 * It is important to load the media of the game
 *
 *
 */
 Scene* Game::get_actual_scene() {
    assert(actual_scene);
    return actual_scene;
}

/**
 * @brief This routine validates an RGBA color.
 *
 * It is important to use RGBA to change the opacity of the background.
 * R (red) G (green) B (blue) is the regular colors and the A is the opacity nivel.
 *
 * @param integer containing the quantity of the red color.
 * @param integer containing the quantity of the green color.
 * @param integer containing the quantity of the blue color.
 * @param integer containing the quantity of the Alpha (A) opacity.
 * @return void.
 */
bool Game::RGBA_color_is_valid(int R, int G, int B, int A) {
    /*Variables declaration*/
    bool color_is_valid = true;

    /*Function core*/
    if (R < 0 || R > 255) {
        /*Given value for red channel is out of limits, therefore, invalid*/
        color_is_valid = false;
    }
    else if (G < 0 || G > 255) {
        /*Given value for green channel is out of limits, therefore, invalid*/
        color_is_valid = false;
    }
    else if (B < 0 || B > 255) {
        /*Given value for blue channel is out of limits, therefore, invalid*/
        color_is_valid = false;
    }
    else if (A < 0 || A > 255) {
        /*Given value for alpha channel is out of limits, therefore, invalid*/
        color_is_valid = false;
    }
    else {
        /*All values are valid*/
    }

    if (color_is_valid != true && color_is_valid != false) {
      WARN("Invalid bool value in RGBA_color_is_valid");
      throw_error("Invalid bool value");
    }
    return color_is_valid;
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
    bool color_is_valid = RGBA_color_is_valid(R, G, B, A);

    if (color_is_valid != true && color_is_valid != false) {
      WARN("Failed color validation");
      throw_error("Invalid bool value");
    }

    if (color_is_valid) {
        /*Ensures that the color values given are valid*/
        game_background_color = Color(R, G, B, A);
    }
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
