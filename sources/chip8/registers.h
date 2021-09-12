//
// Created by olesg on 9/12/2021.
//

#pragma once
#ifndef INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
#define INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
#include "config.h"
class Registers {

 public:
  Registers()
  {
	stack_pointer = 0;
	program_counter = 0;
  }
  unsigned short  get_pc() const;
  unsigned char  get_sp() const;
  void sp_add() { stack_pointer++;};
  void sp_dec() { stack_pointer--;};

 private:
  unsigned char v[CHIP8_TOTAL_DATA_REGISTERS]; // restrict vF
  unsigned short i;
  unsigned char delay_timer;
  unsigned char sound_timer;
  unsigned short program_counter;
  unsigned char stack_pointer;
};

#endif //INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
