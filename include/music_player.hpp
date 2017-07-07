#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/time.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/keyboard_event.hpp"
#include <string>

namespace mindscape {
  class MusicPlayer : public engine::GameObject {

    private:
        int cont = 0;
        bool test = true;
        engine::Time * timer;
        int time = 0;
        int time_aux = 0;
        engine::Game * game;

        int sub_position_x = 0;

    public:
      MusicPlayer(
        std::string name,
        std::pair<int, int> position,
        int priority):engine::GameObject(name, position, priority, {
      {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
      {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
        }){
        timer->init();
        engine::Game& game = engine::Game::get_instance();
      };

      ~MusicPlayer(){};


      void update_state();
      void on_event(GameEvent);
  };
}

#endif
