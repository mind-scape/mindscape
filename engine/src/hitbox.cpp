/**
 * @file hitbox.cpp
 * @brief Purpose: Contains methods that create and specify a hitbox.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include <string>
#include <iostream>
#include "hitbox.hpp"

using namespace engine;

/**
 * @brief This method return the width and height of the hitbox.
 *
 * @return std::pair<int, int> Dimensions of the hitbox.
 */
std::pair<int, int> Hitbox::get_dimensions() {
    return std::make_pair(hitbox.w, hitbox.h);
}

/**
 * @brief This method set the width and height of the hitbox.
 *
 * @params p_dimensions is it the pointer that sets the dimensions of hitbox.
 * @return void.
 */
void Hitbox::set_dimensions(std::pair<int, int> p_dimensions) {
    hitbox.w = p_dimensions.first;
    hitbox.h = p_dimensions.second;
}

/**
 * @brief Sets the new coordinate of the hitbox after its movement
 *
 * this method calculate the new coordinate of the hitbox based in the its
 * coordinate plus its coordinate of the movement.
 *
 * @params go_coordinates coordinate that the hitbox will go.
 * @params p_displacement coordinate that the hitbox is.
 * @return void.
 */
void Hitbox::set_displacement(std::pair<int, int> go_coordinates,
    std::pair<int, int> p_displacement) {

    hitbox.x = p_displacement.first + go_coordinates.first;
    hitbox.y = p_displacement.second + go_coordinates.second;

    Component::set_displacement(p_displacement);
}

/**
 * @brief Update the coordinate of the hitbox after its movement
 *
 * this method updates the coordinate of the hitbox based in the its
 * coordinate plus its coordinate of the movement.
 *
 * @params go_coordinates coordinate that the hitbox will go.
 * @return void.
 */
void Hitbox::update(std::pair<int, int> go_coordinates) {
    hitbox.x = get_displacement().first + go_coordinates.first;
    hitbox.y = get_displacement().second + go_coordinates.second;
}

/**
 * @brief This method gets the coordinates of the hitbox.
 *
 * @return Returns the position in axis X and Y of the hitbox.
 */
std::pair<int, int> Hitbox::get_coordinates() {
    return std::make_pair(hitbox.x, hitbox.y);
}

/**
 * @brief Defines the collides with others hitboxes.
 *
 * this method defines the collision with two hitbox,
 * based in its coordinates and dimensions
 *
 * @params other_hitbox A hitbox object to identify collision between them.
 * @return returns true if the collision was identify.
 */
bool Hitbox::collides_with(Hitbox* other_hitbox) {
    std::pair<int, int> other_hitbox_dimensions;
    std::pair<int, int> other_hitbox_coordinates;

    int left_a;
    int left_b;

    int right_a;
    int right_b;

    int top_a;
    int top_b;

    int bottom_a;
    int bottom_b;

    left_a = hitbox.x;
    right_a = hitbox.x + hitbox.w;
    top_a = hitbox.y;
    bottom_a = hitbox.y + hitbox.h;

    other_hitbox_coordinates = other_hitbox->get_coordinates();
    other_hitbox_dimensions = other_hitbox->get_dimensions();

    // x coordinate and width's dimension, respectively

    left_b = other_hitbox_coordinates.first;
    right_b = other_hitbox_coordinates.first +
            other_hitbox_dimensions.first;

    // y coordinate and height's dimension, respectively

    top_b = other_hitbox_coordinates.second;
    bottom_b = other_hitbox_coordinates.second +
             other_hitbox_dimensions.second;

    if (bottom_a <= top_b) {
        return false;
    }

    if (top_a >= bottom_b) {
        return false;
    }

    if (right_a <= left_b) {
        return false;
    }

    if (left_a >= right_b) {
        return false;
    }

    return true;
}

/**
 * @brief Load and show the hitbox on the screen.
 *
 *  this method load an image and initialize as a hitbox.
 *
 * @return void.
 */
void Hitbox::initialize() {
    SDL_Texture* new_texture = NULL;

    SDL_Surface* loaded_surface =
        IMG_Load("../assets/images/scenes/test_scene/Fundo-Vermelho.jpg");

    if (loaded_surface != NULL) {
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

        if (new_texture == NULL) {
            printf("Unable to create texture from! SDL Error: %s\n",
                SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }
    else {
        printf("Unable to load image");
    }

    texture = new_texture;
}

/**
 * @brief Shows the image that was loaded and initialized on the screen
 *
 * @return void.
 */
void Hitbox::draw() {
    SDL_Rect ret = {0, 0, hitbox.w, hitbox.h};

    // This render_quad tells where the image will appear in the screen
    SDL_Rect render_quad = {hitbox.x, hitbox.y, hitbox.w, hitbox.h};

    SDL_RenderCopy(renderer, texture, &ret, &render_quad);
}

/**
 * @brief Help developers to debug the hitboxes.
 *
 * Help developers to debug the hitboxes because it allows you to show all hitboxes.
 *
 * @return if return true, all of hitboxes will be showed on the screen.
 */
bool Hitbox::wanna_draw_hitbox() {
    return false;
}
