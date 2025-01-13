#include "include/Chip-8.h"
#include <Chip-8.h>
#include <iostream>

Chip8 chip8;

int main() {
  chip8.init();
  chip8.loadGame("/Users/henok.tadesse.meta/Downloads/chip8-roms-master/"
                 "programs/IBMLogo.ch8");
  for (int i = 0; i < 10; i += 2) {
    chip8.emulateCycle();
  }

  return 0;
}
