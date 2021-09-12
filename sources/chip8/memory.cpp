//
// Created by olesg on 9/11/2021.
//

#include "memory.h"
#include <assert.h>
#include "config.h"

unsigned char Memory::get(int index) const {
  check_bounds(index); // not sure can be too slow
  return this->memory[index];
}

void Memory::set(int index, unsigned char val) {
  check_bounds(index);
  this->memory[index] = val;
}

void Memory::check_bounds(int index) const {
  assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}