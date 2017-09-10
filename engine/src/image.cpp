/**
 * @file image.cpp
 *
 * @brief Purpose: Contains methods to images management
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "image.hpp"
#include <string>

using namespace engine;

/**
 * @brief Method Load
 *
 * Responsible for load the game images and create the texture
 *
 * @return void
 */
bool Image::load() {

    free();

    SDL_Texture* new_texture = NULL;

    SDL_Surface* loaded_surface = IMG_Load(image_path.c_str());

    if (loaded_surface != NULL) {
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

        if (new_texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   image_path.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }
    else {
        printf("Unable to load image %s! Image error: %s\n",
               image_path.c_str(), IMG_GetError());
    }

    texture = new_texture;
    return texture != NULL;
}

/**
 * @brief Free Method
 *
 * Method responsible for close the game
 *
 * @return void
 */
void Image::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);

        texture = NULL;

        dimension_on_screen.first = 0;
        dimension_on_screen.second = 0;
    }
}

/**
 * @brief Draw
 *
 * Draw the image on the screen
 *
 * @param x position in axis x on the screen
 * @param y position in axis y on the screen
 *
 * @return
 */
void Image::draw(int x, int y) {
    SDL_Rect ret = {coordinatesOnTexture.first,
                    coordinatesOnTexture.second,
                    dimensionOnTexture.first,
                    dimensionOnTexture.second};

    // This render_quad tells where the image will appear in the screen
    SDL_Rect render_quad = {x+get_displacement().first,
                            y+get_displacement().second, this->get_width(),
                            this->get_height()};

    SDL_RenderCopy(renderer, texture, &ret, &render_quad);
}

/**
 * @brief Methods Set values
 *
 * Set the position and dimension of the texture on the screen
 *
 * @param _dimension_on_screen size in the screen of the texture
 * @param _dimension_on_texture size of the texture
 * @param _coordinates_on_texture coordinates in axis x,y
 */
void Image::set_values(std::pair<int, int> _dimension_on_screen,
                       std::pair<int, int> _dimension_on_texture,
                       std::pair<int, int> _coordinates_on_texture) {

    dimension_on_screen = _dimension_on_screen;
    dimensionOnTexture = _dimension_on_texture;
    coordinatesOnTexture = _coordinates_on_texture;
}

/**
 * @brief Get Width
 *
 * @return width dimension
 */
int Image::get_width() {
    return dimension_on_screen.first;
}

/**
 * @brief Get Height
 *
 * @return the height dimension
 */
int Image::get_height() {
    return dimension_on_screen.second;

}
