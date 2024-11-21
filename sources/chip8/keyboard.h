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
	  SDLK_1, SDLK_1, SDLK_2, SDLK_3,
  	  SDLK_q, SDLK_w, SDLK_e, SDLK_r,
  	  SDLK_a, SDLK_s, SDLK_d, SDLK_f,
  	  SDLK_z, SDLK_x, SDLK_c, SDLK_v
  };
	
  int	map_key(char key);
  void  down(int key);
  void 	up(int key);
  bool  is_pressed(int key) const;
};

#endif //INC_8BITEMU_SOURCES_CHIP8_KEYBOARD_H_
