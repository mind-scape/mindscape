#include "event_handler.hpp"

using namespace engine;

std::list<GameObject *> EventHandler::listeners;

void EventHandler::dispatch_pending_events(unsigned now){
  auto get_events_until_now(now);

  auto keyboard_events = pending_keyboard_events(now);
  std::cout << "Keyboard Events number " << keyboard_events.size() << std::endl;

  auto game_events = Translator::keyboard_events_to_game_events(keyboard_events);
  
  std::cout << "Game Events number " << game_events.size() << std::endl;

  for (auto event : game_events){
    for (auto listener : listeners){
      if(listener->name == event.solver){
        //listener->on_event(event);                              
      }
    }
  }

} 

std::list<KeyboardEvent> EventHandler::pending_keyboard_events(unsigned now){
  get_events_until_now(now);                                                 
  auto it = sdl_events.begin();   

  std::list<KeyboardEvent> events; 

  while (it != sdl_events.end())                                                
  {                                                                           
    unsigned timestamp = it->quit.timestamp;                                

    if (it->type == SDL_KEYDOWN) {                                          
      bool repeated = it->key.repeat != 0;                                
      auto event = KeyboardEvent(timestamp,                               
          KeyboardEvent::State::PRESSED,                                  
          it->key.keysym.sym,                                
          repeated);                                                      

      events.push_back(event);                                        
      it = sdl_events.erase(it);                                        
    } else if (it->type == SDL_KEYUP)                                       
    {                                                                       
      bool repeated = it->key.repeat != 0;                                
      auto event = KeyboardEvent(timestamp,                               
          KeyboardEvent::State::RELEASED,                                 
          it->key.keysym.sym,                                
          repeated);                                                      

      events.push_back(event);                                        
      it = sdl_events.erase(it);                                        
    } else                                                                  
      ++it;                                                               
  }                                                                           

  return events;                                                              
}

void EventHandler::get_events_until_now(unsigned now){                                                                                  
  if (last_update == now)                                                      
    return;                                                                    

  sdl_events.clear();                                                              
  SDL_PumpEvents();                                                              

  SDL_Event event;                                                               

  while (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT,                
        SDL_LASTEVENT) > 0)                                                        
  {                                                                              
    unsigned timestamp = event.quit.timestamp;                                 

    if (timestamp > now)                                                       
      break;                                                                 

    SDL_PollEvent(&event); 

    if(event.type == SDL_QUIT){
      Game::get_instance().quit_event = true;
      break;
    }
                                                    
    sdl_events.push_back(event);

    SDL_PumpEvents();                                                          
  }                                                                              

  last_update = now;                                                           
}

void EventHandler::add_listener(GameObject * listener){
  if(listener != NULL) listeners.push_back(listener);
}

void EventHandler::remove_listener(GameObject * listener){
  if(listener != NULL) listeners.remove(listener);
}
