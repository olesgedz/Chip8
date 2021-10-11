//
// Created by olesg on 9/11/2021.
//

#include "memory.h"
#include <assert.h>
#include <iostream>
#include "config.h"

Memory::Memory() {
  memset(memory, 0, sizeof(unsigned char) * CHIP8_MEMORY_SIZE);
  memcpy(memory, default_character_set, sizeof(default_character_set) * sizeof(char));
}

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

unsigned short Memory::get_short(int index) {
  unsigned char byte1 = get(index);
  unsigned char byte2 = get(index + 1);
  return byte1 << 8 | byte2;
}
