#include <cmath>
#include <algorithm>    // std::reverse
#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;


Animation::Animation(
  std::string name,
  std::string path,
  std::pair<int, int> displacement,
  double p_duration_of_animation,
  std::pair<int, int> sprite_sheet_size,
  std::pair<int, int> sprite_size,
  Direction p_direction,
  int priority)
  :Component(name, displacement, false, priority){
  direction = p_direction;
  initialize_images(path, sprite_sheet_size, sprite_size);
}

void Animation::initialize_images( std::string path,
  std::pair<int, int> sprite_sheet_size, std::pair<int, int> sprite_size){

  engine::Game& game = engine::Game::get_instance();
  int number_of_sprites = sprite_sheet_size.first/sprite_size.first;
  
  for(int sprite_step = 0; sprite_step < number_of_sprites; sprite_step++){
    engine::Image* image = new engine::Image(
      game.get_renderer(), path, true, get_displacement(), get_priority()
    );

    image-> set_values(
      sprite_size,
      sprite_size, //works only for a single line
      std::make_pair(sprite_size.first * sprite_step, 0)
    );

    images.push_back(image);
  }

  setup_direction();
  actual_sprite = images.begin();
}

void Animation::setup_direction(){
  if(direction == Direction::LEFT)
    std::reverse(images.begin(), images.end());
}

bool Animation::load(){
  std::vector<Image *>::iterator it;
  for(it = images.begin(); it < images.end(); it++){
    (*it)->load();
  }
  return true;
}

void Animation::draw(int x, int y){
  (*actual_sprite)->draw(x,y);
  next();
}

bool Animation::is_end_of_sprites(){
  return actual_sprite == images.end();
}

void Animation::next(){
  if(is_end_of_sprites() && !is_in_loop()){
    finish();
  }else if(actual_sprite < images.end()){
    (*actual_sprite)->deactivate();
    actual_sprite++;
    (*actual_sprite)->activate();
  }else{
    actual_sprite = images.begin();
  }
}

void Animation::set_sprites_order(int total_sprites, std::string direction){
  //[TODO]
}

void Animation::finish(){
  deactivate();
  finished = true;
}

bool Animation::is_finished(){
  return finished;
}

bool Animation::is_in_loop(){
  return in_loop;
}

void Animation::deactivate_loop(){
  in_loop = false; 
}
