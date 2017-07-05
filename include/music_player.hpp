#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../engine/include/game_object.hpp"
#include <string>

namespace mindscape {
  class MusicPlayer : public engine::GameObject {
    public:
      MusicPlayer(
        std::string name,
        std::pair<int, int> position,
        int priority):engine::GameObject(name, position, priority, {}){};

      ~MusicPlayer(){};
  };
}

#endif
