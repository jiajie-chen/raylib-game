#ifndef COLLAPSE_RL_GAME_H_
#define COLLAPSE_RL_GAME_H_

#include <memory>

#include <flecs.h>
#include <raylib-cpp.hpp>

namespace collapse_rl
{

struct RenderableText {
  raylib::Color text_color_;
  std::string text_;
  int pos_x_;
  int pos_y_;
  int font_;
};

class Game
{
private:
  std::unique_ptr<raylib::Window> window_;
  std::unique_ptr<flecs::world> world_;
public:
  Game(int screen_width, int screen_height);
  ~Game() = default;
  void StartGameLoop(int fps);
};

} // namespace collapse_rl

#endif // COLLAPSE_RL_GAME_H_
