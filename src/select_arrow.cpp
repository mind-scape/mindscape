#include "select_arrow.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "../engine/include/audio.hpp"
#include "level_factory.hpp"

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
  engine::Text* sel = new engine::Text(game.get_renderer(), "selector", std::make_pair(0,0), 5, ">", "/opt/mindscape/assets/fonts/FFF_Tusj.ttf", 35);
  sel->activate();
  add_component(sel);
  timer->init();

  action = new Action(Action::Command::CHANGE_SCENE);


}

void SelectArrow::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;
  time += timer->time_elapsed() -  time_aux;
  time_aux = timer->time_elapsed();

  if(enable){
    if(event_name == "DOWN"){
      enable = false;
      next_time = time + 200;
      if(arrow_seletor >= 0 && arrow_seletor < 3){
        arrow_seletor += 1;
      } else {
        arrow_seletor = 0;
      }
    }

    if(event_name == "UP"){
      enable = false;
      next_time = time + 200;
      if(arrow_seletor <= 3 && arrow_seletor > 0){
        arrow_seletor -= 1;
      } else {
        arrow_seletor = 3;
      }
    }
   }

   if(enable == false){
      if(time > next_time){
        enable = true;
        time = 0;
      }
   }


  switch(arrow_seletor){
    //INICIAR
    case(0):
      set_position(std::make_pair(get_position().first, 175));
      if(event_name == "ENTER"){
        action->execute("/opt/mindscape/data/1.level.dat");
      }
      break;
    //INSTRUÇÕES
    case(1):
      set_position(std::make_pair(get_position().first, 227));
      if(event_name == "ENTER"){
        action->execute("/opt/mindscape/data/2.level.dat");
      }
      break;
    //CRÉDITOS
    case(2):
      set_position(std::make_pair(get_position().first, 280));
      if(event_name == "ENTER"){
        action->execute("/opt/mindscape/data/credits_scene.dat");
      }
      break;
    //SAIR
    case(3):
      set_position(std::make_pair(get_position().first, 335));
      if(event_name == "ENTER"){

      }
      break;
    default:
      break;
  }

}

void SelectArrow::update_state(){

}
