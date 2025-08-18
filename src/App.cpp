#include "App.hpp"

#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "Grid.h"
#include "Tree.hpp"
#include "Typing.h"
#include "shared_data.hpp"
#include "gui.hpp"

void App::init() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(Globals.config.fWinWidth, Globals.config.fWinHeight,
             "SyntaxTreeGen");
  SetTargetFPS(Globals.config.iTargetFPS);
  rlImGuiSetup(true);

#ifdef IMGUI_HAS_DOCK
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

  InitGlobals();
  SetTextureFilter(Globals.font.texture, TEXTURE_FILTER_BILINEAR);
  GridSpace::initGrid({0, 0, Globals.config.fViewWidth, Globals.config.fWinHeight}, 20);
}

void App::shutdown() {
  UnloadFont(Globals.font);
  rlImGuiShutdown();
  CloseWindow();
}

void App::run() {
  init();
  while (!WindowShouldClose()) {
    update();
    draw();
  }
  shutdown();
}

void App::update() {
  updateMouse();
  GridSpace::update();
}

void App::draw() {
  BeginDrawing(); {
    ClearBackground(DARKGRAY);
    BeginMode2D(Globals.camera); {
      GridSpace::draw();
      tree.drawTree();
      // if (Typing::isTyping() && bIsTypingNode) {
      //   Typing::drawCursor();
      //   Typing::drawSelectedBounds();
      // }
    }
    EndMode2D();
    Gui::draw();
  } EndDrawing();
}
