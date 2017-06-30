#include "game_object_factory.hpp"


using namespace mindscape;

engine::GameObject* GameObjectFactory::fabricate(
  GameObjectFactory::Options option,
  std::pair<int, int> coordinates,
  int priority){

  switch(option){
    case(GameObjectFactory::LITTLE_GIRL):
      return fabricate_little_girl(coordinates, priority);
    case(GameObjectFactory::SCORPION):
      return fabricate_scorpion(coordinates, priority);
    case(GameObjectFactory::SPIDER):
      return fabricate_spider(coordinates, priority);
    case(GameObjectFactory::FOOTER):
      return fabricate_footer();
    case(GameObjectFactory::FOX):
      return fabricate_fox();
    case(GameObjectFactory::PLATFORM):
      return fabricate_platform();
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

engine::GameObject* GameObjectFactory::fabricate_spider(
  std::pair<int, int> postion, int priority){
  engine::GameObject* spider = new Spider(
    "spider", postion, priority
  );
  return spider;
}

engine::GameObject* GameObjectFactory::fabricate_scorpion(
  std::pair<int, int> postion, int priority){
  engine::GameObject* scorpion = new Scorpion(
    "scorpion", postion, priority
  );
  return scorpion;
}

engine::GameObject* GameObjectFactory::fabricate_little_girl(
  std::pair<int, int> position, int priority){
  engine::GameObject *little_girl = new LittleGirl(
    "little_girl", position, priority
  );
  return little_girl;
}
