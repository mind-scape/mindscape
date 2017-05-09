#include "event_handler.hpp"

void EventHandler::dispatch_pending_events(unsigned now){
  auto get_events_until_now(now);

  auto keyboard_events = kernel->pending_keyboard_events(now)  auto game_events = Translator::
  auto game_events = Translator.keyboard_events_to_game_events(keyboard_events);

  game_events.sort();                                                 

  for (auto event : game_events)                                      
  {                                                                   
    for (auto listener : listeners)                                 
      if (listener->on_event(event)){                              
        //break;                     
      }                             
  }

  Translator.game_events.clear();                                                                   
} 

list<KeyboardEvent> EventHandler::pending_keyboard_events(unsigned now) {                             
    update_pending_events(now);                                                 
    auto it = m_events.begin();                                                 
                                                                                
    list<KeyboardEvent> events;   

    while (it != m_events.end())                                                
    {                                                                           
        unsigned timestamp = it->quit.timestamp;                                
                                                                                
        if (it->type == SDL_KEYDOWN) {                                          
            bool repeated = it->key.repeat != 0;                                
            auto event = KeyboardEvent(timestamp,                               
                KeyboardEvent::State::PRESSED,                                  
                it->key.keysym.sym,                                
                key_modifier(it->key.keysym.mod),                               
                repeated);                                                      
                                                                                
                events.push_back(event);                                        
                it = m_events.erase(it);                                        
        } else if (it->type == SDL_KEYUP)                                       
        {                                                                       
            bool repeated = it->key.repeat != 0;                                
            auto event = KeyboardEvent(timestamp,                               
                KeyboardEvent::State::RELEASED,                                 
                it->key.keysym.sym,                                
                key_modifier(it->key.keysym.mod),                               
                repeated);                                                      
                                                                                
                events.push_back(event);                                        
                it = m_events.erase(it);                                        
        } else                                                                  
            ++it;                                                               
    }                                                                           
                                                                                
    return events;                                                              
}

void EventHandler::get_events_until_now(unsigned now)                                    
{                                                                                  
    if (m_last_update == now)                                                      
        return;                                                                    
                                                                                   
    m_events.clear();                                                              
    SDL_PumpEvents();                                                              
                                                                                   
    SDL_Event event;                                                               
                                                                                   
    while (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT,                
        SDL_LASTEVENT) > 0)                                                        
    {                                                                              
        unsigned timestamp = event.quit.timestamp;                                 
                                                                                   
        if (timestamp > now)                                                       
            break;                                                                 
                                                                                   
        SDL_PollEvent(&event);                                                     
        m_events.push_back(event);                                                 
                                                                                   
        SDL_PumpEvents();                                                          
    }                                                                              
                                                                                   
    m_last_update = now;                                                           
} 
