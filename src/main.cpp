#include <raylib-cpp.hpp>

#include "game.h"

int main() {
  raylib_roguelike::Game game(800, 450);
  game.StartGameLoop(60);
  return 0;
}
