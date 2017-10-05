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
 * @param p_dimensions is it the pointer that sets the dimensions of hitbox.
 * @return void.
 */
void Hitbox::set_dimensions(std::pair<int, int> p_dimensions) {
    /*
     * Is the dimensions of the hitbox. w = width and h = height.
     * All the dimensions are in pixels.
     */
    hitbox.w = p_dimensions.first;
    hitbox.h = p_dimensions.second;
}

/**
 * @brief Sets the new coordinate of the hitbox after its movement
 *
 * this method calculate the new coordinate of the hitbox based in the its
 * coordinate plus its coordinate of the movement.
 *
 * @param go_coordinates coordinate that the hitbox will go.
 * @param p_displacement coordinate that the hitbox is.
 * @return void.
 */
void Hitbox::set_displacement(std::pair<int, int> go_coordinates,
    std::pair<int, int> p_displacement) {

    /*
     * Hitbox x and y are the coordinates of the hitbox and your movement.
     * All the coordinates are in pixels.
     */
    hitbox.x = p_displacement.first + go_coordinates.first;
    hitbox.y = p_displacement.second + go_coordinates.second;

    /*
     * Set de displacement of the hitbox.
     */
    Component::set_displacement(p_displacement);
}

/**
 * @brief Update the coordinate of the hitbox after its movement
 *
 * this method updates the coordinate of the hitbox based in the its
 * coordinate plus its coordinate of the movement.
 *
 * @param go_coordinates coordinate that the hitbox will go.
 * @return void.
 */
void Hitbox::update(std::pair<int, int> go_coordinates) {

    /*
     * Hitbox x and y are the update coordinates of the hitbox and your movement.
     * All the coordinates are in pixels.
     */
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
 * @param other_hitbox A hitbox object to identify collision between them.
 * @return returns true if the collision was identify.
 */
bool Hitbox::collides_with(Hitbox* other_hitbox) {

    int left_a = 0; /**< int. Coordinate of the hitbox in axis x */
    int right_a = 0; /**< int. Coordinate in axis x and width of the hitbox */
    int top_a = 0; /**< int. Coordinate of the hitbox in axis y */
    int bottom_a = 0; /**< int. Coordinate in axis y and height of the hitbox */

    /*
     * x coordinate and width's dimension of the hitbox a, respectively
     */
    left_a = hitbox.x;
    right_a = hitbox.x + hitbox.w;

    /*
     * y coordinate and height's dimension of the hitbox a, respectively
     */
    top_a = hitbox.y;
    bottom_a = hitbox.y + hitbox.h;

    /**< pair<int, int>. Dimensions of the hitbox. width and height */
    std::pair<int, int> other_hitbox_dimensions (0, 0);

    /**< pair<int, int>. Coordinates on the axis x and y */
    std::pair<int, int> other_hitbox_coordinates (0, 0);

    other_hitbox_coordinates = other_hitbox->get_coordinates();
    other_hitbox_dimensions = other_hitbox->get_dimensions();

    int left_b = 0; /**< int. Coordinate of the hitbox that will collide in axis x */
    int right_b = 0; /**< int. Coordinate in axis x and width of the hitbox*/

    /*
     * x coordinate and width's dimension of the hitbox b, respectively
     */
    left_b = other_hitbox_coordinates.first;
    right_b = other_hitbox_coordinates.first +
            other_hitbox_dimensions.first;

    int top_b = 0; /**< int. Coordinate of the hitbox in axis y */
    int bottom_b = 0; /**< int. Coordinate in axis y and height of the hitbox */

    /*
     * y coordinate and height's dimension of the hitbox b, respectively
     */
    top_b = other_hitbox_coordinates.second;
    bottom_b = other_hitbox_coordinates.second +
             other_hitbox_dimensions.second;

    if (bottom_a <= top_b) {
        /* If the bottom of the hitbox a collides with the top of hitbox b */
        return false;
    }

    if (top_a >= bottom_b) {
        /* If the top of the hitbox a collides with the bottom of hitbox b */
        return false;
    }

    if (right_a <= left_b) {
        /* If the right of the hitbox a collides with the left of hitbox b */
        return false;
    }

    if (left_a >= right_b) {
        /* If the left of the hitbox a collides with the right of hitbox b */
        return false;
    }

    return true;
}

/**
 * @brief Load and show the hitbox on the screen.
 *
 * this method load an image and initialize as a hitbox.
 *
 * @return void.
 */
void Hitbox::initialize() {

    /**<
     * SDL_Surface. Structure that contains a collection of pixels and images of the surface.
     */
    SDL_Surface* loaded_surface = nullptr;
    loaded_surface =
     IMG_Load("../assets/images/scenes/test_scene/Fundo-Vermelho.jpg");

    SDL_Texture* new_texture = nullptr; /**< SDL_Texture. A group of pixels. */

    if (loaded_surface != NULL) {
        /* if the surface image is loaded  */

        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

        if (new_texture == NULL) {
            /* if the texture is null  */

            printf("Unable to create texture from! SDL Error: %s\n",
                SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }
    else {
        /* print if the image surface is not loaded  */

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
    SDL_Rect ret = {0, 0, 0, 0};
    ret = {0, 0, hitbox.w, hitbox.h};

    /**<
     * SDL_Rect. This render_quad tells where the image will appear in the screen.
     */
    SDL_Rect render_quad = {0, 0, 0, 0};
    render_quad = {hitbox.x, hitbox.y, hitbox.w, hitbox.h};

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
