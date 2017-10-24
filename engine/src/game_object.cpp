/** 
 * @file game_object.cpp
 * @brief Contains methods to game_object class' management. This methods can control the entire 
 * game object, setting the components, free them, loading and playing audio, animations, components, 
 * setting and displaying hitboxes, detecting and notifing collission with other game objects. 
 * 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "game_object.hpp"
#include "game.hpp"
#include "../include/log.hpp"
#include <algorithm>

using namespace engine;

bool GameObject::on_limit_of_level; /**< Bollean. Determs if game object is in the bound compared to map hitbox */

/**
 * @brief This Routine compare 2 Components of one Game Object and verify with one has more 
 * priority in order to apply game effects.
 * 
 * Because the game have no ideia with game object is more important its important this routine 
 * to know this.
 *  
 * @param Component a, pointer to a component declared in a Game Object.
 * @param Component b, pointer to a component declared in a Game Object.
 * @return The component who have higher priority.
 */
bool compare(Component *a, Component *b) {
	return a->get_priority() < b->get_priority();
}

/**
 * @brief This routine in game context apply components to a any game object declared in game.
 * 
 * It can give multiple functions to a game object, including Audio, Text, Hitbox and Image.
 *  
 * @param Component component pointer to a component declared in a game object.
 * @return void.
 */
void GameObject::add_component(Component *component) {
	if (dynamic_cast<Audio *>(component)) {
	/* Add an audio component to the map of audios of that game object */
		INFO("Adding Audio Component " + component->get_name() + " to " + this->name);
		audios.push_back(component);
	}
	else if (dynamic_cast<Text *>(component)) {
	/* Add an text component to the map of texts of that game object */
		INFO("Adding Text Component " + component->get_name() + " to " + this->name);
		texts.push_back(component);
		sort(texts.begin(), texts.end(), compare);
	}
	else if (dynamic_cast<Hitbox *>(component)) {
	/* Add an hitbox component to the map of hitboxes of that game object */
		INFO("Adding Hitbox Component " + component->get_name() + " to " + this->name);
		hitboxes.push_back(dynamic_cast<Hitbox *>(component));
	}
	else if (dynamic_cast<Image *>(component)) {
	/* Add an image component to the map of images of that game object */
		INFO("Adding Image Component " + component->get_name() + " to " + this->name);
		images.push_back(component);
		sort(images.begin(), images.end(), compare);
	}
}

/**
 * @brief This routine add an animation already created in another part of the code to the Game Object   
 * 
 * Because Animation class contains all the structure to be added to game object its necessary to run this 
 * routine to link the animation class to the Game Object.
 *  
 * @param animation_name string with contains the name of the animation.
 * @param animation pointer to an Animation object.
 * @return void.
 */
void GameObject::add_animation(std::string animation_name, Animation *animation) {
	/* Attach an animation previous created to a game object */
	INFO("Adding animation " + animation->get_name() + " to " + this->name);
	animations[animation_name] = animation;
	animation->set_game_object(this);
}

/**
 * @brief Load all components of the game object rendering animations, audios and text and loading 
 * lopping animations.
 * 
 * Without this routine the game will never change the states, because it plays the musics given to the game object, 
 * the images or animations and texts. 
 *  
 * @return boolean true meaning that everything finishes fine.
 */
bool GameObject::load() {
	INFO("Loading components for " + this->name);

	for (auto image : images) {
		image->load();
	}
	
	for (auto audio : audios) {
		audio->load();
	}
	
	for (auto text : texts) {
		text->load();
	}
	
	for (auto animation : animations) {
		animation.second->load();
	}
	
	return true;
}

/**
 * @brief Free all component of the game game object applied.   
 * 
 * After the use of the component, when the game will be finished this routine will be called to destroy every 
 * component of Game Object to free the computer memory.
 *  
 * @return void.
 */
void GameObject::free() {
	INFO("Freeing " + this->name + " object components");

	for (auto image : images) {
		image->free();
	}
	
	for (auto audio : audios) {
		audio->free();
	}
	
	for (auto text : texts) {
		text->free();
	}
	
	for (auto animation : animations) {
		animation.second->free();
	}
}

