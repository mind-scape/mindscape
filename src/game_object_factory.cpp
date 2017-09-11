/**
* @file game_object_factory.cpp
* @brief Purpose: Contains all the methods related to GameObject handling.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "game_object_factory.hpp"

using namespace mindscape;
/**
* @brief Fabricates an object.
*
* The method compiles all the methods related to object fabrication
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate(
    GameObjectFactory::Options option,
    std::string name, //Used as an unique id
    std::pair<int, int> coordinates, int priority) {
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
    }
}
/**
* @brief Fabricates the fox's hud.
*
* The method fabricates the fox's information
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_hud_fox(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* hud_fox;
    hud_fox = new HudFox(name, position, priority);

    return hud_fox;
}
/**
* @brief Fabricates the girl's hud.
*
* The method fabricates the girl's information
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_hud_girl(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* hud_girl;
    hud_girl = new HudGirl(name, position, priority);

    return hud_girl;
}
/**
* @brief Fabricates the button.
*
* The method fabricates the button
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_button(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* button;
    button = new Button(name, position, priority);

    return button;
}
/**
* @brief Fabricates the selection arrow.
*
* The method fabricates the selection arrow
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_select_arrow(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* select_arrow;
    select_arrow = new SelectArrow(name, position, priority);

    return select_arrow;
}
/**
* @brief Fabricates the fox.
*
* The method fabricates the fox character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_fox(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* fox;
    fox = new Fox(name, position, priority);

    return fox;
}
/**
* @brief Fabricates the background.
*
* The method fabricates the background
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_background(std::string name,
  std::pair<int, int> position, int priority) {
    Background* background;
    background = new Background(name, position, priority);

    if (name == "main_background") {
        background->set_paralax(10);
    }
    else {
        background->set_paralax(2 * priority);
    }

    return background;
}
/**
* @brief Fabricates the plataform.
*
* The method fabricates the plataform
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_platform(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* platform;
    platform = new Platform(name, position, priority);

    return platform;
}
/**
* @brief Fabricates the spider.
*
* The method fabricates the spider character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_spider(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* spider;
    spider = new Spider(name, position, priority);

    return spider;
}
/**
* @brief Fabricates the scorpion.
*
* The method fabricates the scorpion character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_scorpion(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* scorpion;
    scorpion = new Scorpion(name, position, priority);

    return scorpion;
}
/**
* @brief Fabricates the star.
*
* The method fabricates the star
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_star(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* scorpion;
    scorpion = new Star(name, position, priority);

    return scorpion;
}
/**
* @brief Fabricates the girl.
*
* The method fabricates the girl character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_little_girl(std::string name,
   std::pair<int, int> position, int priority) {
     engine::GameObject *little_girl;
     little_girl = new LittleGirl(name , position, priority);

     return little_girl;
}
/**
* @brief Fabricates the hitbox.
*
* The method fabricates the character's hitbox
*
* @param GameObject* containing the reference to the hitbox owner
* @param std:pair<int, int> containing the displacement of the hitbox
* @param std::pair<int, int> containing the dimensions of the hitbox
* @return void.
*/
void GameObjectFactory::fabricate_hitbox(engine::GameObject * game_object,
  std::pair<int, int> displacement, std::pair<int, int> dimensions) {
    game_object->create_hitbox(displacement, dimensions);
}
/**
* @brief Fabricates the image.
*
* The method fabricates the image
*
* @param GameObject* containing the reference to the hitbox owner
* @param std::string containing the path of the image
* @param std:pair<int, int> containing the displacement of the hitbox
* @param int containing the priority of the object
* @param std::pair<int, int> containing the dimensions on the screen
* @param std::pair<int, int> containing the dimensions on the texture
* @param std::pair<int, int> containing the coordinates on the texture
* @return void.
*/
void GameObjectFactory::fabricate_image(engine::GameObject *game_object,
  std::string path, std::pair<int, int> displacement, int priority,
  std::pair<int, int> dimensions_on_screen,
  std::pair<int, int> dimensions_on_texture,
  std::pair<int, int> coordinatesOnTexture) {

    engine::Game& game = engine::Game::get_instance();
    engine::Image* image = new engine::Image(game.get_renderer(), path, true,
     displacement, priority);

    image-> set_values(dimensions_on_screen, dimensions_on_texture,
      coordinatesOnTexture);

    game_object->add_component(image);
}
/**
* @brief Fabricates text.
*
* The method fabricates text
*
* @param GameObject* containing the reference to the text owner
* @param std::string containing the text that will be written
* @param std::string containing the path of the font
* @param int containing the font size
* @param std::pair containing the displacement of the text
* @param int containing the priority of the object
* @return void.
*/
void GameObjectFactory::fabricate_text(engine::GameObject *game_object,
  std::string p_text, std::string font_path, int font_size,
  std::pair<int, int> displacement, int priority) {
    engine::Game& game = engine::Game::get_instance();
    engine::Text* text = new engine::Text(game.get_renderer(),
      "text", displacement, priority, p_text, font_path, font_size);

    game_object->add_component(text);
}
/**
* @brief Fabricates an action.
*
* The method fabricates an action
*
* @param GameObject* containing the reference of the action's owner
* @param int containing the command that identifies the action
* @param std::string containing the action name
* @return void.
*/
void GameObjectFactory::fabricate_action(engine::GameObject *game_object,
  int p_command, std::string param) {
    Action::Command command;
    command = static_cast<Action::Command>(p_command);

    Action *action;
    action = new Action(command);

    Button* button;
    button = dynamic_cast<Button *>(game_object);
    button->set_action(action, param);
}
/**
* @brief Fabricates the translation.
*
* The method fabricates the translation
*
* @param GameObject* containing the reference to the translation's owner
* @param int containing the keyboard event identification
* @param std::string containing the event name
* @return void.
*/
void GameObjectFactory::fabricate_translation(engine::GameObject *game_object,
   int p_key, std::string event_name) {
     engine::KeyboardEvent::Key key;
     key = static_cast < engine::KeyboardEvent::Key > (p_key);

     game_object->translations[key] = event_name;
}
/**
* @brief Fabricates the audio.
*
* The method fabricates the audio
*
* @param GameObject* containing the reference of the audio's owner
* @param std:string containing the name of the audio
* @param std::string containing the path of the audio file
* @param int containing the identification of the audio type
* @return void.
*/
void GameObjectFactory::fabricate_audio(engine::GameObject *game_object,
  std::string name, std::string path, int p_audio_type) {
    engine::Audio::AudioType audio_type;
    audio_type = static_cast<engine::Audio::AudioType>(p_audio_type);

    engine::Audio *audio;
    audio = new engine::Audio(name, path, audio_type);

    game_object->add_component(audio);
}
/**
* @brief Fabricates the music player.
*
* The method fabricates the music player
*
* @param std::string containing the name of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_music_player(
  std::string name, std::pair<int, int> position, int priority){
    engine::GameObject *music_player;
    music_player = new MusicPlayer(name , position, priority);

    return music_player;
}
/**
* @brief Fabricates the clown.
*
* The method fabricates the clown character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_clown(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* clown;
    clown = new Clown(name , position, priority);

    return clown;
}
/**
* @brief Fabricates the dark girl.
*
* The method fabricates the dark girl character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_dark_girl(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* dark_girl;
    dark_girl = new DarkGirl(name , position, priority);

    return dark_girl;
}
/**
* @brief Fabricates the uncle.
*
* The method fabricates the uncle character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_uncle(std::string name,
   std::pair<int, int> position, int priority) {
    engine::GameObject* uncle;
    uncle = new Uncle(name, position, priority);

    return uncle;
}
/**
* @brief Fabricates the arm.
*
* The method fabricates the arm character
*
* @param std::string containing the identification of the object
* @param std:pair containing the coordinates of the new object
* @param int containing the priority of the new object
* @return engine::GameObject* containing the reference of the new object.
*/
engine::GameObject* GameObjectFactory::fabricate_arm(std::string name,
  std::pair<int, int> position, int priority) {
    engine::GameObject* arm;
    arm = new Arm(name , position, priority);

    return arm;
}
