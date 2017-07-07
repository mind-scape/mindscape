#include "../include/music_player.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/audio.hpp"
#include <stdlib.h>

using namespace mindscape;

void MusicPlayer::update_state(){

   if(get_audio_by_name("music_menu")){
        play_song("music_menu");
    }else if(get_audio_by_name("intro_level_1")){
        time += timer->time_elapsed() - time_aux;
        time_aux = timer->time_elapsed();

        set_music_volume("intro_level_1",30);
        set_music_volume("loop_level_1",30);
        if(time < 25850){
            play_song("intro_level_1");
        } else {
            free_music("intro_level_1");
            play_song("loop_level_1");
        }

    }

}