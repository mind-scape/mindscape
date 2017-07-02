#include "../include/hud_fox.hpp"

using namespace mindscape;

HudFox::HudFox(
  std::string name,
  std::pair<int, int> position,
  int priority)
  :engine::GameObject(
    name,
    position,
    priority,
    {
    }
  ){
    initialize_animations();
};

void HudFox::notify(engine::Observable* game_object){
  Fox* fox = dynamic_cast<Fox *>(game_object);
  if(fox){
    int count = fox->get_star_count();
    if(count == 0){
      if(!(get_actual_animation() == animations["zero_star"])){
        set_actual_animation(animations["zero_star"]);
      }
    }else if(count == 1){
      if(!(get_actual_animation() == animations["one_star"])){
        set_actual_animation(animations["one_star"]);
      }
    }else if(count == 2){
      if(!(get_actual_animation() == animations["two_star"])){
        set_actual_animation(animations["two_star"]);
      }
    }else if(count == 3){
      if(!(get_actual_animation() == animations["three_star"])){
        set_actual_animation(animations["three_star"]);
      }
    }
  }
}

void HudFox::initialize_animations(){
  engine::Animation* fox_zero_star = create_animation(
      "../assets/images/sprites/hud/hud_fox_0.png",
      1,1,0.9, "RIGHT"
      );

  engine::Animation* fox_one_star = create_animation(
      "../assets/images/sprites/hud/hud_fox_1.png",
      1,1,0.9, "RIGHT"
      );

  engine::Animation* fox_two_star = create_animation(
      "../assets/images/sprites/hud/hud_fox_2.png",
      1,1,0.9, "RIGHT"
      );

  engine::Animation* fox_three_star = create_animation(
      "../assets/images/sprites/hud/hud_fox_3.png",
      1,1,0.9, "RIGHT"
      );

  add_animation("zero_star", fox_zero_star);
  add_animation("one_star", fox_one_star);
  add_animation("two_star", fox_two_star);
  add_animation("three_star", fox_three_star);
  fox_zero_star->activate();
  set_actual_animation(fox_zero_star);
}

engine::Animation* HudFox::create_animation(
    std::string path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction){

  engine::Game& game = engine::Game::get_instance();
  engine::Animation* animation = new engine::Animation(
      game.get_renderer(),
      path,                 // image path
      false,                // is_active
      std::make_pair(0, 0), // displcement
      1,                    // priority
      sprite_lines,         // sprite_lines
      sprite_columns,       // sprite_columns
      duration,             // duration
      true,                 // in_loop
      direction             // direction
      );

  animation->set_values(
      std::make_pair(170, 78),
      std::make_pair(170, 78),
      std::make_pair(0, 0)
      );

  return animation;
}
