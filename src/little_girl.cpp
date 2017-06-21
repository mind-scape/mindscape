#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include <typeinfo>
#include <algorithm>

using namespace engine;

void LittleGirl::on_collision(GameObject* other, Hitbox* p_my_hitbox, Hitbox* p_other_hitbox){
  Platform* p = dynamic_cast<Platform *>(other);
  Hitbox* my_hitbox = dynamic_cast<Hitbox *>(p_my_hitbox);
  Hitbox* other_hitbox = dynamic_cast<Hitbox *>(p_other_hitbox);

  if(get_speed().second >= 0 && p){ //if she is falling on a platform
    set_speed(std::make_pair(get_speed().first, 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 180));

    for(int i = 1000; i > 0; i--){
      std::cout << "COLIDIU" << std::endl;
    }
  }
}

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  Image* moving_left_image = dynamic_cast<Image*>(images[1]);
  Image* moving_right_image = dynamic_cast<Image*>(images[0]);
  Image* stop_girl = dynamic_cast<Image*>(images[2]);

  //speed.first = 0;

std::cout << "Position X: " << get_position().first << " Position Y: " << get_position().second << " Speed X: " << get_speed().first << " Speed Y: " << get_speed().second << std::endl;

  //Verifying if its on the ground
  if(event_name == "JUMP"){ //&& get_speed().second == 0){
    set_speed(std::make_pair(get_speed().first, -16));
  }else if(event_name == "MOVE_LEFT"){
    set_speed(std::make_pair(-1.0, get_speed().second));

    moving_right_image->deactivate();
    stop_girl->deactivate();
    moving_left_image->activate();

    animation_count2 +=1;
    if(animation_count2 == 5){
      moving_left_image->coordinatesOnTexture.first -= 192;
      animation_count2 = 0;
    }
    if(moving_left_image->coordinatesOnTexture.first <= 0)
      moving_left_image->coordinatesOnTexture.first = 1536;
  }else if(event_name == "MOVE_RIGHT"){
    set_speed(std::make_pair(1.0, get_speed().second));

    moving_left_image->deactivate();
    moving_right_image->activate();
    stop_girl->deactivate();

    animation_count +=1;
    if(animation_count == 5){
      moving_right_image->coordinatesOnTexture.first += 192;
      animation_count = 0;
    }

    if(moving_right_image->coordinatesOnTexture.first >= 1728)
      moving_right_image->coordinatesOnTexture.first = 0;
  }
}

void LittleGirl::update_state(){
  //Should be implemented
std::cout << "LITTLE GIRL UPDATE" << std::endl;
}
