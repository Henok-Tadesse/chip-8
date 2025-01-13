#include <Chip-8.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void Chip8::init() {
  // clear display
  for (int i = 0; i < 4096; i++) {
    memory[i] = 0;
  }

  // clear registers
  for (int i = 0; i < 16; i++) {
    V[i] = 0x0;
  }

  // clear display
  clearDisplay();
  // clear stack
  for (int i = 0; i < 16; i++) {
    stack[i] = 0x0;
  }

  pc = 0x200; // Program counter starts at 0x200 (512)
  opcode = 0;
  I = 0;
  sp = 0;
}

void Chip8::dump() {
  printf("I = %04X , pc = %d , opcode = %04X \n\n", I, pc, opcode);
  for (int i = 0; i < 5; i++) {
    printf("V%d = %d | ", i, V[i]);
  }
  printf("\n");
  for (int i = 6; i < 11; i++) {
    printf("V%d = %d | ", i, V[i]);
  }
  printf("\n");
  for (int i = 12; i < 16; i++) {
    printf("V%d = %d | ", i, V[i]);
  }
  printf("\n");
}

void Chip8::emulateCycle() {
  // Fetch
  // Decode
  // Execute
  printf("\n========\n");
  opcode_t currentOpCode = fetch();
  decode();
  dump();
  printf("\n========\n");
  // Decode
};

Chip8::opcode_t Chip8::fetch() {

  opcode = memory[pc] << 8 | memory[pc + 1]; // fetch opcode
  printf("Opcode: %04X\n", opcode);
  return opcode;
};

void Chip8::clearDisplay() {
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 31; j++) {
      gfx[i][j] = 0;
    }
  }
}

void Chip8::fillDisplaybuffer(int x, int y, int n) {
  printf("x: %d , y: %d, n: %d\n", x, y, n);
};

void Chip8::decode() {

  switch (opcode & 0xF000) {
  case 0xA000: // 0xAnnn
    printf("manupilating index\n");
    I = opcode & 0x0FFF;
    pc = pc + 2;
    break;
  case 0x6000:
    printf("Set Vx = kk\n");
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    pc = pc + 2;
    break;
  case 0xD000:
    printf("Display n-byte sprite starting at memory location\n");
    // jump to memory [I] and read values
    // the writing to buffer starts at x,y => gpx[64][32]
    printf("code: %d\n",
           (opcode &
            0x000F)); // cause we are casting it to int, it takes care of itself
    fillDisplaybuffer((opcode & 0x0F00), (opcode & 0x00F0) >> 4,
                      (opcode & 0x000F));
    break;
  case 0x0000:
    switch (opcode & 0x000F) {
    case 0x0000: // 0x00E0 , clear the screen
      printf("clear the screen\n");
      clearDisplay();
      pc = pc + 2;
      break;
    case 0x00E0: // 0x00EE: returns from subroutine
      printf("returns from subroutine\n");
      break;
    default:
      printf("don't know shit man\n");
      break;
    }
    break;
  default:
    printf("opcode not implemented yet\n");
    break;
  }
};

void Chip8::loadGame(std::filesystem::path filePath) {

  std::ifstream input(filePath, std::ios::binary);

  // copies all data into buffer
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input),
                                    {}); // gonna give fopen a try

  for (int i = 0; i < buffer.size() + 1; i++) {
    memory[pc + i] = buffer[i];
    program_size++;
    // memcpy( memory[i], , buffer.size() );
  }
};
