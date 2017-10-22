/** 
 * @file fox.cpp
 * @brief Purpose: Contains methods to game class' management.
 * 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "../include/fox.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/physics.hpp"
#include "../engine/include/log.hpp"
#include <cmath>

//TODO generalize methos create_animation in GOs

using namespace mindscape;

/**
 * @brief Class Contructor.  
 * 
 * Sets character fox's firsts informations (attributes' values).
 *  
 * @param name Character Fox's name(name of the object).
 * @param position Fox's coordinates in the game's map.
 * @param priority Fox's priority in game's execution.  
 * @return void.
 */
Fox::Fox(
    std::string name,
    std::pair<int, int> position,
    int priority)
    :engine::GameObject(
        name,
        position,
        priority,
        {
            {engine::KeyboardEvent::LEFT, "MOVE_LEFT"},
            {engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"},
            {engine::KeyboardEvent::UP, "JUMP"},
            {engine::KeyboardEvent::DOWN, "CROUCH"},
        }
    ) {

        /* Inicialize all the characterists of the Fox */
        initialize_state_map();
        initialize_hitboxes();
        initialize_animations();
        initialize_as_physicable();
};

/**
 * @brief Inicializes Fox Hitbox.  
 * 
 * Inicializes coordinates of the fox's hitbox.  
 * @return void.
 */
void Fox::initialize_hitboxes() {
    DEBUG("Started");

    /* Gets actual state of the game */
    engine::Game& game = engine::Game::get_instance();
    
    /* Creates Fox's hitbox */
    engine::Hitbox* fox_hitbox = nullptr;
    fox_hitbox = new engine::Hitbox(
        "fox_hitbox",
        this->get_position(),
        std::make_pair(0, 110),
        std::make_pair(120, 10),
        game.get_renderer()
    );
    
    /* Adds component in game */
    add_component(fox_hitbox);
    DEBUG("Ended");
}

/**
 * @brief Initiates Fox state in game's map.  
 * 
 * Sets Fox's coordinates in x and y axis, and Fox's action state.
 * @return void.
 */
void Fox::initialize_state_map() {
    DEBUG("Started");

    /* Sets initial position of the Fox in the game, also her action
        state */ 
    states.set_state("X_STATE", "LOOKING_RIGHT");
    states.set_state("Y_STATE", "FALLING");
    states.set_state("ACTION_STATE", "NORMAL");

    DEBUG("Ended");
}

/**
 * @brief Notifies Fox of Little Girl's state.  
 * 
 * Verifies Little Girl's situation, as life and position, and do actions like
 *  heal the Little Girl, jump, move or rest.
 *
 * @param game_object Object for observe game's situation.
 * @return void.
 */
void Fox::notify(engine::Observable *game_object) {

    LittleGirl* little_girl = nullptr;
    little_girl = dynamic_cast<LittleGirl *>(game_object);
    
    if(little_girl) {
    /* If the Little Girl exists */ 

        INFO("Fox notify: Little Girl is NOT NULL");

        if(!little_girl->is_life_full() && get_star_count() == 3) {
            /* If the Little Girl's life is full and Fox has 3 stars */ 

            little_girl->heal(30);
            must_give_hp_to_girl = false;
            animation_hud_fading = true;
        }

        else {
            /* Do nothing */
        }


        if(little_girl->get_position_y() + 70 == get_position_y()) {
            /* If the Little Girl's position is the same of the Fox */ 

            move(little_girl);
        }

        else if(little_girl && 
            little_girl->get_position_y() + 70 != get_position_y() &&
            little_girl->get_state("Y_STATE") == "ON_GROUND" && 
            get_state("Y_STATE") == "ON_GROUND") {
            /* If the Little Girl's position is different of the Fox and both 
            are on the ground */ 
            
            jump(little_girl);
        }

        else if(little_girl->get_state("Y_STATE") != "ON_GROUND" && 
            get_state("Y_STATE") == "ON_GROUND") {
            /* If the Little Girl's position is different
            from "Ground" and the Fox is on the ground */
            set_speed_x(0.0);
        }

        else {
            /* Do nothing */
        }
    }

    else {
        /* Do nothing */
       WARN("Fox notify(): Little Girl is NULL");
    }
}

/**
 * @brief Initiates Fox's animation.  
 * 
 * Initiates all Fox's sprites(images).
 *
 * @return void.
 */
void Fox::initialize_animations() {
    DEBUG("Started");

    /* Initiates animation of the Fox's running to right */
    DEBUG("running_right_animation");
    engine::Animation* running_right_animation = nullptr;
    running_right_animation = create_animation(
        "../assets/images/sprites/fox/fox_running_right.png",
        1, 9, 0.9, "RIGHT"
    );
    add_animation("running_right_animation", running_right_animation);

    /* Initiates animation of the Fox's running to left */
    DEBUG("running_left_animation");
    engine::Animation* running_left_animation = nullptr;
    running_left_animation = create_animation(
        "../assets/images/sprites/fox/fox_running_left.png",
        1, 9, 0.9, "LEFT"
    );
    add_animation("running_left_animation", running_left_animation);

    /* Initiates animation of the Fox's standing looking right */
    DEBUG("idle_right_animation");
    engine::Animation* idle_right_animation = nullptr;
    idle_right_animation = create_animation(
      "../assets/images/sprites/fox/fox_idle_right.png",
        1, 10, 1.5, "RIGHT"
    );
    add_animation("idle_right_animation", idle_right_animation);
    idle_right_animation->activate();
    set_actual_animation(idle_right_animation);

    /* Initiates animation of the Fox's standing looking left */
    DEBUG("idle_left_animation");
    engine::Animation* idle_left_animation = nullptr;
    idle_left_animation = create_animation(
        "../assets/images/sprites/fox/fox_idle_left.png",
        1, 10, 1.5, "LEFT"
    );
    add_animation("idle_left_animation", idle_left_animation);

    /* Initiates animation of the Fox's jumping to right */
    DEBUG("jumping_right_animation");
    engine::Animation* jumping_right_animation = nullptr;
    jumping_right_animation = create_animation(
        "../assets/images/sprites/fox/fox_jumping_right.png",
        1, 4, 1.5, "RIGHT"
    );
    add_animation("jumping_right_animation", jumping_right_animation);

    /* Initiates animation of the Fox's jumping to left */
    DEBUG("jumping_left_animation");
    engine::Animation* jumping_left_animation = nullptr;
    jumping_left_animation = create_animation(
        "../assets/images/sprites/fox/fox_jumping_left.png",
        1, 4, 1.5, "LEFT"
    );
    add_animation("jumping_left_animation", jumping_left_animation);
   
   DEBUG("Ended"); 
}

/**
 * @brief Creates Fox's animation.  
 * 
 * Creates all Fox's animation based on Fox's sprites.
 *
 * @param image_path Path of the Fox's sprite. 
 * @param sprite_lines Line of the Fox's sprite. 
 * @warning Limitations of sprite_lines and sprite_columns are
 * 1 to the quantity of lines/columns in the image.
 * @param sprite_columns Column of the Fox's sprite needed.
 * @param duration Duration of the Fox's image to show up.
 * @param direction Direction of the Fox's image.
 * @return engine::Animation* The animation constructed.
 */
engine::Animation* Fox::create_animation(
    std::string image_path,
    int sprite_lines,
    int sprite_columns,
    double duration,
    std::string direction) {

    DEBUG("Started");
    
    engine::Game& game = engine::Game::get_instance(); /* Gets game instance */
    engine::Animation* animation = nullptr;

    /* Creates an animation Object of the Fox */
    animation = new engine::Animation(
        game.get_renderer(),
        image_path, 
        // is_active      
        false, 
        // displacement               
        std::make_pair(0, 0),
        // priority
        1,                    
        sprite_lines,
        sprite_columns,
        duration,             
        // in_loop
        true,                 
        direction           
    );

    /* Set dimentions on screen and, coordinates and dimention on texture */
    animation->set_values(
        std::make_pair(120, 120),
        std::make_pair(120, 120),
        std::make_pair(0, 0)
    );

    DEBUG("Ended");

    return animation;
}

/**
 * @brief Initiates Fox's physics.  
 * 
 * Applies physics forces in character as gravity, and makes it collidable.
 *
 * @return void.
 */
void Fox::initialize_as_physicable() {
    DEBUG("Started");

    /* Gets Physics object and makes Fox collidable */
    engine::Physics *physics = nullptr;
    physics = engine::Physics::get_instance();
    physics->add_physicable(this);
    collidable = true;

    DEBUG("Ended");
}

/**
 * @brief Gets Fox's event.  
 * 
 * Gets actual animation, position and modifies position in axis x if needed.
 *
 * @param game_event Object of the current game event.
 * @return void.
 */
void Fox::on_event(GameEvent game_event) {

    /* Gets name of the game event */
    std::string event_name = ""; /**< String. Variable to catch game 
    event name. */

    event_name = game_event.game_event_name;

    /* Gets actual animation */
    engine::Animation* actual_animation = nullptr; /**< Pointer. Variable for 
    actual animation. */
    actual_animation = get_actual_animation();
    
    /* Gets coordinates of the game event */
    std::string actual_x_state = ""; /**< String. Variable for x coordinate. */
    std::string actual_y_state = ""; /**< String. Variable for y coordinate. */
    std::string actual_action_state = ""; /**< String. Variable for actual 
    action state. */
    actual_x_state = states.get_state("X_STATE");
    actual_y_state = states.get_state("Y_STATE");
    actual_action_state = states.get_state("ACTION_STATE");

    if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level && 
        actual_action_state == "NORMAL") {
        /* If the event is MOVE LEFT and the Fox is in state NORMAL */

        /* Makes the Fox move left */
        set_position_x(get_position_x() + 10);
    }

    else if(event_name == "MOVE_RIGHT" && 
        !engine::GameObject::on_limit_of_level && 
        actual_action_state == "NORMAL") {
        /* If the event is MOVE RIGHT and the Fox is in state NORMAL */

        /* Makes the Fox move right */
        set_position_x(get_position_x() - 10);
    }

    else {
        /* Do nothing */
    }
}

