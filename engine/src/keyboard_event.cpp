#include "keyboard_event.hpp"

using namespace engine;

KeyboardEvent::KeyMap KeyboardEvent::keymap = {
  {SDLK_BACKSPACE, KeyboardEvent::BACKSPACE},
  {SDLK_TAB, KeyboardEvent::TAB},
  {SDLK_CLEAR, KeyboardEvent::CLEAR},
  {SDLK_RETURN, KeyboardEvent::RETURN},
  {SDLK_PAUSE, KeyboardEvent::PAUSE},
  {SDLK_ESCAPE, KeyboardEvent::ESCAPE},
  {SDLK_SPACE, KeyboardEvent::SPACE},
  {SDLK_EXCLAIM, KeyboardEvent::EXCLAIM},
  {SDLK_QUOTEDBL, KeyboardEvent::DOUBLE_QUOTE},
  {SDLK_HASH, KeyboardEvent::HASH},
  {SDLK_DOLLAR, KeyboardEvent::DOLLAR},

  {SDLK_AMPERSAND, KeyboardEvent::AMPERSAND},
  {SDLK_QUOTE, KeyboardEvent::QUOTE},
  {SDLK_LEFTPAREN, KeyboardEvent::LEFT_PARENTESIS},
  {SDLK_RIGHTPAREN, KeyboardEvent::RIGHT_PARENTESIS},
  {SDLK_ASTERISK, KeyboardEvent::ASTERISK},
  {SDLK_PLUS, KeyboardEvent::PLUS},
  {SDLK_COMMA, KeyboardEvent::COMMA},
  {SDLK_MINUS, KeyboardEvent::MINUS},
  {SDLK_PERIOD, KeyboardEvent::PERIOD},
  {SDLK_SLASH, KeyboardEvent::SLASH},

  {SDLK_0, KeyboardEvent::ZERO},
  {SDLK_1, KeyboardEvent::ONE},
  {SDLK_2, KeyboardEvent::TWO},
  {SDLK_3, KeyboardEvent::THREE},
  {SDLK_4, KeyboardEvent::FOUR},
  {SDLK_5, KeyboardEvent::FIVE},
  {SDLK_6, KeyboardEvent::SIX},
  {SDLK_7, KeyboardEvent::SEVEN},
  {SDLK_8, KeyboardEvent::EIGHT},
  {SDLK_9, KeyboardEvent::NINE},
  {SDLK_COLON, KeyboardEvent::COLON},
  {SDLK_SEMICOLON, KeyboardEvent::SEMICOLON},
  {SDLK_LESS, KeyboardEvent::LESS},
  {SDLK_EQUALS, KeyboardEvent::EQUALS},
  {SDLK_GREATER, KeyboardEvent::GREATER},

  {SDLK_QUESTION, KeyboardEvent::QUESTION},
  {SDLK_AT, KeyboardEvent::AT},
  {SDLK_LEFTBRACKET, KeyboardEvent::LEFT_BRACKET},
  {SDLK_BACKSLASH, KeyboardEvent::BACKSLASH},
  {SDLK_RIGHTBRACKET, KeyboardEvent::RIGHT_BRACKET},
  {SDLK_CARET, KeyboardEvent::CARET},
  {SDLK_UNDERSCORE, KeyboardEvent::UNDERSCORE},
  {SDLK_BACKQUOTE, KeyboardEvent::BACKQUOTE},
  {SDLK_DELETE, KeyboardEvent::DELETE},

  {SDLK_a, KeyboardEvent::A},
  {SDLK_b, KeyboardEvent::B},
  {SDLK_c, KeyboardEvent::C},
  {SDLK_d, KeyboardEvent::D},
  {SDLK_e, KeyboardEvent::E},
  {SDLK_f, KeyboardEvent::F},
  {SDLK_g, KeyboardEvent::G},
  {SDLK_h, KeyboardEvent::H},
  {SDLK_i, KeyboardEvent::I},
  {SDLK_j, KeyboardEvent::J},
  {SDLK_k, KeyboardEvent::K},
  {SDLK_l, KeyboardEvent::L},
  {SDLK_m, KeyboardEvent::M},
  {SDLK_n, KeyboardEvent::N},
  {SDLK_o, KeyboardEvent::O},
  {SDLK_p, KeyboardEvent::P},
  {SDLK_q, KeyboardEvent::Q},
  {SDLK_r, KeyboardEvent::R},
  {SDLK_s, KeyboardEvent::S},
  {SDLK_t, KeyboardEvent::T},
  {SDLK_u, KeyboardEvent::U},
  {SDLK_v, KeyboardEvent::V},
  {SDLK_w, KeyboardEvent::W},
  {SDLK_x, KeyboardEvent::X},
  {SDLK_y, KeyboardEvent::Y},
  {SDLK_z, KeyboardEvent::Z},

  {SDLK_LEFT, KeyboardEvent::LEFT},
  {SDLK_RIGHT, KeyboardEvent::RIGHT},
  {SDLK_UP, KeyboardEvent::UP},
  {SDLK_DOWN, KeyboardEvent::DOWN},

  {SDLK_F1, KeyboardEvent::F1},
  {SDLK_F2, KeyboardEvent::F2},
  {SDLK_F3, KeyboardEvent::F3},
  {SDLK_F4, KeyboardEvent::F4},
  {SDLK_F5, KeyboardEvent::F5},
  {SDLK_F6, KeyboardEvent::F6},
  {SDLK_F7, KeyboardEvent::F7},
  {SDLK_F8, KeyboardEvent::F8},
  {SDLK_F9, KeyboardEvent::F9},
  {SDLK_F10, KeyboardEvent::F10},
  {SDLK_F11, KeyboardEvent::F11},
  {SDLK_F12, KeyboardEvent::F12},
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