/**
 * @brief This routine Draw the components of the game objects in game, includes animations, images, texts and hitboxes    
 * 
 * Before add the component need to be one way to display everything added to screen, this routine randles this. One observation 
 * it that the hitboxes will only be displayed if one one condition is satisfied to not disturb the player interaction. 
 *  
 * @return void.
 */
void GameObject::draw() {
	for (auto audio : audios) {
		audio->draw(position.first, position.second);
	}
	
	for (auto animation : animations) {
		if (animation.second->is_active()) {
		/* Verifys if animation is active and not null, then show on screen */
			animation.second->draw(position.first, position.second);
		}
	}
	
	for (auto image : images) {
		if (image->is_active()) {
		/* Verifys if image(s) is active and not null, then show on screen */
			image->draw(position.first, position.second);
		}
	}
	
	for (auto text : texts) {
		text->draw(position.first, position.second);
	}
	
	for (auto hitbox : hitboxes) {
		if (hitbox->wanna_draw_hitbox()) {
		/* Verifys if hitboxes(s) is active and not null, then show on screen */
			hitbox->draw();
		}
	}
}

/**
 * @brief This routine compare the actual game object to others verifing if it is equals. 
 * 
 * Somewhere in the game in time to decide witch game object to pick this routine will validate if contains another 
 * game objects equals to it.
 *  
 * @param GameObject pointer to an other game object.
 * @return The other game object witch is the same as the actual.
 */
bool GameObject::equals(GameObject *other) {
	return (this == other);
}

/**
 * @brief This routine get all hitboxes related to the game object.
 * 
 * It is important to have this routine because the hitboxes returned will be threated and verified with the hitboxes of others game objects
 * detecting this way collisions between objects in game.
 *  
 * @return The hitboxes of actual game object.
 */
std::vector<Hitbox *> GameObject::get_hitboxes() {
	return hitboxes;
}

/**
 * @brief This routine verifies if the actual game object collides with another game object in game.
 * 
 * Without this routine its imposible to threat collisions between 2 objects in game.
 *  
 * @param GameObject pointer to an other game object.
 * @return void.
 */
void GameObject::collide(GameObject *other) {
	if (!this->equals(other)) {
	/* In case that one game object is diferent from other objects then it will run collisions and verify both objetcs hitboxes */
		this->run_collisions(other);
	}
}

/**
 * @brief This routine run all the collisions of the game object
 * 
 * Without this routine the hiboxes will not be threated.
 *
 * @see GameObject::collide(GameObject *other)
 * @param GameObject pointer to an other game object.
 * @return void.
 */
void GameObject::run_collisions(GameObject *other) {
	for (auto my_hitbox : hitboxes) {
		for (auto other_hitbox : other->get_hitboxes()) {
			/* Get status of hitboxes */
			bool my_hitbox_active = my_hitbox->is_active();
			bool other_hitbox_active = other_hitbox->is_active();
			bool should_hitbox_collide = my_hitbox_active && other_hitbox_active;
			
			if (my_hitbox->collides_with(other_hitbox) && should_hitbox_collide) {
			/* Control Struct that determs if two objects are colliding and call collision function */
				this->on_collision(other, my_hitbox, other_hitbox);
			}
		}
	}
}

/**
 * @brief This routine updated the hitboxes of the game object in game loop.
 * 
 * Every frame of the game this routine tun to apdate hitboxes position.
 *
 * @return void.
 */
void GameObject::update_hitboxes() {
	for (auto hitbox : hitboxes) {
		hitbox->update(position);
	}
}

/**
 * @brief Get the actual game object state in runtime.
 * 
 * Is necessary to have this routine to decide with components will be dispared and what will be updated to make the game faster.
 * If the state is PAUSED the is not necessary to draw objects and the game will be paused.
 *
 * @param state_name, a string that contains the state.
 * @return The state of the object.
 */