/**
 * @brief Makes Fox move.  
 * 
 * Makes Fox move according with the Girl's moviment.
 *
 * @param girl Object of the girl.
 * @return void.
 */
void Fox::move(engine::GameObject* girl) {
 
    float fox_position = 0; /**< Integer. Catches Fox's position. */
    float girl_position = 0; /**< Integer. Catches Little Girl's position. */
    int distance_from_girl = 0; /**< Integer. Catches distance between the Fox 
    and the Little Girl. */

    /* Gets objects' position */
    fox_position = get_position_x();
    girl_position = girl->get_position_x();
    states.set_state("Y_STATE", "ON_GROUND");
    
    if(fox_position > girl_position) {
    /* If the Fox's position is greater than the Little Girl's */

        /* Set new Fox's states */
        states.set_state("X_STATE", "LOOKING_LEFT");
        distance_from_girl = fox_position - girl_position;

        if(distance_from_girl <= 200) {
        /* If the distance from the girl is greater than 200 */

            /* Set new Fox's animation: idle to the left */
            set_actual_animation(animations["idle_left_animation"]);
            set_speed_x(0);
        }

        else if(distance_from_girl > 200 && distance_from_girl <= 400) {
        /* If the distance from the girl is between 201 and 400 */

            /* Set new Fox's animation: running to the left */
            set_actual_animation(animations["running_left_animation"]);
            set_speed_x(-10);
        }

        else if(distance_from_girl > 400) {
        /* If the distance from the girl is greater 400 */

            /* Set new Fox's animation: running to the left */
            set_actual_animation(animations["running_left_animation"]);
            set_speed_x(-15);
        }

        else {
            /* Do nothing */
        }
    }

    else {
    /* If the Fox's position is lower than or equal to the Little Girl's */

        /* Set new Fox's states */
        states.set_state("X_STATE", "LOOKING_RIGHT");
        distance_from_girl = girl_position - fox_position;

        if(distance_from_girl <= 100) {
        /* If the distance from the girl is lower than, or equal to, 1000 */

            /* Set new Fox's animation: idle to the right */
            set_actual_animation(animations["idle_right_animation"]);
            set_speed_x(0);
        }
    
        else if(distance_from_girl > 100 && distance_from_girl <= 350) {
        /* If the distance from the girl is between 101 and 350 */

            /* Set new Fox's animation: running to the right */
            set_actual_animation(animations["running_right_animation"]);
            set_speed_x(10);
        }

        else if(distance_from_girl > 350) {
        /* If the distance from the girl is greater than 350 */

            /* Set new Fox's animation: running to the right */
            set_actual_animation(animations["running_right_animation"]);
            set_speed_x(15);
        }

        else {
            /* Do nothing */
        }
    }

}

