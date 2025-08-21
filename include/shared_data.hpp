#pragma once
#include "Tree.hpp"
#include "LinkedList.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

#define DEFAULT_WIN_WIDTH 1000
#define DEFAULT_WIN_HEIGHT 600
#define DEFAULT_IMGUI_WIDTH 300
#define DEFAULT_FPS 60

typedef struct Mouse {
  Vector2 pos = {0.f, 0.f};
  Vector2 deltaPos = {0.f, 0.f};
  Vector2 worldPos = {0.f, 0.f};
  Vector2 worldDeltaPos = {0.f, 0.f};
  Vector2 screenPos = {0.f, 0.f};

  bool leftDown = false;
  bool leftPressed = false;
  bool rightDown = false;
  bool rightPressed = false;
} Mouse;

typedef struct Config {
  float fWinWidth = DEFAULT_WIN_WIDTH;
  float fWinHeight = DEFAULT_WIN_HEIGHT;
  float fDefaultWinWidth = DEFAULT_WIN_WIDTH;
  float winWidthImGui = DEFAULT_IMGUI_WIDTH;
  float fViewWidth = DEFAULT_WIN_WIDTH - DEFAULT_IMGUI_WIDTH;
  int iTargetFPS = DEFAULT_FPS;
} Config;

typedef struct FontData {
  Font font;
  float size = 30.f;
  float bigSize = 45.f;
  float spacing = 2.f;
} FontData;

typedef struct SharedData {
  Config config;
  Camera2D camera;
  Mouse mouse;
  FontData fontData;

  Tree tree;
  std::string loadedSentence;
  std::string currentSentence;
  Rectangle inputBox;
} SharedData;

inline SharedData Globals;

inline void InitGlobals() {
  Globals.currentSentence = "";
  Globals.inputBox = {0, Globals.config.fWinHeight - 60.f,
                      Globals.config.fViewWidth, 60};
  Globals.fontData.font =
      LoadFontEx("Fonts/Rethink_Sans/RethinkSans-Regular.ttf", 64, 0, 0);

  Globals.camera.target =
      Vector2{Globals.config.fViewWidth / 2.f, Globals.config.fWinHeight / 2.f};
  Globals.camera.offset = Globals.camera.target;
  Globals.camera.rotation = 0;
  Globals.camera.zoom = 0.7;
}

inline void updateMouse() {
  Globals.mouse.pos = GetMousePosition();
  Globals.mouse.deltaPos = GetMouseDelta();
  Globals.mouse.worldPos =
      GetScreenToWorld2D(Globals.mouse.pos, Globals.camera);
  Globals.mouse.worldDeltaPos = GetScreenToWorld2D(
      Vector2Add(Globals.mouse.pos, Globals.mouse.deltaPos), Globals.camera);
  Globals.mouse.screenPos =
      GetWorldToScreen2D(Globals.mouse.pos, Globals.camera);

  Globals.mouse.leftDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
  Globals.mouse.leftPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
  Globals.mouse.rightDown = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
  Globals.mouse.rightPressed = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
}
