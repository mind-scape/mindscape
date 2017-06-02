#ifndef STATE_MAP_H
#define STATE_MAP_H

#include <string>
#include <unordered_map>

namespace engine {
  class StateMap{
    private:
      std::unordered_map<std::string, std::string> states;

    public:
      StateMap(std::unordered_map<std::string, std::string> p_states = {{}}):states(p_states){};

      ~StateMap(){};

      void set_state (std::string, std::string);
      std::string get_state (std::string);
  };
}

#endif
