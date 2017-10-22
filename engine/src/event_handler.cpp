#include <include/log.hpp>
#include "event_handler.hpp"

using namespace engine;

std::list<GameObject *> EventHandler::listeners; /**< objects listening for events triggers */

void EventHandler::dispatch_pending_events(unsigned now) {
	INFO("Dispatching pending events");

	engine::Game& game = engine::Game::get_instance(); /**< singleton game's instance */
	auto keyboard_events = pending_keyboard_events(now); /**< keyboard events that were not processed yet */
	auto game_events = Translator::keyboard_events_to_game_events(keyboard_events); /**< game events created from keyboard events */

	INFO("Looping all events");
	for (auto event : game_events) {
		/* loops all events in the translated game events */
		for (auto listener : listeners) {
			/* loops all listeners inside each event */
			if(listener->name == event.solver || event.solver == "All") {
				/* if the listener name is the event solver or the solver is everyone */
				if(game.get_state() == Game::PAUSED && (
						event.game_event_name != "CHANGE_SCENE" ||
						event.game_event_name != "PLAY_GAME")){
					listener->on_event(event);
					/* if the game state is paused it breaks the loop */
					break;
				}

				listener->on_event(event);

				if(game.get_state() == Game::PAUSED) {
					/* breaks the loop if the game state is paused */
					break;
				}
				listener->update_hitboxes();
				listener->notify_observers();
			}
		}
		if(game.get_state() == Game::PAUSED) {
			/* breaks the loop if the game state is paused */
			INFO("Game Paused");
			break;
		}
	}
}

std::list<KeyboardEvent> EventHandler::pending_keyboard_events(unsigned now) {
	INFO("Getting all pending keyboard events");

	get_events_until_now(now);
	auto it = sdl_events.begin();
	std::list<KeyboardEvent> events; /* list of keyboard events */
	bool has_events = false; /* if has events to be processed */

	while (it != sdl_events.end()) {
		/* loops while all the events were not processed */
		unsigned timestamp = it->quit.timestamp;
		if (it->type == SDL_KEYDOWN || it->type == SDL_KEYUP) {
			/* if the type of the event is a key down or key up */
			bool repeated = it->key.repeat != 0; /**< if the event is repeated by the same keys */
			auto event = KeyboardEvent(timestamp,
									   it->type == SDL_KEYUP ?
									   KeyboardEvent::State::RELEASED :
									   KeyboardEvent::State::PRESSED,
									   it->key.keysym.scancode,
									   repeated);

			events.push_back(event);
			it = sdl_events.erase(it);
			has_events = true; /**< make variable responsible for checking if has events to be processed true */
		}

		else
			/* increments the iterator */
			++it;
	}

	if(!has_events) {
		/* if has events to be processed */
		try_to_get_delayed_keys(events);
	}

	return events;
}

void EventHandler::try_to_get_delayed_keys(std::list<KeyboardEvent>& events) {
	INFO("Pump for getting delayed events");

	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL); /**< states of the keys of the keyboard */

	for (auto const& mapped_key : KeyboardEvent::keymap) {
		/* iterates all maped keys in the keymap */
		if(state[mapped_key.first]) {
			/**< if there is the mapped key first on the state map */
			auto event = KeyboardEvent(-1,
									   KeyboardEvent::State::PRESSED,
									   mapped_key.first, true
			);
			events.push_back(event);
			break;
		}
	}
}

void EventHandler::get_events_until_now(unsigned now) {
	INFO("Getting all events happened until now");

	if (last_update == now) {
		/* returns if the last update is equals to now */
		return;
	}

	sdl_events.clear();
	SDL_PumpEvents();

	SDL_Event event;

	while (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0) {
		/**< loops while the number of events is greater than 0 */
		unsigned timestamp = event.quit.timestamp; /**< time of quit form the event */

		if (timestamp > now) {
			/* if the timestamp is after now */
			break;
		}

		SDL_PollEvent(&event);

		if(event.type == SDL_QUIT) {
			/* if the event type is a SDL QUIT */
			Game::get_instance().set_state(Game::QUIT);
			break;
		}

		sdl_events.push_back(event);
		SDL_PumpEvents();
	}

	last_update = now;
}

void EventHandler::add_listener(GameObject * listener) {
	INFO("Adding " + listener->name + " as listener");

	if(listener != NULL) {
		/* if the listener is null (no listeners registered) */
		listeners.push_back(listener);
	}
}

void EventHandler::remove_listener(GameObject * listener) {
	INFO("Removing " + listener->name + " from listeners");

	if(listener != NULL) {
		/* if the listener is not null (not empty) */
		listeners.remove(listener);
	}
}
