#ifndef LEVEL_FACTORY_H
#define LEVEL_FACTORY_H

#include "game_object_factory.hpp"
#include "../engine/include/level.hpp"
#include "../engine/include/game_object.hpp"
#include <string>

namespace mindscape {
  class LevelFactory {
    public:
      LevelFactory(){};
      ~LevelFactory(){};

      void update_level(engine::Level *, std::string);
      std::vector<engine::GameObject *> execute_dat(engine::Level *, std::string);
      engine::Level * fabricate_level(std::string);
      engine::Level * fabricate_menu();
      engine::Level * fabricate_game_over();
  };
}

#endif
