//
// Created by olesg on 9/20/2021.
//

#ifndef INC_8BITEMU_SOURCES_CHIP8_SCREEN_H_
#define INC_8BITEMU_SOURCES_CHIP8_SCREEN_H_

#include "config.h"

class Screen {
 public:
  Screen();
  bool pixels[CHIP8_HEIGHT * CHIP8_WIDTH];
  void set(int x, int y);
  bool get(int x, int y);

};

#endif //INC_8BITEMU_SOURCES_CHIP8_SCREEN_H_
