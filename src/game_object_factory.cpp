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
      return fabricate_fox();
    case(GameObjectFactory::PLATFORM):
      return fabricate_platform(name, coordinates, priority);
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

engine::GameObject* GameObjectFactory::fabricate_footer(){
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

engine::GameObject* GameObjectFactory::fabricate_platform(
  std::string name, std::pair<int, int> postion, int priority){
  engine::GameObject* platform = new Platform(
    name, postion, priority
  );
  return platform;
}

engine::GameObject* GameObjectFactory::fabricate_spider(
  std::string name, std::pair<int, int> postion, int priority){
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
