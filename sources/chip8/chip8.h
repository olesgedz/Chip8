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
#include "screen.h"

class Chip8 {
 public:
  Memory 	memory;
  Registers registers;
  Stack		stack;
  Keyboard 	keyboard;
  Screen	screen;
  Chip8();
  void exec(unsigned short opcode);
  void load(const char* buf, size_t size);
};

#endif //INC_8BITEMU_SOURCES_CHIP8_CHIP8_H_
