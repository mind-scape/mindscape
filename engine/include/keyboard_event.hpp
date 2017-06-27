#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include "event.hpp"

#include <SDL2/SDL.h>
#include <map>

namespace engine {

  class KeyboardEvent : public Event {
    public:
      typedef enum {PRESSED, RELEASED} State;

      typedef enum {
          BACKSPACE, TAB, CLEAR, RETURN, PAUSE, ESCAPE, SPACE, EXCLAIM,
          DOUBLE_QUOTE, HASH, DOLLAR, AMPERSAND, QUOTE, LEFT_PARENTESIS,
          RIGHT_PARENTESIS, ASTERISK, PLUS, COMMA, MINUS, PERIOD, SLASH, ZERO,
          ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, COLON, SEMICOLON,
          LESS, EQUALS, GREATER, QUESTION, AT, LEFT_BRACKET, BACKSLASH,
          RIGHT_BRACKET, CARET, UNDERSCORE, BACKQUOTE, DELETE, A, B, C, D, E, F,
          G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, LEFT,
          RIGHT, UP, DOWN, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
        } Key;

      typedef enum {NONE, SHIFT, CONTROL, ALT, CAPS} Modifier;

      typedef std::map<unsigned, Key> KeyMap;
      static KeyMap keymap;

      KeyboardEvent(unsigned timestamp, State key_state, unsigned pressed_key, bool p_was_repeated = false) :
        Event(timestamp), key_state(key_state), SDL_key(pressed_key), was_repeated(p_was_repeated) {}

      State state() const { return key_state; }
      Key key() const { return keymap[SDL_key]; }
      Modifier modifier() const { return m_modifier; }
      bool repeated() const { return was_repeated; }

    private:
      State key_state;
      unsigned SDL_key;
      Key m_key;
      Modifier m_modifier;
      bool was_repeated;
  };
}

#endif