/**
 * @brief Makes Fox jump.  
 * 
 * Makes Fox jump according with the Girl's position and if She's jumping 
 * as well.
 *
 * @param little_girl Object of the girl.
 * @return void.
 */
void Fox::jump(engine::GameObject *little_girl) {

    if(get_state("Y_STATE") != "JUMPING" && get_state("Y_STATE") != "FALLING") {
    /* If the Fox is not jumping */

        /* Makes it jump */
        states.set_state("Y_STATE", "JUMPING");

        if(little_girl->get_state("X_STATE") == "LOOKING_LEFT") {
        /* If the Little Girl is looking left */

            /* Makes the Fox looks left */
            set_actual_animation(animations["jumping_left_animation"]);
        }

        else if(little_girl->get_state("X_STATE") == "LOOKING_RIGHT") {
        /* If the Little Girl is looking right */

            /* Makes the Fox looks right */
            set_actual_animation(animations["jumping_right_animation"]);
        }

        else {
            /* Do nothing */
        }

        /* Makes the Fox follow the Little Girl jump */
        follow_jump(little_girl);
    }

    else {
        
        if(get_position_x() > little_girl->get_position_x()) { 
        /* If the girl is on the left */

            /* Makes the Fox look left */
            states.set_state("X_STATE","LOOKING_LEFT");
        }

        else {
        /* If the girl is on the left */

            /* Makes the Fox look left */
            states.set_state("X_STATE","LOOKING_RIGHT");
        }
    }
}

