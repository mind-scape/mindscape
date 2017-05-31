#include "keyboard_event.hpp"

using namespace engine;

KeyboardEvent::KeyMap KeyboardEvent::keymap = {
  {SDL_SCANCODE_BACKSPACE, KeyboardEvent::BACKSPACE},
  {SDL_SCANCODE_TAB, KeyboardEvent::TAB},
  {SDL_SCANCODE_CLEAR, KeyboardEvent::CLEAR},
  {SDL_SCANCODE_RETURN, KeyboardEvent::RETURN},
  {SDL_SCANCODE_PAUSE, KeyboardEvent::PAUSE},
  {SDL_SCANCODE_ESCAPE, KeyboardEvent::ESCAPE},
  {SDL_SCANCODE_SPACE, KeyboardEvent::SPACE},

  {SDL_SCANCODE_COMMA, KeyboardEvent::COMMA},
  {SDL_SCANCODE_MINUS, KeyboardEvent::MINUS},
  {SDL_SCANCODE_PERIOD, KeyboardEvent::PERIOD},
  {SDL_SCANCODE_SLASH, KeyboardEvent::SLASH},

  {SDL_SCANCODE_0, KeyboardEvent::ZERO},
  {SDL_SCANCODE_1, KeyboardEvent::ONE},
  {SDL_SCANCODE_2, KeyboardEvent::TWO},
  {SDL_SCANCODE_3, KeyboardEvent::THREE},
  {SDL_SCANCODE_4, KeyboardEvent::FOUR},
  {SDL_SCANCODE_5, KeyboardEvent::FIVE},
  {SDL_SCANCODE_6, KeyboardEvent::SIX},
  {SDL_SCANCODE_7, KeyboardEvent::SEVEN},
  {SDL_SCANCODE_8, KeyboardEvent::EIGHT},
  {SDL_SCANCODE_9, KeyboardEvent::NINE},
  {SDL_SCANCODE_SEMICOLON, KeyboardEvent::SEMICOLON},
  {SDL_SCANCODE_EQUALS, KeyboardEvent::EQUALS},

  {SDL_SCANCODE_LEFTBRACKET, KeyboardEvent::LEFT_BRACKET},
  {SDL_SCANCODE_BACKSLASH, KeyboardEvent::BACKSLASH},
  {SDL_SCANCODE_RIGHTBRACKET, KeyboardEvent::RIGHT_BRACKET},
  {SDL_SCANCODE_DELETE, KeyboardEvent::DELETE},

  {SDL_SCANCODE_A, KeyboardEvent::A},
  {SDL_SCANCODE_B, KeyboardEvent::B},
  {SDL_SCANCODE_C, KeyboardEvent::C},
  {SDL_SCANCODE_D, KeyboardEvent::D},
  {SDL_SCANCODE_E, KeyboardEvent::E},
  {SDL_SCANCODE_F, KeyboardEvent::F},
  {SDL_SCANCODE_G, KeyboardEvent::G},
  {SDL_SCANCODE_H, KeyboardEvent::H},
  {SDL_SCANCODE_I, KeyboardEvent::I},
  {SDL_SCANCODE_J, KeyboardEvent::J},
  {SDL_SCANCODE_K, KeyboardEvent::K},
  {SDL_SCANCODE_L, KeyboardEvent::L},
  {SDL_SCANCODE_M, KeyboardEvent::M},
  {SDL_SCANCODE_N, KeyboardEvent::N},
  {SDL_SCANCODE_O, KeyboardEvent::O},
  {SDL_SCANCODE_P, KeyboardEvent::P},
  {SDL_SCANCODE_Q, KeyboardEvent::Q},
  {SDL_SCANCODE_R, KeyboardEvent::R},
  {SDL_SCANCODE_S, KeyboardEvent::S},
  {SDL_SCANCODE_T, KeyboardEvent::T},
  {SDL_SCANCODE_U, KeyboardEvent::U},
  {SDL_SCANCODE_V, KeyboardEvent::V},
  {SDL_SCANCODE_W, KeyboardEvent::W},
  {SDL_SCANCODE_X, KeyboardEvent::X},
  {SDL_SCANCODE_Y, KeyboardEvent::Y},
  {SDL_SCANCODE_Z, KeyboardEvent::Z},

  {SDL_SCANCODE_LEFT, KeyboardEvent::LEFT},
  {SDL_SCANCODE_RIGHT, KeyboardEvent::RIGHT},
  {SDL_SCANCODE_UP, KeyboardEvent::UP},
  {SDL_SCANCODE_DOWN, KeyboardEvent::DOWN},

  {SDL_SCANCODE_F1, KeyboardEvent::F1},
  {SDL_SCANCODE_F2, KeyboardEvent::F2},
  {SDL_SCANCODE_F3, KeyboardEvent::F3},
  {SDL_SCANCODE_F4, KeyboardEvent::F4},
  {SDL_SCANCODE_F5, KeyboardEvent::F5},
  {SDL_SCANCODE_F6, KeyboardEvent::F6},
  {SDL_SCANCODE_F7, KeyboardEvent::F7},
  {SDL_SCANCODE_F8, KeyboardEvent::F8},
  {SDL_SCANCODE_F9, KeyboardEvent::F9},
  {SDL_SCANCODE_F10, KeyboardEvent::F10},
  {SDL_SCANCODE_F11, KeyboardEvent::F11},
  {SDL_SCANCODE_F12, KeyboardEvent::F12},
};

/*
Modifier KeyboardEvent::key_modifier(Uint16 modifier){
  switch (modifier){
    case KMOD_CAPS:
      return KeyboardEvent::CAPS;

    case KMOD_SHIFT:
      return KeyboardEvent::SHIFT;

    case KMOD_ALT:
      return KeyboardEvent::ALT;

    case KMOD_CTRL:
      return KeyboardEvent::CONTROL;

    default:
      return KeyboardEvent::NONE;
  }
}
*/
