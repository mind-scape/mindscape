#include "../include/level_factory.hpp"
#include "../engine/include/persistence_dat.hpp"
#include "../engine/include/observable.hpp"
#include <unordered_map>
#include <vector>

using namespace mindscape;

typedef mindscape::GameObjectFactory::Options Opts;

engine::Level *LevelFactory::fabricate_level(std::string path){
  engine::Level *level = new engine::Level();
  GameObjectFactory mindscape_factory = GameObjectFactory();
  engine::PersistenceDat *persistence = engine::PersistenceDat::get_instance();
  engine::PersistenceMap *objects = persistence->load(path);
  if(!!objects){
    for(auto it = objects->begin(); it < objects->end(); it++){
      std::unordered_map<std::string, std::string> object = *it;

      engine::GameObject * constructed_obj = mindscape_factory.fabricate(
        static_cast<Opts>(std::stoi(object["type"])),
        std::make_pair(std::stoi(object["x"]), std::stoi(object["y"])),
        std::stoi(object["priority"])
      ); 


std::cout << "1 QUEBROOOOOOOOOOOU" << std::endl;
      if(object.count("follows") > 0){ //if follow key is declared

std::cout << "2 QUEBROOOOOOOOOOOU" << std::endl;
        engine::Observable * observable = level->get_object_by_id(
          std::stoi(object["follows"])
        );
std::cout << "OPAAAAAA " << object["follows"] << std::endl;

std::cout << "3 QUEBROOOOOOOOOOOU" << std::endl;
        observable->attach_observer(constructed_obj);
      }

std::cout << "4 QUEBROOOOOOOOOOOU" << std::endl;
      level->add_object(constructed_obj);
std::cout << "5 QUEBROOOOOOOOOOOU" << std::endl;
      level->activate_game_object(constructed_obj);
    }

    return level;
  }else{
    return NULL;
  }
}

engine::Level* LevelFactory::fabricate_menu(){
  return NULL;
}

engine::Level* LevelFactory::fabricate_game_over(){
  return NULL;
}
