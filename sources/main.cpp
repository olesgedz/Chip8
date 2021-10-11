#include <iostream>
#include "SDL.h"
#include "chip8/chip8.h"
#include <assert.h>
#include <chrono>

void test_memory()
{
  Chip8 chip8;

  chip8.memory.set(0, 'Z');
  std::cout << chip8.memory.get(50) << std::endl;
}

void test_registers()
{
  Chip8 chip8;
  chip8.stack.push(0xff);
  chip8.stack.push(0xaa);
  std::cout << chip8.stack.pop() << std::endl;
  std::cout << chip8.stack.pop() << std::endl;
}

void test_keyboard()
{
  Chip8 chip8;
  chip8.keyboard.down(0x0f);
  assert(chip8.keyboard.is_pressed(0x0f));
  chip8.keyboard.up(0x0f);
  assert(!chip8.keyboard.is_pressed(0x0f));
  printf("%x\n", chip8.keyboard.map_key(0x08));
}

int main(int argc, char *argv[]) {
//  if (argc < 2) {
//	std::cout << "usage: ./8bitemu rom" << std::endl;
//	return -1;
//  }

  FILE* f = fopen("resources/INVADERS", "rb");
  if (!f) {
	std::cout << "fail to open" << std::endl;
	return -1;
  }
  fseek(f, 0, SEEK_END);
  long  size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* buf = new char [size];
  int res = fread(buf, size, 1, f);
  if (res != 1) {
	std::cout << "fail to open" << std::endl;
	return -1;
  }


  Chip8 chip8;
  chip8.load(buf, size);

  chip8.screen.draw_sprite(62,30, &chip8.memory.memory[0x00], 5);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow(
	  EMULATOR_WINDOW_TITLE,
	  SDL_WINDOWPOS_UNDEFINED,
	  SDL_WINDOWPOS_UNDEFINED,
	  CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
	  CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER,
	  SDL_WINDOW_SHOWN
  );
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
  SDL_Event event;

  uint64_t  delta_time = 0;
  uint64_t current_time = 0;
  uint64_t last = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  bool  sleep = false;
  while (1)
  {
	current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	delta_time = current_time - last;
	if (sleep = true) {
	  if (delta_time < 100)
		continue;
	  sleep = false;
	  last = current_time;
	}
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	  break;
	switch (event.type)
	{
	  case SDL_KEYDOWN:
	  {
		int key = chip8.keyboard.map_key(event.key.keysym.sym);
		if (key != -1)
		{
		  chip8.keyboard.down(key);
		}
	  }
		break;
	  case SDL_KEYUP:
	  {
		int key = chip8.keyboard.map_key(event.key.keysym.sym);
		if (key != -1)
		{
		  chip8.keyboard.up(key);
		}
	  }
		break;
	  default:
		break;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	for (int y = 0; y < CHIP8_HEIGHT; y++)
	{
	  for (int x = 0; x < CHIP8_WIDTH; x++)
	  {
		if (chip8.screen.get(x, y))
		{
		  SDL_Rect r;
		  r.x = x * CHIP8_WINDOW_MULTIPLIER;
		  r.y = y * CHIP8_WINDOW_MULTIPLIER;
		  r.w = CHIP8_WINDOW_MULTIPLIER;
		  r.h = CHIP8_WINDOW_MULTIPLIER;
		  SDL_RenderFillRect( renderer, &r);
		  SDL_RenderDrawRect(renderer, &r);
		}

	  }
	}
	SDL_RenderPresent(renderer);
	if (chip8.registers.delay_timer > 0) {
	  chip8.registers.delay_timer--;
	  sleep = true;
	}
	if (chip8.registers.sound_timer > 0) {
	  //Beep() no idea
//	  Beep(8000, 100 * chip8.registers.sound_timer ); //doesnt work for resons
	  chip8.registers.sound_timer = 0;
	}
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}