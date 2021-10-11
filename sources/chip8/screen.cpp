//
// Created by olesg on 9/20/2021.
//

#include <cstring>
#include "screen.h"
#include <assert.h>

static void screen_check_bounds(int x, int y) {
  assert(x >= 0 && x < CHIP8_WIDTH && y >= 0 && y < CHIP8_HEIGHT);
}

Screen::Screen() {
  memset(pixels, 0, sizeof(bool) * CHIP8_WIDTH * CHIP8_HEIGHT);
}
void Screen::set(int x, int y) {
  screen_check_bounds(x, y);
  pixels[x + y * CHIP8_WIDTH] = true;
}
bool Screen::get(int x, int y) {
  screen_check_bounds(x, y);
  return pixels[x + y * CHIP8_WIDTH];
}

bool Screen::draw_sprite(int x, int y, const unsigned char *sprite, int num) {
  bool pixel_collision = false;
  for (int ly = 0; ly < num; ly++) {
	char c = sprite[ly];
	for (int lx = 0; lx < 8; lx++) {
	  if ((c & (0b10000000 >> lx)) == 0) {
		continue;
	  }
	  pixels[((lx + x) % CHIP8_WIDTH)+ ((((ly + y) % CHIP8_HEIGHT) * CHIP8_WIDTH))] = true; // wrapping
	}
  }
  return pixel_collision;
}
