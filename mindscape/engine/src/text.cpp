#include "../include/text.hpp"
#include "game.hpp"
#include <string>

using namespace engine;

bool Text::load(){

    text_font = TTF_OpenFont(text_font_path.c_str(), text_font_size);

    SDL_Color color  = {text_color.r, text_color.g,
                                  text_color.b, text_color.a};

    SDL_Color bg_color = {text_background_color.r, text_background_color.g,
                                       text_background_color.b, text_background_color.a};

    SDL_Surface * surface = NULL;

    if(bg_color.a == 0x00){

        surface = TTF_RenderText_Blended(text_font, text_for_view.c_str(), color);

    } else {

        surface = TTF_RenderText_Solid(text_font, text_for_view.c_str(), color);

    }

    if(surface == NULL){
        printf("\nThe text surface cannot be NULL\n");
        return false;
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(!text_texture){
        printf("\nError in the text_texture :%s\n", SDL_GetError());
    }

    if(text_texture == NULL){
        printf("\n The text_texture cannot be NULL\n");
        return false;
    }

    text_weigth = surface->w;
    text_heigth = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

void Text::free(){


    SDL_DestroyTexture(text_texture);
    text_texture = NULL;

    TTF_CloseFont(text_font);
    text_font = NULL;

}

void Text::draw(int posX, int posY){

    SDL_Rect renderQuad = {
        posX,
        posY,
        text_weigth,
        text_heigth
    };

    SDL_RenderCopy(renderer, text_texture, NULL, &renderQuad);


}