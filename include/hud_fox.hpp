#ifndef HUD_FOX_H
#define HUD_FOX_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/observable.hpp"
#include "fox.hpp"
#include "game_event.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape{
  class HudFox : public engine::GameObject{
  private:
    void initialize_animations();
    void initialize_audio_effects();
    engine::Animation *create_animation(
      std::string path,
      int sprite_lines,
      int sprite_columns,
      double duration,
      std::string direction
    );

  public:
    HudFox(std::string name, std::pair<int, int> position, int priority);
    ~HudFox(){};

    void notify(engine::Observable*);
  };
}

#endif
