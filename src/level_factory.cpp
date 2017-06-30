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
      Opts type = static_cast<Opts>(std::stoi(object["type"]));

      if(type == Opts::HITBOX){
        std::pair<int, int> dimensions;
        std::pair<int, int> displacement;
        dimensions.first = std::stoi(object["size_x"]);
        dimensions.second = std::stoi(object["size_y"]);
        displacement.first = std::stoi(object["displ_x"]);
        displacement.second = std::stoi(object["displ_y"]);

        mindscape_factory.fabricate_hitbox(level->get_object_by_name(
          object["belongs_to"]), displacement, dimensions); 

      }else if(type == Opts::IMAGE){
        int priority = std::stoi(object["priority"]);
        std::pair<int, int> displacement;
        std::pair<int, int> dimensions_on_screen;
        std::pair<int, int> dimensions_on_texture;
        std::pair<int, int> coordinates_on_texture;
        displacement.first = std::stoi(object["displ_x"]);
        displacement.second = std::stoi(object["displ_y"]);
        dimensions_on_screen.first = std::stoi(object["screen_x"]);
        dimensions_on_screen.second = std::stoi(object["screen_y"]);
        dimensions_on_texture.first = std::stoi(object["tex_x"]);
        dimensions_on_texture.second = std::stoi(object["tex_y"]);
        coordinates_on_texture.first = std::stoi(object["tex_coord_x"]);
        coordinates_on_texture.second = std::stoi(object["tex_coord_y"]);

        mindscape_factory.fabricate_image(
          level->get_object_by_name(object["belongs_to"]),
          object["path"], displacement, priority, dimensions_on_screen,
          dimensions_on_texture, coordinates_on_texture);

      }else{
        engine::GameObject * constructed_obj = mindscape_factory.fabricate(
          type, object["id"], std::make_pair(std::stoi(object["x"]),
          std::stoi(object["y"])), std::stoi(object["priority"])
        ); 

        if(object.count("follows") > 0){ //if follow key is declared
          engine::Observable * observable = level->get_object_by_name(
            object["follows"]);
          observable->attach_observer(constructed_obj);
        }

        level->add_object(constructed_obj);
        level->activate_game_object(constructed_obj);
      }
    }

    return level;
  }

  return NULL;
}

engine::Level* LevelFactory::fabricate_menu(){
  return NULL;
}

engine::Level* LevelFactory::fabricate_game_over(){
  return NULL;
}
