#include "../include/music_player.hpp"
#include "../include/little_girl.hpp"
#include "../engine/include/audio.hpp"
#include <stdlib.h>

using namespace mindscape;

void MusicPlayer::update_state(){
  engine::Audio * intro_song = dynamic_cast<engine::Audio *>(audios[0]);
  engine::Audio * loop_song = dynamic_cast<engine::Audio *>(audios[1]);
  engine::Audio * intro_palhaco = dynamic_cast<engine::Audio *>(audios[2]);
  engine::Audio * loop_palhaco = dynamic_cast<engine::Audio *>(audios[3]);

    time += timer->time_elapsed() - time_aux;
    time_aux = timer->time_elapsed();

    intro_song->set_music_volume(30);
    loop_song->set_music_volume(30);
    if(time < 25850){
        intro_song->play_music_type();
    } else {
        intro_song->free();
        loop_song->play_music_type();
    }



    // if(cont > 500){
    //     std::cout << "\n contador : " << cont << std::endl;
    //     intro_song->free();
    //     loop_song->play_music_type();
    // }

}