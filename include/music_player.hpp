#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/time.hpp"
#include <string>

namespace mindscape {
  class MusicPlayer : public engine::GameObject {
    private:
        int cont = 0;
        bool test = true;
        engine::Time * timer;
        int time = 0;
        int time_aux = 0;

    public:
      MusicPlayer(
        std::string name,
        std::pair<int, int> position,
        int priority):engine::GameObject(name, position, priority, {}){timer->init();};

      ~MusicPlayer(){};


      void update_state();
  };
}

#endif
