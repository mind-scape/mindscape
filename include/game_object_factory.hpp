#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/audio.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/text.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/physics.hpp"
#include "platform.hpp"
#include "little_girl.hpp"
#include "fox.hpp"
#include "scorpion.hpp"
#include "spider.hpp"
#include "background.hpp"
#include "hud_girl.hpp"
#include "hud_fox.hpp"
#include "button.hpp"
#include "select_arrow.hpp"
#include "music_player.hpp"
#include <iostream>
#include <string>

namespace mindscape {
  class GameObjectFactory {
    public:
      typedef enum {
        LITTLE_GIRL, SCORPION, SPIDER, PLATFORM, FOX, BUTTON,
        SELECT_ARROW, BACKGROUND, STAR, HITBOX, IMAGE, HUD_GIRL,
        HUD_FOX, TEXT, ACTION, AUDIO, MUSIC_PLAYER
      } Options;

      GameObjectFactory(){};
      ~GameObjectFactory(){};

      engine::GameObject* fabricate(
        Options option,
        std::string name,
        std::pair<int, int> coordinates = std::make_pair(0,0),
        int priority = 0
      );

      void fabricate_hitbox(engine::GameObject *, std::pair<int, int>,
        std::pair<int, int>);
      void fabricate_image(engine::GameObject *, std::string,
        std::pair<int, int>, int, std::pair<int, int>,
        std::pair<int, int>, std::pair<int, int>);
      void fabricate_text(engine::GameObject *, std::string,
        std::string, int, std::pair<int, int>, int);
      void fabricate_action(engine::GameObject *, int, std::string);
      void fabricate_audio(engine::GameObject *, std::string, int);

    private:
      engine::GameObject* fabricate_button(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_select_arrow(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_fox(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_background(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_platform(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_scorpion(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_spider(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_little_girl(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_hud_fox(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_hud_girl(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_star(std::string, std::pair<int, int>, int);
      engine::GameObject* fabricate_music_player(std::string, std::pair<int, int>, int);
  };
}

#endif
