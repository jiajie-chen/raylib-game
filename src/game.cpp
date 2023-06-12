#include "game.h"

#include <memory>

#include <flecs.h>
#include <raylib.h>
#include <raylib-cpp.hpp>

namespace collapse_rl
{

Game::Game(int screen_width, int screen_height) :
    window_ (std::make_unique<raylib::Window>(screen_width, screen_height, "Roguelike")),
    world_  (std::make_unique<flecs::world>())
{
  this->world_->entity("HelloWorldText")
    .set<RenderableText>({
      raylib::Color::LightGray(),
      "Congrats! You created your first window!",
      190, 200, 20
    });
  
  this->world_->entity("ExtraText")
    .set<RenderableText>({
      raylib::Color::Red(),
      "Hi :)",
      190, 225, 20
    });

  this->world_->system("PreRender")
    .kind(flecs::PreUpdate)
    .iter([this](flecs::iter& it) {
      ::BeginDrawing();
      this->window_->ClearBackground(RAYWHITE);
    });

  this->world_->system<const RenderableText>("Render")
    .kind(flecs::OnUpdate)
    .each([](const RenderableText& text) {
      text.text_color_.DrawText(
        text.text_,
        text.pos_x_, text.pos_y_, text.font_
      );
    });

  this->world_->system("PostRender")
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& it) {
      ::EndDrawing();
    });
}

void Game::StartGameLoop(int fps)
{
  /* Init */
  ::SetTargetFPS(fps);
  /* Game loop */
  while (!this->window_->ShouldClose()) {   // Detect window close button or ESC key
    this->world_->progress();
  }

  return;
}

} // namespace collapse_rl
