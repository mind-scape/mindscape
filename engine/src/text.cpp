/**
 * @file text.cpp
 * @brief Purpose: Contains methods to game class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/text.hpp"
#include "../include/log.hpp"

using namespace engine;

/**
 * @brief Loads text
 *
 * Loads the text and get it ready to be displayed on the screen
 *
 * @return void
 */
bool Text::load() {
	font = TTF_OpenFont(font_path.c_str(), font_size);
	
	SDL_Color sdl_color = {
			color.r,
			color.g,
			color.b,
			color.a
	};
	
	SDL_Color bg_color = {
			background_color.r,
			background_color.g,
			background_color.b,
			background_color.a
	};
	
	SDL_Surface *surface = NULL;
	
	if (bg_color.a == 0x00) {
		surface = TTF_RenderText_Blended(
				font,
				text.c_str(),
				sdl_color
		);
	} 
	
	else {
		surface = TTF_RenderText_Solid(font, text.c_str(), sdl_color);
	}
	
	if (surface == NULL) {
		ERROR("The text surface cannot be NULL");
		return false;
	}
<<<<<<< HEAD
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	if (!texture) {
		ERROR(("\nError in the text_texture :%s\n", SDL_GetError()));

	}
	
	if (texture == NULL) {
		ERROR("The text_texture cannot be NULL");
		return false;
=======
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		if (!texture) {
			printf("\nError in the text_texture :%s\n", SDL_GetError());
		}

		else {
			/*Do nothing*/
		}
		
		if (texture == NULL) {
			printf("\n The text_texture cannot be NULL\n");
			return false;
		}

		else {

			weigth = surface->w;
			heigth = surface->h;
			
			activate();
			SDL_FreeSurface(surface);
			
			return true;

		}
>>>>>>> 602adcf3ad92662791c86d607f46f0b8e82b3119
	}
	
}

/**
 * @brief Frees the text
 *
 * Frees the text from the memory
 *
 * @return void
 */
void Text::free() {
	DEBUG("Freeing text");
	SDL_DestroyTexture(texture);
	texture = NULL;
	
	TTF_CloseFont(font);
	font = NULL;
}

/**
 * @brief Draws the text
 *
 * Draws the thexo to the screen
 *
 * @param x X position for the text
 * @param y Y position for the text
 */
void Text::draw(int x, int y) {
	DEBUG("Drawing text");
	SDL_Rect renderQuad = {x + get_displacement().first,
						   y + get_displacement().second,
						   weigth,
						   heigth};
	
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
