#include "../include/hud_girl.hpp"

using namespace mindscape;

HudGirl::HudGirl(
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

void HudGirl::notify(engine::Observable* game_object){
  LittleGirl* little_girl = dynamic_cast<LittleGirl *>(game_object);
  if(little_girl){
    engine::Image* bar = dynamic_cast<engine::Image *>(images[0]);
    float reducer_percentage = little_girl->get_hp()/90.0;
    int bar_size = reducer_percentage * 180;
    bar->set_values(
        std::make_pair(bar_size, 10),
        std::make_pair(180, 10),
        std::make_pair(0, 0)
        );
  }
}

void HudGirl::initialize_animations(){
  engine::Animation* girl_hp = create_animation(
      "/opt/mindscape/assets/images/sprites/hud/hud_girl.png",
      1,1,0.9, "RIGHT"
  );

  engine::Image* hp = create_image();

  add_component(hp);
  add_animation("girl_hp", girl_hp);
  girl_hp->activate();
  set_actual_animation(girl_hp);
}

engine::Image* HudGirl::create_image(){
  engine::Game& game = engine::Game::get_instance();
  engine::Image* health_bar = new engine::Image(game.get_renderer(),
  "/opt/mindscape/assets/images/sprites/sprites_test/health_bar.jpg",
  true, std::make_pair(74, 64), 70);

  health_bar->set_values(
      std::make_pair(180, 10),
      std::make_pair(180, 10),
      std::make_pair(0, 0)
      );

  return health_bar;
}

engine::Animation* HudGirl::create_animation(
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
      std::make_pair(266, 90),
      std::make_pair(266, 90),
      std::make_pair(0, 0)
      );

  return animation;
}
