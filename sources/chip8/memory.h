//
// Created by olesg on 9/11/2021.
//
#pragma once
#ifndef INC_8BITEMU_SOURCES_CHIP8_MEMORY_H_
#define INC_8BITEMU_SOURCES_CHIP8_MEMORY_H_
#include "config.h"

class Memory {

 public:
  unsigned char memory[CHIP8_MEMORY_SIZE];
  void set(int index, unsigned char val);
  unsigned char get(int index) const;
  const unsigned char *GetMemory() const;

 private:
 inline void check_bounds(int index) const;
};

#endif //INC_8BITEMU_SOURCES_CHIP8_MEMORY_H_
