//TODO discover how overwrite static attribute

#ifndef FOX_H
#define FOX_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "platform.hpp"
#include "../engine/include/observable.hpp"
#include "little_girl.hpp"
#include "star.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

const int INITIALIZE_AS_ZERO = 0;

namespace mindscape {
    class Fox : public engine::GameObject {
    private:
        int velocity;
        int star_count = INITIALIZE_AS_ZERO;
        int running_right_animation_count = INITIALIZE_AS_ZERO;
        int running_left_animation_count = INITIALIZE_AS_ZERO;
        int omelete = INITIALIZE_AS_ZERO;
        int girl_hp;
        bool animation_hud_fading = false;
        bool must_give_hp_to_girl = false;

        void initialize_state_map();
        void initialize_hitboxes();
        void initialize_animations();
        void initialize_as_physicable();
        void jump(GameObject *);
        void move_left();
        void move_right();
        void notify(engine::Observable*);
        void move(engine::GameObject*);
        void  follow_jump(GameObject *);
        float calculate_jump_time(float, float);
        float calculate_vy_jump(float, float, float);
        float calculate_vx_jump(float, float);
        bool is_on_the_right(engine::GameObject *);
        engine::Animation *create_animation(
            std::string path,
            int sprite_lines,
            int sprite_columns,
            double duration,
            std::string direction
        );

    public:
        Fox(std::string p_name,std::pair<int, int> position,int priority);
        ~Fox(){};

        void set_star_count(int);
        int get_star_count();
        void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
        void on_event(GameEvent game_event);
        void update_state();
        bool get_animation_hud_fading();
        void set_animation_hud_fading(bool);
    };
}

#endif
