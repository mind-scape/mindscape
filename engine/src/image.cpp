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
#include "log.hpp"

using namespace engine;

/**
 * @brief Method Load
 *
 * Responsible for load the game images and create the texture
 *
 * @return void
 */
bool Image::load() {
    DEBUG("Loading image");
    free();

    SDL_Texture* new_texture = NULL; /**< sdl texture new texture converted */
    SDL_Surface* loaded_surface = IMG_Load(image_path.c_str()); /**< surface loaded to be converted */

    if (loaded_surface != NULL) {
        /* if the loaded surface is null (didnt work properly) */
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

        if (new_texture == NULL) {
			/* if the texture is null */
            WARN("Unable to create texture");
        }
        else {
            /*Do nothing*/
        }

        SDL_FreeSurface(loaded_surface);
    }
    else {
		/* if the surface loaded properly */
        WARN("Unable to load image");
    }

	texture = nullptr;
	texture = new_texture;
	return texture != nullptr;
}

/**
 * @brief Free Method
 *
 * Method responsible for close the game
 *
 * @return void
 */
void Image::free() {
    DEBUG("Trying to free image");
    if (texture != NULL) {
        /* if the texture didnt load properly */
        WARN("Image could not be freed");
        SDL_DestroyTexture(texture);

		texture = nullptr;

		dimension_on_screen.first = 0;
		dimension_on_screen.second = 0;
    }
    else {
        /*Do nothing*/
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
    DEBUG("Drawing image");
    SDL_Rect ret = {coordinatesOnTexture.first,
                    coordinatesOnTexture.second,
                    dimensionOnTexture.first,
                    dimensionOnTexture.second}; /**< rectangle holding the images positions and dimensions */

    // This render_quad tells where the image will appear in the screen
    SDL_Rect render_quad = {x+get_displacement().first,
                            y+get_displacement().second, this->get_width(),
                            this->get_height()}; /**< on screen rendering rectangle */

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