std::string GameObject::get_state(std::string state_name) {
	return states.get_state(state_name);
}

/**
 * @brief Get the actual game object position.
 * 
 * Is necessary to have this routine to know where is the game objects in order to run any action.
 *
 * @return The position of the object, witch is a pair that contains X and Y.
 */
std::pair<float, float> GameObject::get_position() {
	return position;
}

/**
 * @brief Get the actual game object position in X grid.
 * 
 * Is necessary to have this routine to know where is the game objects in order to run any action.
 *
 * @see it's a child of GameObject::get_position().
 * @return The X position of the object.
 */
float GameObject::get_position_x() {
	return position.first;
}

/**
 * @brief Get the actual game object position in Y grid.
 * 
 * Is necessary to have this routine to know where is the game objects in order to run any action.
 *
 * @see it's a child of GameObject::get_position().
 * @return The Y position of the object.
 */
float GameObject::get_position_y() {
	return position.second;
}

/**
 * @brief Set the actual game object position in X and Y in one time.
 * 
 * Is necessary to have this routine to set the game object position outside the GameObject class.
 *
 * @param p_position, a pair that contains the game object X and Y position to be set.
 * @return void.
 */
void GameObject::set_position(std::pair<float, float> p_position) {
	position = p_position;
}

/**
 * @brief Set the actual game object position in X.
 * 
 * Is necessary to have this routine to set the game object position outside the GameObject class.
 *
 * @param p_x, a float that contains the game object X position to be set.
 * @return void.
 */
void GameObject::set_position_x(float p_x) {
	position.first = p_x;
}

/**
* @brief Set the actual game object position in Y.
 * 
 * Is necessary to have this routine to set the game object position outside the GameObject class.
 *
 * @param p_y, a float that contains the game object Y position to be set.
 * @return void.
 */
void GameObject::set_position_y(float p_y) {
	position.second = p_y;
}

/**
 * @brief Get the actual game object speed in X and Y in one time.
 * 
 * Is necessary to have this routine to get the game object speed outside the GameObject class and change game physics.
 *
 * @return void.
 */
std::pair<float, float> GameObject::get_speed() {
	return speed;
}

/**
 * @brief Get the actual game object speed in X.
 * 
 * Is necessary to have this routine to get the game object speed outside the GameObject class and change game physics.
 *
 * @return void.
 */
float GameObject::get_speed_x() {
	return speed.first;
}

/**
 * @brief Get the actual game object speed in Y.
 * 
 * Is necessary to have this routine to get the game object speed outside the GameObject class and change game physics.
 *
 * @return void.
 */
float GameObject::get_speed_y() {
	return speed.second;
}

/**
 * @brief Set the actual game object speed in X and Y in one time.
 * 
 * Is necessary to have this routine to set the game object speed outside the GameObject class and change game physics.
 *
 * @param p_position, a pair that contains the game object X and Y speed to be set.
 * @return void.
 */
void GameObject::set_speed(std::pair<float, float> p_speed) {
	speed = p_speed;
}

/**
 * @brief Set the actual game object speed in X.
 * 
 * Is necessary to have this routine to set the game object speed outside the GameObject class and change game physics.
 *
 * @param p_position, a pair that contains the game object X speed to be set.
 * @return void.
 */
void GameObject::set_speed_x(float v_x) {
	speed.first = v_x;
}

/**
 * @brief Set the actual game object speed in Y.
 * 
 * Is necessary to have this routine to set the game object speed outside the GameObject class and change game physics.
 *
 * @param p_position, a pair that contains the game object Y speed to be set.
 * @return void.
 */
void GameObject::set_speed_y(float v_y) {
	speed.second = v_y;
}

/**
 * @brief Set the actual animation to game object.
 * 
 * Is necessary to have this routine to set what animation will be played during the game for each game object. It verifys 
 * if the current animation is not NULL to be deactivate, and then runs the next animation passed as param.
 *
 * @param animation pointer to an Animation object.
 * @return void.
 */