/**
 * @brief Makes Fox jump according with the Girl.  
 * 
 * Calculates gravity and position in axis for the Fox jumps according the Girl.
 *
 * @param little_girl Object of the girl.
 * @return void.
 */
void Fox::follow_jump(engine::GameObject *little_girl) {

    /* Gets physics instance */
    engine::Physics *physics = nullptr; /**< Pointer. Physics engine pointer */
    physics = engine::Physics::get_instance();
    
    
    float final_x = 0; /**< Float. Variable to catch x coordinate. */
    float throw_speed_x = 0; /**< Float. Variable to catch throw speed in 
    x coordinate. */
    float jump_time = 0; /**< Float. Variable to catch jump time. */
    float gravity = 0; /**< Float. Variable to catch gravity. */
    float final_y = 0; /**< Float. Variable to catch y coordinate. */
    float throw_speed_y = 0; /**< Float. Variable to catch throw speed in 
    y coordinate. */
   
    final_x = 500;
    throw_speed_x = is_on_the_right(little_girl) ? 15 : -15;
    jump_time = calculate_jump_time(final_x, throw_speed_x);
    gravity = physics->get_gravity();
    final_y = little_girl->get_position_y() + 70;
   
    /* Calculates speeds */ 
    throw_speed_y = calculate_vy_jump(final_y, gravity, jump_time);
    throw_speed_x = calculate_vx_jump(final_x, jump_time);

    /* Sets speeds */
    set_speed_y(throw_speed_y < -30? -20 : throw_speed_y);
    set_speed_x(std::abs(throw_speed_x) > 20 ? 
        throw_speed_x/std::abs(throw_speed_x)*15 : throw_speed_x);
}

