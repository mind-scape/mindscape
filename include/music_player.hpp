#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/time.hpp"
#include "../engine/include/game.hpp"
#include <string>

namespace mindscape {
  class MusicPlayer : public engine::GameObject {
    // public:
    //   typedef enum {
    //     MENU,
    //     INTRODUCTION,
    //     CREDITS,
    //     LEVEL1,
    //     LEVEL2
    //   } SetList;
    private:
        int cont = 0;
        bool test = true;
        engine::Time * timer;
        int time = 0;
        int time_aux = 0;
        engine::Game * game;
        // SetList setlist;
    public:
      MusicPlayer(
        std::string name,
        std::pair<int, int> position,
        int priority):engine::GameObject(name, position, priority, {}){
        timer->init();
        engine::Game& game = engine::Game::get_instance();
      };

      ~MusicPlayer(){};


      void update_state();
  };
}

#endif
