#include "../include/button.hpp"

bool Button::load(){
    for(auto image : images){
      image->load();
    }
    for(auto audio : audios){
      audio->load();
    }
    for(auto text : texts){
      text->load();
    }
  return true;
}

void Button::free(){
  for(auto image : images){
    image->free();
  }
  for(auto audio : audios){
    audio->free();
  }
  for(auto text : texts){
    text->free();
  }
}

/*
void Button::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
}
*/

void Button::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "ENTER"){
    engine::Game* game = &(engine::Game::get_instance());
    game->change_scene("first level");
  }
}

void Button::update(){

}
