#include "../include/level_factory.hpp"
#include "../engine/include/persistence_dat.hpp"
#include <unordered_map>

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

      level->add_object(constructed_obj);
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
