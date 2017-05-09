#ifndef TRANSLATOR_H
#define TRANSLATOR_H

namespace engine{

  class Translator {
    Translator();
    ~Translator();

    public:
      static std::list<GameEvent> keyboard_events_to_game_events();
      static std::list<GameEvent> game_events;
  };

}

#endif