/**
 * @brief Verifies if the Fox is on the right.  
 * 
 * Verifies if the Fox is on the right of the map.
 *
 * @param target Object that is the reference for the verification.
 * @return bool True if the Fox is on the right, false if it does not.
 */
bool Fox::is_on_the_right(engine::GameObject *target) {
    return (get_position_x() - target->get_position_x() < 0);
}

/**
 * @brief Calculates Fox's jump velocity in axis y.  
 * 
 * Calculates Fox's jump velocity in axis y in its throw.
 *
 * @param final_y Final position in axis y.
 * @param gravity Value of the gravity.
 * @param jump_time Time that the Fox takes to jump.
 * @return float Final velocity in axis y.
 */
float Fox::calculate_vy_jump(float final_y, float gravity, float jump_time) {

    float initial_y = 0; /**< Float. Variable to initial y coordinate. */
    float delta_y =  0; /**< Float. Variable to delta y */
    float throw_speed_y = 0; /**< Float. Variable to catch throw speed in 
    y coordinate. */

    /* Calculates throw speed in vertical direction */
    initial_y = (float) get_position_y();
    delta_y = final_y - initial_y;
    throw_speed_y = (delta_y/jump_time) - (gravity * jump_time/2);

    return throw_speed_y;
}

/**
 * @brief Calculates Fox's jump velocity in axis x.  
 * 
 * Calculates Fox's jump velocity in axis x in its throw.
 *
 * @param final_x Final position in axis x.
 * @param jump_time Time that the Fox takes to jump.
 * @return float Final velocity in axis x.
 */
float Fox::calculate_vx_jump(float final_x, float jump_time) {

    float initial_x = 0;  /**< Float. Variable to initial x coordinate. */
    float delta_x = 0; /**< Float. Variable to delta x */
    float throw_speed_x = 0; /**< Float. Variable to catch throw speed in 
    x coordinate. */

    /* Calculates throw speed in horizontal direction */
    initial_x = (float) get_position_x();
    delta_x = final_x - initial_x;
    throw_speed_x = std::floor(delta_x/jump_time);


    return throw_speed_x;
}

/**
 * @brief Calculates Fox's jump time.  
 * 
 * Calculates time that the Fox takes to jump.
 *
 * @param final_x Final position in axis x.
 * @param speed_x Speed in axis x.
 * @return float Time for the fox to jump.
 */
float Fox::calculate_jump_time(float final_x, float speed_x) {
    
    float initial_x = 0; /**< Float. Variable to initial x coordinate. */
    float delta_x = 0; /**< Float. Variable to delta x */
    float jump_time = 0; /**< Float. Variable to jump time */
    
    /* Calculates jump time */
    initial_x = (float) get_position_x();
    delta_x = final_x - initial_x;
    jump_time = delta_x/speed_x;
    
    return jump_time;
}

/**
 * @brief Updates Fox's state in the game.  
 * 
 * Update Fox's state in the game related to the position, if is looking right, 
 * left, is in the ground or falling.
 *
 * @return void.
 */
