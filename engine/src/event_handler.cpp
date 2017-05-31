#include "event_handler.hpp"

using namespace engine;

std::list<GameObject *> EventHandler::listeners;

void EventHandler::dispatch_pending_events(unsigned now){
  auto keyboard_events = pending_keyboard_events(now);

  auto game_events = Translator::keyboard_events_to_game_events(keyboard_events);

  
std::cout << "ENTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOU" << game_events.size() << std::endl;

  for (auto event : game_events){
    for (auto listener : listeners){
      if(listener->name == event.solver || event.solver == "All"){
        listener->on_event(event);
      }
    }
  }
}


std::list<KeyboardEvent> EventHandler::pending_keyboard_events(unsigned now){
  get_events_until_now(now);
  auto it = sdl_events.begin();
  std::list<KeyboardEvent> events;
  bool has_events = false;

  while (it != sdl_events.end()){
    unsigned timestamp = it->quit.timestamp;
    if (it->type == SDL_KEYDOWN || it->type == SDL_KEYUP) {
std::cout << "ENTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOU" << std::endl;
      bool repeated = it->key.repeat != 0;
      auto event = KeyboardEvent(timestamp,
        it->type == SDL_KEYUP ?
          KeyboardEvent::State::RELEASED :
          KeyboardEvent::State::PRESSED,
        it->key.keysym.scancode,
        repeated);

      events.push_back(event);
      it = sdl_events.erase(it);
      has_events = true;
    } else
      ++it;
  }

  if(!has_events)
    try_to_get_delayed_keys(events);

std::cout << "ENTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOU" << events.size() << std::endl;

  return events;
}

void EventHandler::try_to_get_delayed_keys(std::list<KeyboardEvent>& events){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  for (auto const& mapped_key : KeyboardEvent::keymap){
    if(state[mapped_key.first]){

      auto event = KeyboardEvent(NULL,
        KeyboardEvent::State::PRESSED,
        mapped_key.first, true
      );

      events.push_back(event);
      break;
    }
  }
    std::cout << "asdfasdfhasdkljfhalsdkjfhklajsdhfkaljh"  << std::endl;
}

void EventHandler::get_events_until_now(unsigned now){
  if (last_update == now)
    return;

  sdl_events.clear();
  SDL_PumpEvents();

  SDL_Event event;

  while (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0){
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
