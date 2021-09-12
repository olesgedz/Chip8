//
// Created by olesg on 9/12/2021.
//
#include "registers.h"

unsigned short Registers::get_pc() const {
  return program_counter;
}
unsigned char Registers::get_sp() const {
  return stack_pointer;
}
