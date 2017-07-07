#include "event_handler.hpp"

using namespace engine;

std::list<GameObject *> EventHandler::listeners;

void EventHandler::dispatch_pending_events(unsigned now){
  engine::Game& game = engine::Game::get_instance();
  auto keyboard_events = pending_keyboard_events(now);
  auto game_events = Translator::keyboard_events_to_game_events(keyboard_events);

  for (auto event : game_events){
    for (auto listener : listeners){
      if(listener->name == event.solver || event.solver == "All"){

        if(game.get_state() == Game::PAUSED && (
          event.game_event_name != "CHANGE_SCENE" ||
          event.game_event_name != "PLAY_GAME")){
          listener->on_event(event);
          break;
        }

        listener->on_event(event);

        if(game.get_state() == Game::PAUSED) break;
        listener->update_hitboxes();
        listener->notify_observers();
      }
    }
    if(game.get_state() == Game::PAUSED) break;
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
      Game::get_instance().set_state(Game::QUIT);
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