void Fox::update_state() {

    if(get_speed_x() == 0.0 && get_speed_y() == 0.0) {
    /* If the Fox speed is zero */

        std::string actual_x_state = ""; /**< String. Gets actual state in x
        coordinate */
        actual_x_state = get_state("X_STATE");

        if(actual_x_state == "LOOKING_RIGHT") {
        /* If the Fox is looking rigth */

            /* Sets idle_right animation rigth */
            set_actual_animation(animations["idle_right_animation"]);
        }

        else if(actual_x_state == "LOOKING_LEFT") {
        /* If the Fox is looking left */

            /* Sets idle_right animation left */
            set_actual_animation(animations["idle_left_animation"]);
        }

        else {
            /* Do nothing */
        }
    }

    else {
        /* Do nothing */
    }
    
    if(get_speed_y() == 0.0 && get_state("Y_STATE") != "JUMPING") {
    /* If the Fox is not jumping */

        /* Sets state ON GROUND */
        states.set_state("Y_STATE", "ON_GROUND");
    }

    else if(get_speed_y() == 0.0) {
    /* If the speed in y coordinate is zero */

        /* Sets state FALLING */
        states.set_state("Y_STATE", "FALLING");
    }

    else {
        /* Do nothing */
    }

}

/**
 * @brief Describes action when the Fox collides.  
 * 
 * Produces the effect in Fox when it collides with another object.
 *
 * @param other Another game object.
 * @param p_my_hitbox Fox's hitbox.
 * @param p_other_object Other object's hitbox.
 * @return void.
 */
void Fox::on_collision(engine::GameObject* other, 
    engine::Hitbox* p_my_hitbox, engine::Hitbox* p_other_hitbox) {

    Platform* platform = nullptr; /**< Pointer. Gets platform object */
    engine::Hitbox* my_hitbox = nullptr; /**< Pointer. Gets hitbox object */
    Star* star = nullptr; /**< Pointer. Gets star object */
    engine::Hitbox* other_hitbox = nullptr; /**< Pointer. Gets hitbox from 
    another object */

    /* Sets the objects initializeded */
    platform = dynamic_cast<Platform *>(other);
    other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);
    star = dynamic_cast<Star *>(other);
    my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
    
    if(get_speed_y() >= 0 && platform) {
    /* If speed in y axis is equal or highter than zero and platform is not 
        null */  
        
        /* Sets speed and position in y axis */
        set_speed_y(0.0);
        set_position_y(other_hitbox->get_coordinates().second - 110);
    }

    else if(star) {
        /* If star is not null */
    
        if(get_star_count() != 3) {
        /* If has not 3 stars */

            star->play_song("got_me"); /* Plays star sound effect */
            star->set_actual_animation(star->animations["star_fading"]); /* 
            Starts new animation */
            star->deactivate_components(); /* Deactivate star component */
            set_star_count(get_star_count() + 1); /* Incrementates star count */
        }

        else {
            /* Do nothing */
        }
    }

    else {
        /* Do nothing */
    }

}

/**
 * @brief Gets Animation of the Hud
 *
 * Returns if the animation of the Hud is inicialized or not.  
 * 
 * @return bool True if the animation of the Hud is on, False if it does not.
 */
bool Fox::get_animation_hud_fading() {
    return animation_hud_fading;
}

/**
 * @brief Sets Animation of the Hud
 *
 * Set the value of the Hud Animation.  
 * 
 * @param bol True if the animation of the Hud is on, False if it does not.
 * @return void.
 */
void Fox::set_animation_hud_fading(bool bol) {
    animation_hud_fading = bol;
}

/**
 * @brief Gets the number of the stars
 *
 * Gets current number of the stars.  
 * 
 * @warning Limitations: start_count maximum is 3.
 * @return int Stars' number.
 */
int Fox::get_star_count() {
    return star_count;
}

/**
 * @brief Sets the number of the stars
 *
 * Sets the current number of the stars.  
 * 
 * @param quantity New number of the stars. 
 * @warning Limitations: start_count maximum is 3.
 * @return int Stars' number.
 */
void Fox::set_star_count(int quantity) {
    star_count = quantity;
}
