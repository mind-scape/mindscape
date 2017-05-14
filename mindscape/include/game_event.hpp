#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <string>

class GameEvent{
    public:
      GameEvent(std::string p_solver,std::string p_game_event_name):solver(p_solver),game_event_name(p_game_event_name){}
      ~GameEvent(){}
      std::string solver;
      std::string game_event_name;
};

#endif

