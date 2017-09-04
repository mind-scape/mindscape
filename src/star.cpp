#include "../include/star.hpp"
#include "fox.hpp"

using namespace mindscape;

Star::Star(
		std::string name,
		std::pair<int, int> position,
		int priority)
		:engine::GameObject(
		name,
		position,
		priority,
		{
				{engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
				{engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
		}
){
	initialize_hitboxes();
	initialize_animations();
	initialize_audio_effects();
};

void Star::initialize_hitboxes() {
	engine::Game& game = engine::Game::get_instance();
	engine::Hitbox* star_hitbox = new engine::Hitbox(
			"star_hitbox",
			this->get_position(),
			std::make_pair(0, 0),
			std::make_pair(40, 40),
			game.get_renderer()
	);
	add_component(star_hitbox);
}

void Star::initialize_audio_effects() {
	engine::Audio * got_me_audio = new engine::Audio(
			"got_me",
			"../assets/audios/effects_songs/pegando_estrela.wav",
			engine::Audio::CHUNK);
	got_me_audio->set_duration(0.5);
	add_component(got_me_audio);
}

void Star::initialize_animations() {
	engine::Animation* star = create_animation(
			"../assets/images/sprites/items/star/star.png",
			1, 6, 0.9, "LEFT"
	);

	engine::Animation* star_fading = create_animation(
			"../assets/images/sprites/items/star/star_caught.png",
			1, 5, 0.5, "LEFT"
	);

	star_fading->is_a_final_animation = true;
	star_fading->in_loop = false;

	add_animation("star", star);
	add_animation("star_fading", star_fading);
	star->activate();
	set_actual_animation(star);
}

engine::Animation* Star::create_animation(std::string path,
										  int sprite_lines,
										  int sprite_columns,
										  double duration,
										  std::string direction) {

	engine::Game& game = engine::Game::get_instance();
	engine::Animation* animation = new engine::Animation(
			game.get_renderer(),
			path,                 // image path
			false,                // is_active
			std::make_pair(0, 0), // displacement
			1,                    // priority
			sprite_lines,         // sprite_lines
			sprite_columns,       // sprite_columns
			duration,             // duration
			true,                 // in_loop
			direction             // direction
	);

	animation->set_values(
			std::make_pair(40, 40),
			std::make_pair(40, 40),
			std::make_pair(0, 0)
	);

	return animation;
}

void Star::on_event(GameEvent game_event) {
	std::string event_name = game_event.game_event_name;

	if(event_name == "MOVE_LEFT" &&
			!engine::GameObject::on_limit_of_level) {
		set_position_x(get_position_x() + 10);
	}

	else if(event_name == "MOVE_RIGHT" &&
			!engine::GameObject::on_limit_of_level) {
		set_position_x(get_position_x() - 10);
	}
}

void Star::on_collision(engine::GameObject* other, engine::Hitbox* p_my_hitbox,
						engine::Hitbox* p_other_hitbox) {
	//Nothing
}
