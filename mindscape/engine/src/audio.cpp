#include "../include/audio.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace engine;

bool Audio::load(){

    if(audio_type.compare("music") == 0){
            audio_music = Mix_LoadMUS(audio_path.c_str());
            if(!audio_music){
                printf("\nAudio error %s\n", Mix_GetError());
                return false;
            }
    }else if(audio_type.compare("chunk") == 0){
        audio_chunk = Mix_LoadWAV(audio_path.c_str());
            if(!audio_music){
                printf("\nAudio error %s\n", Mix_GetError());
                return false;
            }
        } else{
            printf("\nError loading the audio in this path: %s\n", audio_path.c_str());
            return false;
    }

    return true;
}

void Audio::free(){

    Mix_FreeMusic(audio_music);
    Mix_FreeChunk(audio_chunk);
    audio_music = NULL;
    audio_chunk = NULL;

}

void Audio::draw(int x, int y){

    if(audio_type.compare("music") == 0){
            if( Mix_PlayingMusic() == 0 ){
                 //Play the music
                //-1 argument == endless repetitions
                Mix_PlayMusic(audio_music, -1 );
            }else{
                //If the music is paused
                if( Mix_PausedMusic() == 1 ){
                    //Resume the music
                    Mix_ResumeMusic();
                }else{
                    //Pause the music
                    Mix_PauseMusic();
                }
            }
    }else if(audio_type.compare("chunk") == 0){
            Mix_PlayChannel( audio_chanel, audio_chunk, audio_repeat);
    } else {
            printf("\nError while playing this audio: %s\n", audio_path.c_str());
        }
}
