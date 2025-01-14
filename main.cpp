#include "SDL2/SDL.h"
#include "include/Chip-8.h"
#include <Chip-8.h>
#include <iostream>

Chip8 chip8;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {

  chip8.init();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //  std::cerr << "Failed to initialize SDL: " << SDL_GetError() <<
    //  std::endl;
    return -1;
  }

  // Create SDL window
  SDL_Window *window = SDL_CreateWindow(
      "Moving Rectangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    //  std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return -1;
  }

  // Create SDL renderer
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    // std::cerr << "Failed to create renderer: " << SDL_GetError() <<
    // std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  // chip8.setupGraphics(window, renderer);

  chip8.loadGame("/Users/henok.tadesse.meta/Downloads/chip8-roms-master/"
                 "programs/IBMLogo.ch8");

  bool running = true;
  SDL_Event event;

  while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    for (int i = 0; i < 41; i += 2) {
      chip8.emulateCycle();

      if (chip8.drawFlag) {
        //   chip8.fakeDisplay();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int j = 1; j < 33; j++) {
          for (int i = 1; i < 65; i++) {
            if (chip8.gfx_values[(j * 64) + i] == '1') {
              SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
              SDL_Rect rect = {i * 10, j * 10, 10, 10}; // x, y, width, height
              SDL_RenderFillRect(renderer, &rect);
            } else {
              SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // White
              SDL_Rect rect = {i * 10, j * 10, 10, 10}; // x, y, width, height
              SDL_RenderFillRect(renderer, &rect);
            }
          }
        }

        // Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
      }
    }

    //   while (running) {
    //     // Handle events
    //     while (SDL_PollEvent(&event)) {
    //       if (event.type == SDL_QUIT) {
    //         running = false;
    //       }
    //     }

    //     // Clear screen
    //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //     SDL_RenderClear(renderer);

    //     for (int j = 1; j < 33; j++) {
    //       for (int i = 1; i < 65; i++) {
    //         if (chip8.gfx_values[(j * 64) + i] == '1') {
    //           SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    //           SDL_Rect rect = {i * 10, j * 10, 10, 10}; // x, y, width,
    //           height SDL_RenderFillRect(renderer, &rect);
    //         } else {
    //           SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // White
    //           SDL_Rect rect = {i * 10, j * 10, 10, 10};     // x, y, width,
    //           height SDL_RenderFillRect(renderer, &rect);
    //         }
    //       }
    //     }

    //     // Update screen
    //     SDL_RenderPresent(renderer);

    //     // Delay to control frame rate
    //     SDL_Delay(1); // ~60 FPS
  }

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
