#include "../include/audio.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace engine;
Audio::Audio(
  std::string p_name,
  std::string path,
  AudioType m_type,
  int repeat,
  int chanel)
  :audio_path(path),
  m_audio_type(m_type),
  audio_repeat(repeat),
  audio_chanel(chanel),
  audio_music(NULL),
  audio_chunk(NULL),
  Component(p_name, std::make_pair(0, 0), true, 1){

}

bool Audio::load(){
    timer->init();
  if(m_audio_type == MUSIC){
    audio_music = Mix_LoadMUS(audio_path.c_str());
    if(!audio_music){
      printf("\nAudio error %s\n", Mix_GetError());
      exit(1);
      return false;
    }
  }else if(m_audio_type == CHUNK){
    audio_chunk = Mix_LoadWAV(audio_path.c_str());
    if(!audio_chunk){
      printf("\nAudio error %s\n", Mix_GetError());
      exit(1);
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
    Mix_VolumeChunk(audio_chunk, volume);
    Mix_PlayChannel(audio_chanel, audio_chunk, audio_repeat);
  }
}

void Audio::draw(int x, int y){
  // if(m_audio_type == MUSIC){
  //   is_active();
  //   if( Mix_PlayingMusic() == 0 )
  //     {
  //       //Play the music
  //       Mix_PlayMusic(audio_music, -1 );
  //     }
  //     if(Mix_PlayingMusic() == 1){
  //       Mix_ResumeMusic();
  //     }
  //   }
}

void Audio::play_music_type(){

  if(audio_music != NULL){
    is_active();
        if( Mix_PlayingMusic() == 0 )
      {
        //Play the music
        Mix_PlayMusic(audio_music, 0 );
      }
      if(Mix_PlayingMusic() == 1){
        Mix_ResumeMusic();
      }
    }
}

void Audio::pause_music(){
  if(m_audio_type == MUSIC && Mix_PlayingMusic()){
    Mix_PauseMusic();
  }
}

void Audio::set_repetitions(int repeat){
  if(audio_music != NULL){
    audio_repeat = repeat;
    //load();
  }
}

void Audio::set_duration(float duration){
  effect_duration = duration * 1000;
}

void Audio::stop_effect(){
  if(audio_chunk != NULL){
    Mix_VolumeChunk(audio_chunk, 0);
  }
}

void Audio::set_effect_volume(int _volume){
  if(_volume > -1 && volume < 129){
    volume = _volume;
  } else {
    std::cout << "\nThe volume must be between 0 and 128" << std::endl;
  }
}

void Audio::set_music_volume(int _volume){
  if(audio_music != NULL){
    if(_volume > -1 && volume < 129){
      Mix_VolumeMusic(_volume);
    } else {
      std::cout << "\nThe volume must be between 0 and 128" << std::endl;
    }
   }
}