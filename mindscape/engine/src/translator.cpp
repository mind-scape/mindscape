#include "translator.hpp"

using namespace engine;

std::list<GameEvent> Translator::keyboard_events_to_game_events(std::list<KeyboardEvent> keyboard_events){
  for(auto keyboard_event : keyboard_events){
    for(auto game_object : EventHandler::listeners){
      unsigned key = keyboard_event.key();
      if(game_object->translations[key] != ""){
        auto game_event = GameEvent(game_object->name, game_object->translations[key]);
        game_events.push_back(game_event);
      }
    }
  }
}
