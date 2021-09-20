//
// Created by olesg on 9/12/2021.
//

#ifndef INC_8BITEMU_SOURCES_CHIP8_KEYBOARD_H_
#define INC_8BITEMU_SOURCES_CHIP8_KEYBOARD_H_
#include "config.h"
#include "SDL.h"

class Keyboard {

 public:
  bool  keyboard[CHIP8_TOTAL_KEYS];
  const char keyboard_map[CHIP8_TOTAL_KEYS] = {
	  SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
	  0x05, 0x06, 0x07, 0x08, 0x09,
	  SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f
  };
  int	map_key(char key);
  void  down(int key);
  void 	up(int key);
  bool  is_pressed(int key) const;
};

#endif //INC_8BITEMU_SOURCES_CHIP8_KEYBOARD_H_
