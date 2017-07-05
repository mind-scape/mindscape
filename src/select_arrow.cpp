#include "select_arrow.hpp"
#include "../engine/include/game.hpp"

using namespace mindscape;

SelectArrow::SelectArrow(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :engine::GameObject(
    name,
    position,
    priority,
    {
      {engine::KeyboardEvent::UP,"UP"},
      {engine::KeyboardEvent::DOWN,"DOWN"},
      {engine::KeyboardEvent::RETURN,"ENTER"}
    }){

  initialize_arrow();
};

void SelectArrow::initialize_arrow(){
  engine::Game game = engine::Game::get_instance();
  engine::Text* sel = new engine::Text(game.get_renderer(), "selector", std::make_pair(0,0), 5, ">", "../assets/fonts/FFF_Tusj.ttf", 35);
  sel->activate();
  add_component(sel);
}

void SelectArrow::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "UP"){
    if(arrow_seletor >= 0 && arrow_seletor < 6){
      arrow_seletor += 1;
    } else {
      arrow_seletor = 0;
    }
  }

  if(event_name == "DOWN"){
    if(arrow_seletor <= 6 && arrow_seletor > 0){
      arrow_seletor -= 1;
    } else {
      arrow_seletor = 6;
    }
  }

  switch(arrow_seletor){
    case(0):
      set_position(std::make_pair(get_position().first, 275));
      if(event_name == "ENTER"){
        enter_handler = true;
        option_select = 'i';
        std::cout << option_select << std::endl;
        enter_handler = false;
      }
      break;
    case(2):
      set_position(std::make_pair(get_position().first, 310));
      if(event_name == "ENTER"){
        enter_handler = true;
        option_select = 'a';
        std::cout << option_select << std::endl;
        enter_handler = false;
      }
      break;
    case(4):
      set_position(std::make_pair(get_position().first, 345));
      if(event_name == "ENTER"){
        enter_handler = true;
        option_select = 'c';
        std::cout << option_select << std::endl;
        enter_handler = false;
      }
      break;
    case(6):
      set_position(std::make_pair(get_position().first, 380));
      if(event_name == "ENTER"){
        enter_handler = true;
        option_select = 's';
        std::cout << option_select << std::endl;
        enter_handler = false;
      }
      break;
    default:
      break;
  }

}
