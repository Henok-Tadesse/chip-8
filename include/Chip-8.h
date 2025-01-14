#pragma once

#include <filesystem>
#include <vector>

class Chip8 {

  typedef unsigned short opcode_t;

public:
  static void saySomething() { printf("I am saying something"); };
  void init();
  void loadGame(std::filesystem::path filePath);

  void emulateCycle();

  void clearDisplay();

  opcode_t fetch();

  void dump();

  void fillDisplaybuffer(int, int, int);

  void fakeDisplay();

  void decode();

  int program_size = 0;

  bool drawFlag;

private:
  unsigned char memory[4096];
  opcode_t opcode;
  unsigned char V[16];
  unsigned short I;
  unsigned short pc;
  unsigned char gfx[64 * 32]; // x,y
  unsigned char delay_timer;
  unsigned char sound_timer;
  unsigned short stack[16];
  unsigned short sp;
  unsigned char key[16];
  std::vector<char> gfx_values;
};
