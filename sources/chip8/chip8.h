//
// Created by olesg on 9/11/2021.
//
#pragma once
#ifndef INC_8BITEMU_SOURCES_CHIP8_CHIP8_H_
#define INC_8BITEMU_SOURCES_CHIP8_CHIP8_H_
#include "config.h"
#include "memory.h"
#include "registers.h"
#include "stack.h"
#include "keyboard.h"

class Chip8 {
 public:
  Memory 	memory;
  Registers registers;
  Stack		stack;
  Keyboard keyboard;

  Chip8() : stack(registers)
  {
  }

};

#endif //INC_8BITEMU_SOURCES_CHIP8_CHIP8_H_
