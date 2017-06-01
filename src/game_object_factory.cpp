#include "game_object_factory.hpp"

using namespace mindscape;

engine::GameObject* GameObjectFactory::fabricate(
  GameObjectFactory::Options option,
  std::pair<int, int> coordinates,
  int priority){

  switch(option){
    case(GameObjectFactory::LITTLE_GIRL):
      return fabricate_little_girl(); 
    case(GameObjectFactory::FOX):
      return fabricate_fox(); 
    case(GameObjectFactory::PLATFORM):
      return fabricate_little_girl(); 
    case(GameObjectFactory::BUTTON):
      return fabricate_button();
    case(GameObjectFactory::BACKGROUND):
      return fabricate_background();
    case(GameObjectFactory::SELECT_ARROW):
      return fabricate_select_arrow();
    default:
      return NULL;
  }
}

engine::GameObject* GameObjectFactory::fabricate_platform(){
  std::cout << "NOT IMPLEMENTED YET" << std::endl;
  return NULL;
}

engine::GameObject* GameObjectFactory::fabricate_background(){
  std::cout << "NOT IMPLEMENTED YET" << std::endl;
  return NULL;
}

engine::GameObject* GameObjectFactory::fabricate_button(){
  std::cout << "NOT IMPLEMENTED YET" << std::endl;
  return NULL;
}

engine::GameObject* GameObjectFactory::fabricate_select_arrow(){
  std::cout << "NOT IMPLEMENTED YET" << std::endl;
  return NULL;
}

engine::GameObject* GameObjectFactory::fabricate_fox(){
  std::cout << "NOT IMPLEMENTED YET" << std::endl;
  return NULL;
}

engine::GameObject* GameObjectFactory::fabricate_little_girl(){
  engine::Game& game = engine::Game::get_instance();

  std::pair<int, int> place (416, 335);

  //Creating running right image
  engine::Image* image_running_right = new engine::Image(
    game.renderer,
    "../assets/images/menina_correndo_direita.png",
    true,
    std::make_pair(0, 0),
    2
  );
  image_running_right->set_values(
    std::make_pair(192, 192),
    std::make_pair(192, 192),
    std::make_pair(0, 0)
  );

  //Creating running right image
  engine::Image* image_running_left = new engine::Image(
    game.renderer,
    "../assets/images/menina_correndo_esquerda.png",
    false,
    std::make_pair(0, 0),
    2
  );
  image_running_left->set_values(
    std::make_pair(192, 192),
    std::make_pair(192, 192),
    std::make_pair(0, 0)
  );

  engine::GameObject* little_girl = new engine::LittleGirl("little_girl", place, 52);
  little_girl->hitbox = {
    .x = little_girl->position.first,
    .y = little_girl->position.second,
    .w = 50,
    .h = 1
  };

  little_girl->collidable = true;
  little_girl->add_component("image", image_running_right);
  little_girl->add_component("image", image_running_left);

  return little_girl;
}
