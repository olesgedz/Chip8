#include <iostream>
#include "SDL.h"
#include "chip8/chip8.h"

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

int main(int argc, char *argv[])
{
  Chip8 chip8;
  test_registers();
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

  while (1)
  {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	  break;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 40;
	r.h = 40;
	SDL_RenderDrawRect(renderer, &r);
	SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}