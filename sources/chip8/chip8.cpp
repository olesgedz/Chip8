//
// Created by olesg on 9/11/2021.
//

#include "chip8.h"
#include <assert.h>
#include <stdlib.h>

Chip8::Chip8() : stack(registers) {

}

void Chip8::exec(unsigned short opcode) {

}

void Chip8::load(const char *buf, size_t size) {
  assert(size + CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
  memcpy(&memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
  registers.program_counter = CHIP8_PROGRAM_LOAD_ADDRESS;
}
