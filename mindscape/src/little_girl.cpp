#include "../include/little_girl.hpp"

using namespace engine;

bool LittleGirl::load(){
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

void LittleGirl::free(){
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
void LittleGirl::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
}
*/

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;
  if(event_name == "JUMP"){
     
  }else if(event_name == "CROUCH"){
      
  }else if(event_name == "MOVE_LEFT"){
/*
    if(ret.y == 0) ret.y = 140;                                              
    ret.x -= 108;                                                            
    if(ret.x < 0) ret.x = 756;                                               
    right_cont = 0;                                                          

    pos.first -= 20;                                                         
    if(pos.first < 0) pos.first = 700; 
*/
  }else if(event_name == "MOVE_RIGHT"){
/*
    if(ret.y == 140) ret.y = 0;                                           
    ret.x+=108;                                                           
    if(ret.x == 864) ret.x = 0;                                           
    left_cont = 0;                                                        

    pos.first += 20;                                                      
    if(pos.first > 700) pos.first = 0;
  */
  }        
}

void LittleGirl::update(){
  
}

