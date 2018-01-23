/**
 * @file state_map.hpp
 * @brief Purpose: Contain a class to states method's management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef STATE_MAP_H
#define STATE_MAP_H

#include <string>
#include <unordered_map>

namespace engine {

	/**
	 * @brief A StateMap class.
	 *
	 * Define a state of the game or of the characters.
	 */

  	class StateMap {
    	private:
      		std::unordered_map<std::string, std::string> states = {{}};

    	public:
     		StateMap(std::unordered_map<std::string, std::string> p_states = 
     		{{}}
     		):states(p_states){
     		};

      		~StateMap(){
      		};

      		void set_state (std::string, std::string);
      
      		std::string get_state (std::string);
  	};
}

#endif
