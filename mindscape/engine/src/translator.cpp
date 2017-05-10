//TODO LUAN think about how to acesss 'active_game_objects' variable, that is being used bellow.

#include "translator.hpp"

using namespace engine;

std::list<GameEvent> Translator::keyboard_events_to_game_events(std::list<KeyboarEvents> keyboard_events){
  for(auto keyboard_event : keyboard_events){
    for(auto game_object : active_game_objects){
      unsigned key = keyboard_event.key();
      if(game_object.translations[key]){
        auto game_event = GameEvent(game_object.name, game_object.translations[key]);
        game_events.push_back(game_event);
      }
    }
  }
}