void GameObject::set_actual_animation(Animation *animation) {
	INFO("Changing " + this->name + " animation to " + animation->get_name());
	if (actual_animation != NULL) {
	/* Validation to determs if current animation is not null*/
		actual_animation->deactivate();
	}
	
	/* Get reference to current animation and active it */
	actual_animation = animation;
	actual_animation->activate();
}

/**
 * @brief Get the actual animation to game object.
 * 
 * Is necessary to have this routine to get what animation is playing during the game runtime for each game object.
 *
 * @param animation pointer to an Animation object.
 * @return The actual animation of the game object.
 */
Animation *GameObject::get_actual_animation() {
	return actual_animation;
}

/**
 * @brief Control the game object state setting to activate.
 * 
 * Is necessary to have this routine to set what game object will be activated or not. And this state can determ if this 
 * game object will be renderer and/or apply physics.
 *
 * @return void.
 */
void GameObject::activate() {
	active = true;
}

/**
 * @brief Control the game object state setting to deactivate.
 * 
 * Is necessary to have this routine to set what game object will be activated or not. And this state can determ if this 
 * game object will be renderer and/or apply physics.
 *
 * @return void.
 */
void GameObject::deactivate() {
	active = false;
}

/**
 * @brief Control the game object component deactivating all of them.
 * 
 * Is necessary to have this routine to deactivate all game object components.
 *
 * @return void.
 */
void GameObject::deactivate_components() {
	INFO("Deactivating " + this->name + " components");

	for (auto image : images) {
		image->deactivate();
	}
	
	for (auto audio : audios) {
		audio->deactivate();
	}
	
	for (auto text : texts) {
		text->deactivate();
	}
	
	for (auto hitbox : hitboxes) {
		hitbox->deactivate();
	}
}

/**
 * @brief Verifys if the current game object is active
 * 
 * Is necessary to have this routine know the current state of the game object changing it state of just free from game.
 *
 * @return true of false depending of it state.
 */
bool GameObject::is_active() {
	return active;
}

void GameObject::update_state() {
}

/**
 * @brief Create the hitbox for the current game object and add it as component.
 * 
 * Is necessary to have this routine because the hitbox can detern the limits of the game objets and when it collides to 
 * another game object.
 * 
 * @param displacement pair that contais an ancor point to start placing the hitbox.
 * @param dimensions pair that contains the dimensions of the hitbox.
 * @return void.
 */
void GameObject::create_hitbox(
		std::pair<int, int> displacement,
		std::pair<int, int> dimensions) {
	INFO("Creating hitbox for " + this->name);

	Game &game = Game::get_instance();
	/* Instantiate objects calling contrutor and passsing params */
	Hitbox *hitbox = new Hitbox("hitbox",
	                            this->get_position(), 
	                            displacement, 
	                            dimensions, 
	                            game.get_renderer());
	
	add_component(hitbox);
}

/**
 * @brief Attach observer.
 * 
 * Is necessary to have this routine to attach the observer withou having to acessing from outside the Game Object class.
 * 
 * @param pointer to Observer that contais the reference to object.
 * @return void.
 */
void GameObject::attach_observer(Observer *observer) {
	INFO("Attaching observer to " + this->name);
	observers.push_back(observer);
}

/**
 * @brief Detach observer.
 * 
 * Is necessary to have this routine to detach the observer withou having to acessing from outside the Game Object class.
 * 
 * @param pointer to Observer that contais the reference to object.
 * @return void.
 */
void GameObject::detach_observer(Observer *observer) {
	INFO("Releasing observer from " + this->name);
	observers.remove(observer);
}

/**
 * @brief Attach observer.
 * 
 * Is necessary to have this routine to notify the observers withou having to acessing from outside the Game Object class.
 * 
 * @param pointer to Observer that contais the reference to object.
 * @return void.
 */
void GameObject::notify_observers() {
	for (auto observer : observers) {
		observer->notify(this);
	}
}

