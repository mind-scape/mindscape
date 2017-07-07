#include "../include/level_factory.hpp"
#include "../engine/include/persistence_dat.hpp"
#include "../engine/include/observable.hpp"
#include <unordered_map>
#include <vector>

using namespace mindscape;

typedef mindscape::GameObjectFactory::Options Opts;

void LevelFactory::update_level(engine::Level *level, std::string path){
  std::vector<engine::GameObject *> new_objects = execute_dat(level, path);
  for(auto game_object : new_objects){
    level->activate_game_object(game_object);
    game_object->load();
  }
}

std::vector<engine::GameObject *> LevelFactory::execute_dat(engine::Level *level, std::string path){
  std::vector<std::string> includes;
  std::vector<engine::GameObject *> added_game_objects;
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

      }else if(type == Opts::TEXT){
        int priority = std::stoi(object["priority"]);
        std::string text = object["text"];
        std::string font_path = object["font_path"];
        int font_size = std::stoi(object["font_size"]);
        std::pair<int, int> displacement;
        displacement.first = std::stoi(object["displ_x"]);
        displacement.second = std::stoi(object["displ_y"]);

        mindscape_factory.fabricate_text(
          level->get_object_by_name(object["belongs_to"]),
          text, font_path, font_size, displacement, priority);

      }else if(type == Opts::AUDIO){
        std::string name = object["id"];
        std::string path = object["path"];
        int audio_type = std::stoi(object["audio_type"]);
        mindscape_factory.fabricate_audio(
          level->get_object_by_name(object["belongs_to"]),
          name, path, audio_type);

      }else if(type == Opts::ACTION){
        mindscape_factory.fabricate_action(
          level->get_object_by_name(object["belongs_to"]),
          std::stoi(object["command"]), object["param"]);

      }else if(type == Opts::TRANSLATION){
        std::string event_name = object["event_name"];
        int key = std::stoi(object["key"]);
        mindscape_factory.fabricate_translation(
          level->get_object_by_name(object["belongs_to"]),
          key, event_name);

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
        added_game_objects.push_back(constructed_obj);
      }
    }
  }
  return added_game_objects;
}

engine::Level *LevelFactory::fabricate_level(std::string path){
  engine::Level *level = new engine::Level();
  execute_dat(level, path);
  return level;
}

engine::Level* LevelFactory::fabricate_menu(){
  return NULL;
}

engine::Level* LevelFactory::fabricate_game_over(){
  return NULL;
}
