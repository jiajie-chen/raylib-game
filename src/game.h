#ifndef RAYLIB_ROGUELIKE_GAME_H_
#define RAYLIB_ROGUELIKE_GAME_H_

#include <flecs.h>

#include <memory>
#include <raylib-cpp.hpp>

namespace raylib_roguelike {

struct RenderableText {
  raylib::Color text_color_;
  std::string text_;
  int pos_x_;
  int pos_y_;
  int font_;
};

class Game {
 private:
  std::unique_ptr<raylib::Window> window_;
  std::unique_ptr<flecs::world> world_;

 public:
  Game(int screen_width, int screen_height);
  void StartGameLoop(int fps);
};

}  // namespace raylib_roguelike

#endif  // RAYLIB_ROGUELIKE_GAME_H_
