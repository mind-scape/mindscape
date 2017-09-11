/**
 * @file text.hpp
 * @brief Purpose: Contains methods to game class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef TEXT_H
#define TEXT_H

#include "SDL2basics.hpp"
#include "component.hpp"
#include "color.hpp"
#include <string>

namespace engine {
	
	/**
	 * @brief A text component class
	 *
	 * A component class specific for handling texts.
	 */
	class Text : public Component {
	private:
		std::string text;
		std::string font_path;
		int font_size;
		Color color;
		Color background_color;
		int weigth;
		int heigth;
		
		SDL_Texture *texture;
		TTF_Font *font;
		SDL_Renderer *renderer;
	
	public:
		/**
     	 * @brief Constructor for Text component
     	 *
     	 * @param p_renderer SDL renderer for writting the text
     	 * @param name Name given for the component
     	 * @param displacement Pair of integers with the displacement
     	 * @param priority Integer representing the priority of rendering
     	 * @param p_text The text to be written
     	 * @param p_font_path The path for the font file
     	 * @param p_font_size Size of the font
     	 * @param p_color RGBA color for the text
     	 * @param p_bg_color RGBA color for the text's background
     	 *
     	 * @return void
     	 */
		Text(
				SDL_Renderer *p_renderer,
				std::string name,
				std::pair<int, int> displacement,
				int priority,
				std::string p_text,
				std::string p_font_path,
				int p_font_size,
				Color p_color = Color(),
				Color p_bg_color = Color(0x00, 0x00, 0x00, 0x00))
				
				: text(p_text),
				  font_path(p_font_path),
				  font_size(p_font_size),
				  color(p_color),
				  background_color(p_bg_color),
				  texture(NULL),
				  font(NULL),
				  renderer(p_renderer),
				  Component(name, displacement, true, priority) {}
		
		~Text() {}
		
		bool load();
		void free();
		void draw(int, int);
		
	};
	
}

#endif
