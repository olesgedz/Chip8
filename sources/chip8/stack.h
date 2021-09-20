//
// Created by olesg on 9/12/2021.
//
#define pragma once
#ifndef INC_8BITEMU_SOURCES_CHIP8_STACK_H_
#define INC_8BITEMU_SOURCES_CHIP8_STACK_H_
#include "config.h"
#include "registers.h"
class Stack {
 public:
  Stack(Registers &registers);

  unsigned short stack[CHIP8_TOTAL_STACK_DEPTH];

  void push(unsigned short val);
  unsigned short pop();
 private:
  inline void check_stack_bounds() const;
  Registers &registers;
};

#endif //INC_8BITEMU_SOURCES_CHIP8_STACK_H_
