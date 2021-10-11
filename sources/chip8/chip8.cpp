//
// Created by olesg on 9/11/2021.
//

#include "chip8.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
Chip8::Chip8() : stack(registers) {

}

void Chip8::exec(unsigned short opcode) {
  switch (opcode) {
	case 0x00E0:
	  screen.clear();
	  break;
	// Return from subroutine
	case 0x00EE:
	  registers.program_counter = stack.pop();
	  break;
	default:
	  exec_ext(opcode);
	  break;
  }
}

void Chip8::exec_ext(unsigned short opcode) {
  unsigned short nnn = opcode & 0x0fff;
  unsigned char x = (opcode >> 8) & 0x000f;
  unsigned char kk = opcode & 0x00ff;
  unsigned char y = (opcode >> 4) & 0x000f;
  unsigned char n =  opcode & 0x000f;
  unsigned short tmp = 0;
  switch (opcode & 0xf000) {
	//jmp to 1nnn
	case 0x1000:
	  registers.program_counter = nnn;
	  break;
    //call addr, 2nnn Call subroutine at location
	case 0x2000:
	  stack.push(registers.program_counter);
	  registers.program_counter = nnn;
	  break;
	//Skip next instruction if Vx = kk.
	case 0x3000:
	  if (registers.v[x] == kk)
	  {
		registers.program_counter += 2;
	  }
	  break;
	case 0x4000:
//	  Skip next instruction if Vx != kk.
	  if (registers.v[x] != kk)
	  {
		registers.program_counter += 2;
	  }
	  break;
	case 0x5000:
//	  Skip next instruction if Vx = Vy..
	  if (registers.v[x] == registers.v[y])
	  {
		registers.program_counter += 2;
	  }
	  break;
	case 0x6000:
//	  Set Vx = kk.
	  registers.v[x] = kk;
	  break;
	case 0x7000:
//	  Set Vx = Vx + kk.
	  registers.v[x] += kk;
	  break;
	case 0x8000:
	  switch (n) {
		//	  Set Vx = Vy.
		case 0x00:
		  registers.v[x] =  registers.v[y];
		  break;
		//	  Set Vx = Vx OR Vy.
		case 0x01:
		  registers.v[x] |=  registers.v[y];
		  break;
//		  Set Vx = Vx AND Vy.
		case 0x02:
		  registers.v[x] = registers.v[x] & registers.v[y];
		  break;
//		  Set Vx = Vx XOR Vy.
		case 0x03:
		  registers.v[x] = registers.v[x] ^ registers.v[y];
		  break;
		  //		 Set Vx = Vx + Vy, set VF = carry.
		case 0x04:
		  tmp =  registers.v[x] + registers.v[y];
		  registers.v[0x0f] = false;
		  if (tmp > 0xff) {

		  }
		  registers.v[x] = tmp;
		  break;
//		  Set Vx = Vx - Vy, set VF = NOT borrow.
		case 0x05:
		  registers.v[0x0f] = false;
		  if (registers.v[x]  > registers.v[y]) {
			registers.v[0x0f] = true;
		  }
		  registers.v[x] = registers.v[x] - registers.v[y];
		  break;
//		  Set Vx = Vx SHR 1.
		case 0x06:
		  registers.v[0x0f] = registers.v[x] & 0x01;
		  registers.v[x] /= 2;
		  break;
		  // Set Vx = Vy - Vx, set VF = NOT borrow.
		case 0x07:
		  registers.v[0x0f] = registers.v[y] > registers.v[x];
		  registers.v[x] = registers.v[y] - registers.v[x];
		  break;
//		  Set Vx = Vx SHL 1. Then Vx is multiplied by 2
		case 0x0E:
		  registers.v[0x0f] = registers.v[x] & 0b10000000;
		  registers.v[x] *= 2;
		  break;
	  };
	  break;
//	  Skip next instruction if Vx != Vy.
	case 0x9000:
	  if (registers.v[x] != registers.v[y])
		registers.program_counter += 2;
	  break;
//	  Set I = nnn.
	case 0xA000:
		registers.i = nnn;
	  break;
	  //	  Jump to location nnn + V0..
	case 0xB000:
	  registers.program_counter = nnn + registers.v[0x00];
	  break;
	  //	  Set Vx = random byte AND kk
	case 0xC000:
	  srand(clock());
	  registers.v[x] = (rand() % 255) & kk;
	  break;
	  // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
	case 0xD000: {
	  const  char* sprite = &memory.memory[registers.i];
	  registers.v[0x0f] = screen.draw_sprite(registers.v[x], registers.v[y], sprite, n);
	}
	  break;
	case 0xE000: {
	  switch (opcode & 0x00ff) {
//		Skip next instruction if key with the value of Vx is pressed.
		case 0x9e: {
		  if (keyboard.is_pressed(registers.v[x])) {
			registers.program_counter += 2;
		  }
		}
		  break;
//		Skip next instruction if key with the value of Vx is not pressed.
		case 0xA1: {
		  if (!keyboard.is_pressed(registers.v[x])) {
			registers.program_counter += 2;
		  }
		}
		  break;
	  }
	}
	  break;
	case 0xF000: {
	  switch (opcode & 0x00ff) {
//		Set Vx = delay timer value.
		case 0x07: {
		 registers.v[x] = registers.delay_timer;
		}
		  break;
		case 0x0A: {
		  SDL_Event event;
		  char c = -1;
		  while (SDL_WaitEvent(&event)) {
			if (event.type != SDL_KEYDOWN)
			  continue;
			c = keyboard.map_key(event.key.keysym.sym);
		  }
		  registers.v[x] = c;
		}
		  break;
	  }
	}
	  break;
  }
}

void Chip8::load(const char *buf, size_t size) {
  assert(size + CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
  memcpy(&memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
  registers.program_counter = CHIP8_PROGRAM_LOAD_ADDRESS;
}
