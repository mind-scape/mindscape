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
    case(GameObjectFactory::FOX):
      return fabricate_fox(name, coordinates, priority);
    case(GameObjectFactory::PLATFORM):
      return fabricate_platform(name, coordinates, priority);
    case(GameObjectFactory::BUTTON):
      return fabricate_button(name, coordinates, priority);
    case(GameObjectFactory::BACKGROUND):
      return fabricate_background(name, coordinates, priority);
    case(GameObjectFactory::HUD_FOX):
      return fabricate_hud_fox(name, coordinates, priority);
    case(GameObjectFactory::HUD_GIRL):
      return fabricate_hud_girl(name, coordinates, priority);
    case(GameObjectFactory::STAR):
      return fabricate_star(name, coordinates, priority);
    case(GameObjectFactory::SELECT_ARROW):
      return fabricate_select_arrow(name, coordinates, priority);
    case(GameObjectFactory::MUSIC_PLAYER):
      return fabricate_music_player(name, coordinates, priority);
    case(GameObjectFactory::CLOWN):
      return fabricate_clown(name, coordinates, priority);
    case(GameObjectFactory::DARK_GIRL):
      return fabricate_dark_girl(name, coordinates, priority);
    case(GameObjectFactory::UNCLE):
      return fabricate_uncle(name, coordinates, priority);
    case(GameObjectFactory::ARM):
      return fabricate_arm(name, coordinates, priority);
    default:
      return NULL;
  }
}

engine::GameObject* GameObjectFactory::fabricate_hud_fox(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* hud_fox = new HudFox(name, position, priority);
  return hud_fox;
}

engine::GameObject* GameObjectFactory::fabricate_hud_girl(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* hud_girl = new HudGirl(name, position, priority);
  return hud_girl;
}

engine::GameObject* GameObjectFactory::fabricate_button(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* button = new Button(name, position, priority);
  return button;
}


engine::GameObject* GameObjectFactory::fabricate_select_arrow(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* select_arrow = new SelectArrow(name, position, priority);
  return select_arrow;
}

engine::GameObject* GameObjectFactory::fabricate_fox(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* fox = new Fox(name, position, priority);
  return fox;
}

engine::GameObject* GameObjectFactory::fabricate_background(
  std::string name, std::pair<int, int> position, int priority){
  Background* background = new Background(
    name, position, priority
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
    name, position, priority
  );
  return spider;
}

engine::GameObject* GameObjectFactory::fabricate_scorpion(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* scorpion = new Scorpion(
    name, position, priority
  );
  return scorpion;
}

engine::GameObject* GameObjectFactory::fabricate_star(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* scorpion = new Star(
    name, position, priority
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

void GameObjectFactory::fabricate_text(
  engine::GameObject *game_object, std::string p_text,
  std::string font_path, int font_size,
  std::pair<int, int> displacement, int priority){

    engine::Game& game = engine::Game::get_instance();
    engine::Text* text = new engine::Text(game.get_renderer(),
      "text", displacement, priority, p_text, font_path, font_size);

    game_object->add_component(text);
}

void GameObjectFactory::fabricate_action(
  engine::GameObject *game_object, int p_command, std::string param){
  Action::Command command = static_cast<Action::Command>(p_command);
  Action *action = new Action(command);
  Button* button = dynamic_cast<Button *>(game_object);
  button->set_action(action, param);
}

void GameObjectFactory::fabricate_translation(
  engine::GameObject *game_object, int p_key, std::string event_name){
  engine::KeyboardEvent::Key key = static_cast<engine::KeyboardEvent::Key>(p_key);
  game_object->translations[key] = event_name;
}

void GameObjectFactory::fabricate_audio(engine::GameObject *game_object,
  std::string name, std::string path, int p_audio_type){
  engine::Audio::AudioType audio_type = static_cast<engine::Audio::AudioType>(p_audio_type);
  engine::Audio *audio = new engine::Audio(name, path, audio_type);
  game_object->add_component(audio);
}

engine::GameObject* GameObjectFactory::fabricate_music_player(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject *music_player = new MusicPlayer(
    name , position, priority
  );

  return music_player;
}

engine::GameObject* GameObjectFactory::fabricate_clown(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* clown = new Clown(
    name , position, priority
  );

  return clown;
}

engine::GameObject* GameObjectFactory::fabricate_dark_girl(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* dark_girl = new DarkGirl(
    name , position, priority
  );

  return dark_girl;
}

engine::GameObject* GameObjectFactory::fabricate_uncle(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* uncle = new Uncle(
    name , position, priority
  );

  return uncle;
}

engine::GameObject* GameObjectFactory::fabricate_arm(
  std::string name, std::pair<int, int> position, int priority){
  engine::GameObject* arm = new Arm(
    name , position, priority
  );

  return arm;
}
