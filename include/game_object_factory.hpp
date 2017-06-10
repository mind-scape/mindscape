#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/text.hpp"
#include "../engine/include/animation.hpp"
#include "platform.hpp"
#include "little_girl.hpp"
#include "fox.hpp"
#include "background.hpp"
#include "button.hpp"
#include "select_arrow.hpp"
#include <iostream>
#include <string>

namespace mindscape {
  class GameObjectFactory {
    public:
      typedef enum {
        LITTLE_GIRL, FOX, PLATFORM, BUTTON, SELECT_ARROW, BACKGROUND
      } Options;

      GameObjectFactory(){};
      ~GameObjectFactory(){};

      // FIXME: hitbox still being a SDL_Rect, it will not be included here,
      // you need to setup it hardcoded
      engine::GameObject* fabricate(
        Options option,
        std::pair<int, int> coordinates = std::make_pair(0,0),
        int priority = 0
      );

    private:
      engine::GameObject* fabricate_platform();
      engine::GameObject* fabricate_background();
      engine::GameObject* fabricate_button();
      engine::GameObject* fabricate_select_arrow();
      engine::GameObject* fabricate_fox();
      engine::GameObject* fabricate_little_girl();
  };
}

#endif