/**
 * @brief Get the audio component of current game object by name.
 * 
 * Is necessary to have this routine to search and verify an audio inside any game object.
 * 
 * @param displacement pair that contais an ancor point to start placing the hitbox.
 * @return Address of object called matched audio containing the game object audio.
 */
Audio *GameObject::get_audio_by_name(std::string audio_name) {
	INFO("Getting audio " + audio_name + " in " + this->name);

	Audio *matched_audio = NULL;
	
	for (auto audio : audios) {
		if (audio->get_name() == audio_name) {
		/* Case audio(s) from game object is equal to audio name passed as param in function */
			matched_audio = dynamic_cast<Audio *>(audio);
			break;
		}
	}
	
	return matched_audio;
}

/**
 * @brief Play game object song, it can be music or sound effect.
 * 
 * Is necessary to have this routine to use play sound directly from the game object without nedding to access the Audio class.
 * 
 * @warning If the game object do not have the song to be played, it will return NULL when the routine try to get the audio.
 * @see Audio()
 * @param string with the song name to be played .
 * @return void.
 */
void GameObject::play_song(std::string song_name) {
	INFO("Playing song " + song_name + " in " + this->name);

	/* Instantiate object song */
	Audio *song = get_audio_by_name(song_name);
	
	/* Play songs. If is a music it will be played in play_music_type, case is a audio effect in play_effect */
	song->play_music_type();
	song->play_effect();
}

/**
 * @brief Stop game object song, it can be music or sound effect.
 * 
 * Is necessary to have this routine to use stop sound directly from the game object without needing to access the Audio class.
 * 
 * @warning If the game object do not have the song to be stopped, it will return NULL when the routine try to get the audio.
 * @see Audio()
 * @param string with the song name to be stopped .
 * @return void.
 */
void GameObject::stop_song(std::string song_name) {
	INFO("Stoping song " + song_name + " in " + this->name);

	Audio *song = get_audio_by_name(song_name);
	
	/* Stop songs. If is a music it will be stopped in pause_music, case is a audio effect in stop_effect */
	song->stop_effect();
	song->pause_music();
}

/**
 * @brief Set game object song repetitions.This repetition can have a number or can be played forever if set to -1.
 * 
 * Is necessary to have this routine to controll sound repetitions directly from the game object without needing to access the Audio class.
 * 
 * 
 * @warning If the game object do not have the song to be repeted, it will return NULL when the routine try to get the audio.
 * @see Audio()
 * @param string with the song name to be set the repetitions.
 * @param int with the number of repetitions to be set.
 * @return void.
 */
void GameObject::set_repetitions(std::string song_name, int repet) {
	/* Instantiate object song  and set number of repetitions */
	Audio *song = get_audio_by_name(song_name);
	song->set_repetitions(repet);
}

/**
 * @brief Set game object song volume.This volume have a range 0 to 100.
 * 
 * Is necessary to have this routine to use set sound volume directly from the game object without needing to access the Audio class.
 * 
 * @warning If the game object do not have the song to be set the volume, it will return NULL when the routine try to get the audio.
 * @see Audio()
 * @param string with the song name to be set volume.
 * @param int with the volume number.
 * @return void.
 */
void GameObject::set_music_volume(std::string song_name, int vol) {
	INFO("Setting " + song_name + " volume in " + this->name);

	/* Instantiate object song  and set volume */
	Audio *song = get_audio_by_name(song_name);
	song->set_music_volume(vol);
};

/**
 * @brief Set game object song volume.This volume have a range 0 to 100.
 * 
 * Is necessary to have this routine to use free sound directly from the game object without needing to access the Audio class.
 * 
 * @warning If the game object do not have the song to be free, it will return NULL when the routine try to get the audio.
 * @see Audio()
 * @param string with the song name to be set free.
 * @return void.
 */
void GameObject::free_music(std::string song_name) {
	INFO("Freeing " + song_name + " in " + this->name);

	/* Instantiate object song  and delete it. Normaly this will be called in game close operation */
	Audio *song = get_audio_by_name(song_name);
	song->free();
};