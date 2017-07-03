//TODO descobrir um jeito mais inteligente de adicionar o evento padrão

#include "translator.hpp"

using namespace engine;

bool Translator::is_a_valid_event;

std::list<GameEvent> Translator::keyboard_events_to_game_events(std::list<KeyboardEvent> keyboard_events){  
  std::list<GameEvent> game_events;
  int contador = 0;

  for(auto keyboard_event : keyboard_events){
    
    for(auto game_object : EventHandler::listeners){
      KeyboardEvent::Key key = keyboard_event.key();
      bool key_repeated = keyboard_event.repeated();
      bool key_released = keyboard_event.state();

      //limit LittleGirl attack to one press
      if((game_object->name == "little_girl" && key == 50) && (key_repeated || key_released)){
        continue;
      }

      //if(key == 50){
      //  std::cout << "DEU CERTO E PASSOU AQUI NESSA BAGAÇA" << std::endl;
     // }

  //    if((game_object->name == "little_girl" && key == 50) && !key_repeated && !key_released){
  //      std::cout << "CHEGOUU AKII NESSAA PARADA " << key << std::endl << std::endl << std::endl;
  //    }

      if(game_object->translations[key] != ""){
        auto game_event = GameEvent(
          game_object->name,
          game_object->translations[key],
          keyboard_event.state()
        );
        game_events.push_back(game_event);
      }
    }
  }
  auto default_game_event = GameEvent(
    "All",
    "Update",
    engine::KeyboardEvent::State::PRESSED
  );

  game_events.push_back(default_game_event);
  return game_events;
}
