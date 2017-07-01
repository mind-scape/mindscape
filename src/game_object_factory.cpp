#include "game_object_factory.hpp"


using namespace mindscape;

engine::GameObject* GameObjectFactory::fabricate(
  GameObjectFactory::Options option,
  std::string name, //used as an unique id
  std::pair<int, int> coordinates,
  int priority){

  switch(option){
    case(GameObjectFactory::LITTLE_GIRL):
      return fabricate_little_girl(name, coordinates, priority);
    case(GameObjectFactory::SCORPION):
      return fabricate_scorpion(name, coordinates, priority);
    case(GameObjectFactory::SPIDER):
      return fabricate_spider(name, coordinates, priority);
    case(GameObjectFactory::FOOTER):
      return fabricate_footer();
    case(GameObjectFactory::FOX):
      return fabricate_fox(name, coordinates, priority);
    case(GameObjectFactory::PLATFORM):
      return fabricate_platform(name, coordinates, priority);
    case(GameObjectFactory::BUTTON):
      return fabricate_button();
    case(GameObjectFactory::BACKGROUND):
      return fabricate_background(name, coordinates, priority);
    case(GameObjectFactory::SELECT_ARROW):
      return fabricate_select_arrow();
    default:
      return NULL;
  }
}

engine::GameObject* GameObjectFactory::fabricate_footer(){
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

engine::GameObject* GameObjectFactory::fabricate_fox(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* fox = new Fox(name, position, priority);
  return fox;
}

engine::GameObject* GameObjectFactory::fabricate_background(
  std::string name, std::pair<int, int> postion, int priority){
  Background* background = new Background(
    name, postion, priority
  );
  if(name == "main_background")
    background->set_paralax(10);
  else
    background->set_paralax(2*priority);
  return background;
}

engine::GameObject* GameObjectFactory::fabricate_platform(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* platform = new Platform(name, position, priority);
  return platform;
}

engine::GameObject* GameObjectFactory::fabricate_spider(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* spider = new Spider(
    name, postion, priority
  );
  return spider;
}

engine::GameObject* GameObjectFactory::fabricate_scorpion(
  std::string name, std::pair<int, int> postion, int priority){
  engine::GameObject* scorpion = new Scorpion(
    name, postion, priority
  );
  return scorpion;
}

engine::GameObject* GameObjectFactory::fabricate_little_girl(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject *little_girl = new LittleGirl(
    name , position, priority
  );

  return little_girl;
}

void GameObjectFactory::fabricate_hitbox(
  engine::GameObject * game_object,
  std::pair<int, int> displacement,
  std::pair<int, int> dimensions){
  game_object->create_hitbox(displacement, dimensions);
}

void GameObjectFactory::fabricate_image(
  engine::GameObject *game_object,
  std::string path,
  std::pair<int, int> displacement,
  int priority,
  std::pair<int, int> dimensions_on_screen,
  std::pair<int, int> dimensions_on_texture,
  std::pair<int, int> coordinates_on_texture){


  engine::Game& game = engine::Game::get_instance();
  engine::Image* image = new engine::Image(
    game.get_renderer(), path, true, displacement, priority
  );

  image-> set_values(
    dimensions_on_screen,
    dimensions_on_texture,
    coordinates_on_texture
  );

  game_object->add_component(image);
}
