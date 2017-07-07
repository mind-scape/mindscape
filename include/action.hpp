#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

namespace mindscape {
  class Action {
    public:
      typedef enum {
        CHANGE_SCENE, PAUSE_GAME, PLAY_GAME
      } Command;
    private:
      Command command;

    public:
      Action(Command p_command):command(p_command){};
      ~Action(){};
      void execute(std::string param);
  };
}

#endif
