//
// Created by olesg on 9/12/2021.
//

#include "keyboard.h"
#include <assert.h>

static void keyboard_in_bounce(int key)
{
  assert(key >= 0 && key < CHIP8_TOTAL_KEYS);
}

int Keyboard::map_key(char key) {

  for (int i = 0; i < CHIP8_TOTAL_KEYS; i++)
  {
		if (keyboard_map[i] == key)
		{
		  return i;
		}
  }
  return -1;
}
void Keyboard::down(int key) {
  keyboard[key] = true;
}
void Keyboard::up(int key) {
  keyboard[key] = false;
}
bool Keyboard::is_pressed(int key) const {
  return keyboard[key];
}
