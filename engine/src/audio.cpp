#include "../include/audio.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace engine;

bool Audio::load(){
    timer->init();
  if(m_audio_type == MUSIC){
    audio_music = Mix_LoadMUS(audio_path.c_str());
    if(!audio_music){
      printf("\nAudio error %s\n", Mix_GetError());
      return false;
    }
  }else if(m_audio_type == CHUNK){
    audio_chunk = Mix_LoadWAV(audio_path.c_str());
    if(!audio_music){
      printf("\nAudio error %s\n", Mix_GetError());
      return false;
    }
  }else{
    printf("\nError loading the audio in this path: %s\n",
      audio_path.c_str()
    );
    return false;
  }
  activate();
  return true;
}

void Audio::free(){
  Mix_FreeMusic(audio_music);
  Mix_FreeChunk(audio_chunk);
  audio_music = NULL;
  audio_chunk = NULL;
}

void Audio::play_effect(){

  time += timer->time_elapsed() - aux_time;
  aux_time = timer->time_elapsed();

  if(time >= effect_duration){
    playing = false;
    time = 0;
  }

  if(!playing){
    time = 0;
    playing = true;
    Mix_PlayChannel(audio_chanel, audio_chunk, audio_repeat);
  }
}

void Audio::play_music(){
  if( Mix_PlayingMusic() == 0 )
    {
      //Play the music
      Mix_PlayMusic(audio_music, -1 );
    }
    if(Mix_PlayingMusic() == 1){
      Mix_ResumeMusic();
    }
}

void Audio::pause_music(){
  if(m_audio_type == MUSIC && Mix_PlayingMusic()){
    Mix_PauseMusic();
  }
}

void Audio::set_repetitions(int repeat){
  audio_repeat = repeat;
}

void Audio::set_duration(float duration){
  effect_duration = duration * 1000;
}
