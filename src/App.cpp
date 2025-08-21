#include "App.hpp"

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#include "Grid.h"
#include "Typing.h"
#include "gui.hpp"
#include "shared_data.hpp"

/*
* TING Å GJØRE/FIKSE/ENDRE
* en string for å representere inputBox
* LinkedList for wordNodes
* Trestruktur
* Funksjon for å gjøre en operasjon på alle noder,
*   som tar en funksjon som parameter.
*   DFS og/eller BFS
*   Eventuelt bare et template for DFS/BFS
* Relasjon mellom Typing, Globals, Tree, etc
*/

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
  Globals.tree.update();
  Typing::update();
  // if (Typing::isTyping()) {
  //   Typing::moveCursor();
  //   Typing::deleteAtCursor();
  //   Typing::writeAtCursor();
  //   if (IsKeyPressed(KEY_ENTER)) {
  //     Globals.loadedSentence = Globals.currentSentence;
  //   }
  // }
}

void App::draw() const {
  BeginDrawing();
  {
    ClearBackground(DARKGRAY);
    BeginMode2D(Globals.camera);
    {
      GridSpace::draw();
      Globals.tree.draw();
      Typing::drawInWorld();
    }
    EndMode2D();
    Typing::drawStatic();
    Gui::draw();
  }
  EndDrawing();
}

///////////////////////////////////////////////////////////////////////////////

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
  // Typing::setWorkingString(&Globals.currentSentence, &Globals.inputBox);
  SetTextureFilter(Globals.fontData.font.texture, TEXTURE_FILTER_BILINEAR);
  GridSpace::initGrid(
      {0, 0, Globals.config.fViewWidth, Globals.config.fWinHeight}, 20);
  Globals.tree.init();
  Typing::inputBox = {0, Globals.config.fWinHeight - 50.f, Globals.config.fWinWidth, 50};
}

void App::shutdown() {
  UnloadFont(Globals.fontData.font);
  rlImGuiShutdown();
  CloseWindow();
}
