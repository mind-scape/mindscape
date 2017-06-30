#include "../include/platform.hpp"
#include "../engine/include/game.hpp"

using namespace mindscape;

Platform::Platform(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :engine::GameObject(name, position, priority,
      {{engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
      {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"}}
  ){
    initialize_image();
};

void Platform::initialize_image(){
  engine::Game& game = engine::Game::get_instance();
  engine::Image* platform_image = new engine::Image(
    game.get_renderer(),
    "../assets/images/scenes/test_scene/plataforma.png",
    true, std::make_pair(0,0), 1
  );

  platform_image-> set_values(
    std::make_pair(507, 256),
    std::make_pair(507, 256),
    std::make_pair(0, 0)
  );

  add_component(platform_image);
}

void Platform::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() + 10);
  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){
    set_position_x(get_position_x() - 10);
  }
}
