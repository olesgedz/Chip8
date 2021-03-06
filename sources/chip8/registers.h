//
// Created by olesg on 9/12/2021.
//

#pragma once
#ifndef INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
#define INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
#include <cstring>
#include "config.h"
class Registers {

 public:
  Registers()
  {
	stack_pointer = 0;
	program_counter = 0;
	i = 0;
	delay_timer = 0;
	sound_timer = 0;
	memset(v, 0, sizeof(unsigned char) * CHIP8_TOTAL_DATA_REGISTERS);
  }
  unsigned short  get_pc() const;
  unsigned char  get_sp() const;
  void sp_add() { stack_pointer++;};
  void sp_dec() { stack_pointer--;};

  unsigned char delay_timer;
  unsigned char sound_timer;
  unsigned short program_counter;
  unsigned char stack_pointer;
  unsigned char v[CHIP8_TOTAL_DATA_REGISTERS]; // restrict vF
  unsigned short i;
 private:

};

#endif //INC_8BITEMU_SOURCES_CHIP8_REGISTERS_H_
