//
// Created by olesg on 9/12/2021.
//

#include "stack.h"
#include <iostream>
#include <assert.h>

Stack::Stack(Registers &registers) : registers(registers) {

}

void Stack::push(unsigned short val) {
//  check_stack_bounds()
  stack[registers.get_sp()] = val;
  registers.sp_add();
}
unsigned short Stack::pop() {
  registers.sp_dec();
  check_stack_bounds();
  return stack[registers.get_sp()];
}
inline void Stack::check_stack_bounds() const{
  assert(registers.get_sp() >= 0 && registers.get_sp() < CHIP8_TOTAL_STACK_DEPTH); // cannot be negative
}
