#include "translator.hpp"

using namespace engine;

std::list<GameEvent> Translator::keyboard_events_to_game_events(std::list<KeyboardEvent> keyboard_events){  
  std::list<GameEvent> game_events;
  for(auto keyboard_event : keyboard_events){
    for(auto game_object : EventHandler::listeners){
      unsigned key = keyboard_event.key();
      
      if(game_object->translations[key] != ""){
        auto game_event = GameEvent(game_object->name, game_object->translations[key]);
        game_events.push_back(game_event);
      }
    }
      //Game::get_instance().quit_event = true; 
      //break;
  }
  auto default_game_event = GameEvent("All","Update");
  game_events.push_back(default_game_event);
  return game_events;
}
