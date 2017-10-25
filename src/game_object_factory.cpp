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
    std::string name, /* Used as an unique id */
    std::pair<int, int> coordinates, int priority) {
        switch(option){
          /* For each option that the GameObject assumes, the function returns
             an object created */
            case(GameObjectFactory::LITTLE_GIRL):
            /* Case Little Girl's needed, returns a new Little Girl object */
                return fabricate_little_girl(name, coordinates, priority);
            case(GameObjectFactory::SCORPION):
            /* Case Scorpion's needed, returns a new Scorpion object */
                return fabricate_scorpion(name, coordinates, priority);
            case(GameObjectFactory::SPIDER):
            /* Case Spider's needed, returns a new Spider object */
                return fabricate_spider(name, coordinates, priority);
            case(GameObjectFactory::FOX):
            /* Case Fox's needed, returns a new Fox object */
                return fabricate_fox(name, coordinates, priority);
            case(GameObjectFactory::PLATFORM):
            /* Case Platform's needed, returns a new Platform object */
                return fabricate_platform(name, coordinates, priority);
            case(GameObjectFactory::BUTTON):
            /* Case Button's needed, returns a new Button object */
                return fabricate_button(name, coordinates, priority);
            case(GameObjectFactory::BACKGROUND):
            /* Case Background's needed, returns a new Background object */
                return fabricate_background(name, coordinates, priority);
            case(GameObjectFactory::HUD_FOX):
            /* Case HudFox's needed, returns a new HudFox object */
                return fabricate_hud_fox(name, coordinates, priority);
            case(GameObjectFactory::HUD_GIRL):
            /* Case HudGirl's needed, returns a new HudGirl object */
                return fabricate_hud_girl(name, coordinates, priority);
            case(GameObjectFactory::STAR):
            /* Case Star's needed, returns a new Star object */
                return fabricate_star(name, coordinates, priority);
            case(GameObjectFactory::SELECT_ARROW):
            /* Case SelectArrow's needed, returns a new SelectArrow object */
                return fabricate_select_arrow(name, coordinates, priority);
            case(GameObjectFactory::MUSIC_PLAYER):
            /* Case Music Player's needed, returns a new Music Player object */
                return fabricate_music_player(name, coordinates, priority);
            case(GameObjectFactory::CLOWN):
            /* Case Clown's needed, returns a new Clown object */
                return fabricate_clown(name, coordinates, priority);
            case(GameObjectFactory::DARK_GIRL):
            /* Case DarkGirl's needed, returns a new DarkGirl object */
                return fabricate_dark_girl(name, coordinates, priority);
            case(GameObjectFactory::UNCLE):
            /* Case Uncle's needed, returns a new Uncle object */
                return fabricate_uncle(name, coordinates, priority);
            case(GameObjectFactory::ARM):
            /* Case Arm's needed, returns a new Arm object */
                return fabricate_arm(name, coordinates, priority);
            default:
            /* If the option is not described above, return a null object*/
                return NULL;
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

    /* Inializes a GameObject object and creates a HudFox object */
    engine::GameObject* hud_fox = nullptr;
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
    
    /* Inializes a GameObject object and creates a HudGirl object */    
    engine::GameObject* hud_girl = nullptr;
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

    /* Inializes a GameObject object and creates a Button object */
    engine::GameObject* button = nullptr;
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
    
    /* Inializes a GameObject object and creates a SelectArrow object */
    engine::GameObject* select_arrow = nullptr;
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
    
    /* Inializes a GameObject object and creates a Fox object */
    engine::GameObject* fox = nullptr;
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
    
    /* Inializes a GameObject object and creates a Background object */
    Background* background = nullptr;
    background = new Background(name, position, priority);

    if (name == "main_background") {
    /* If is the main background of the game */
       
        background->set_paralax(10); /* Sets paralax value equal 10 */
    }
    else {
    /* If is not the main background */
    
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

    /* Inializes a GameObject object and creates a Platform object */
    engine::GameObject* platform = nullptr;
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

    /* Inializes a GameObject object and creates a Spider object */
    engine::GameObject* spider = nullptr;
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
    
    /* Inializes a GameObject object and creates a Scorpion object */
    engine::GameObject* scorpion = nullptr;
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

    /* Inializes a GameObject object and creates a Scorpion object */
    engine::GameObject* scorpion = nullptr;
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
    
    /* Inializes a GameObject object and creates a Little Girl object */
    engine::GameObject *little_girl = nullptr;
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

    /* Creates hitbox of the object received */
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

    /* Gets game's istance and creates new Image object */
    engine::Game& game = engine::Game::get_instance();
    engine::Image* image = new engine::Image(game.get_renderer(), path, true,
        displacement, priority);

    /* Sets the values of the new Image */
    image-> set_values(dimensions_on_screen, dimensions_on_texture,
      coordinatesOnTexture);

    game_object->add_component(image); /* Adds Image to the GameObject 
    received */
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

    /* Gets game's istance and creates new Text object */
    engine::Game& game = engine::Game::get_instance();
    engine::Text* text = new engine::Text(game.get_renderer(),
        "text", displacement, priority, p_text, font_path, font_size);

    game_object->add_component(text); /* Adds Text to the GameObject 
    received */
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

    /* Instanciates new Command enum */
    Action::Command command = static_cast < Action::Command > (0);
    command = static_cast<Action::Command>(p_command);

    /* Instanciates new Action object */
    Action *action = NULL;
    action = new Action(command);

    /* Instanciates new Button object */
    Button* button = NULL;
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
    
    /* Inializes new KeyboardEvent object */
    engine::KeyboardEvent::Key key = 
        static_cast < engine::KeyboardEvent::Key > (0);
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
    
    /* Inializes a new AudioType object */
    engine::Audio::AudioType audio_type = 
        static_cast < engine::Audio::AudioType > (0);
    audio_type = static_cast < engine::Audio::AudioType > (p_audio_type);

    /* Creates a new Audio object */
    engine::Audio *audio = nullptr;
    audio = new engine::Audio(name, path, audio_type);

    /* Adds Audio to the GameObject received */
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

    /* Inializes a GameObject object and creates a MusicPlayer object */
    engine::GameObject *music_player = nullptr;
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

    /* Inializes a GameObject object and creates a Clown object */
    engine::GameObject* clown = nullptr;
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

    /* Inializes a GameObject object and creates a Dark Girl object */
    engine::GameObject* dark_girl = nullptr;
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

    /* Inializes a GameObject object and creates an Uncle object */
    engine::GameObject* uncle = nullptr;
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

    /* Inializes a GameObject object and creates an Arm object */
    engine::GameObject* arm = nullptr;
    arm = new Arm(name , position, priority);

    return arm;
}
