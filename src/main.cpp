#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "Grid.h"
#include "TreeStructure.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;


int main()
{
  float fWinWidth = 1000;
  float fWinHeight = 600;
  float fDefaultWinWidth = fWinWidth;
  float fDefaultWinHeight = fWinHeight;
  int   iTargetFPS = 60;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(fWinWidth, fWinHeight, "Syntacic trees");
  SetTargetFPS(iTargetFPS);
  rlImGuiSetup(true);

  #ifdef IMGUI_HAS_DOCK
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  #endif

  Camera2D camera;
  camera.target = Vector2 {fWinWidth/2.f, fWinHeight/2.f};
  // camera.target = Vector2 {50.f, (fWinHeight-60)/2.f}; // for ImGui on right
  camera.offset = camera.target;
  camera.rotation = 0;
  camera.zoom = 0.7;

  GridSpace::initGrid(fWinWidth, fWinHeight, 20);

  string sentence;
  string currentSentence = "The quick brown fox jumps over the lazy dog";
  vector<WordNode> wordNodes(1);
  vector<WordClassNode> wordClassNodes(1);

  Rectangle sentenceRec = {0, fWinHeight-60.f, (float)fWinWidth, 60};
  bool bIsTyping = false;
  bool showDemoWindow = false;
  int selectedWord = 0;
  static float selectedWordPos[2] = {wordNodes[selectedWord].getPos()->x, wordNodes[selectedWord].getPos()->y};
  WordNode* draggingWordNode = NULL;

  Font font = GetFontDefault();

  float deleteTimer = 0; 
  float deleteSpeedTimer = 0; 
  float cursorTimer = 0;
  float idleTypingTimer = 0;

  Vector2 vCurrentPos;
  Vector2 vDeltaPos;
  Vector2 vDeltaPosCamera;
  Vector2 vMousePrevPos;

  float winWidthImGui = 0;

  while (!WindowShouldClose())
  {
    // Update
    if (IsWindowResized())
    {
      fWinWidth = GetScreenWidth();
      fWinHeight = GetScreenHeight();
      sentenceRec = {0, fWinHeight-60.f, (float)fWinWidth, 60};
      float x = fWinWidth / fDefaultWinWidth;
      // float y = fWinHeight / fDefaultWinHeight;
      camera.zoom = x - 0.3f;
    }

    vCurrentPos = GetMousePosition();
    vDeltaPos = Vector2Subtract(vMousePrevPos, vCurrentPos); 
    vDeltaPosCamera = Vector2Subtract(GetScreenToWorld2D(vMousePrevPos, camera), GetScreenToWorld2D(vCurrentPos, camera));
    vMousePrevPos = vCurrentPos;

    camera.zoom += ((float)GetMouseWheelMove()*0.01f);
    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.3f) camera.zoom = 0.3f;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))  
    {
      // Start typing
      if (CheckCollisionPointRec(vCurrentPos, sentenceRec))
        bIsTyping = true;
      else
        bIsTyping = false;
      
      // Start dragging word
      for (int i = 0; i<wordNodes.size(); i++)
      {
        if (CheckCollisionPointRec(GetScreenToWorld2D(vCurrentPos, camera), Rectangle{wordNodes[i].getPos()->x, wordNodes[i].getPos()->y, wordNodes[i].getSize()->x, wordNodes[i].getSize()->y}))
        {
          draggingWordNode = &wordNodes[i];
          selectedWord = i;
          selectedWordPos[0] = wordNodes[selectedWord].getPos()->x;
          selectedWordPos[1] = wordNodes[selectedWord].getPos()->y;
          break;
        }
      }
      // Start resizing
      int temp = GridSpace::isOverResize(GetScreenToWorld2D(vCurrentPos, camera));
      if (temp == 1)
        GridSpace::resizing = GridSpace::Resizing::Bottom;
      else if (temp == 2)
        GridSpace::resizing = GridSpace::Resizing::Right;
    }

    if (bIsTyping)
    {
      // Writing
      int key = GetCharPressed();
      if (IsKeyPressed(KEY_BACKSPACE))
      {
        deleteTimer = GetTime();
        if (currentSentence.size() > 0)
          currentSentence.pop_back();
      }
      else if (IsKeyDown(KEY_BACKSPACE))
      {
        if ((GetTime() - deleteTimer) > 0.4f)
          if (GetTime() - deleteSpeedTimer > 0.08f)
            if (currentSentence.size() > 0)
            {
              currentSentence.pop_back();
              deleteSpeedTimer = GetTime();
            }
        idleTypingTimer = GetTime();
      }
      else if (key != 0)
      {
        currentSentence.push_back(char(key));
        idleTypingTimer = GetTime();
      }
      if (IsKeyPressed(KEY_ENTER))
      {
        sentence = currentSentence;
        int wordCount = 1;
        for (char c : sentence)
          if (c == ' ') wordCount++;
        wordNodes.clear();
        wordNodes.resize(wordCount);
        string temp = "";
        int i = 0;
        float tempY = (*GridSpace::getHeight()*0.8f);
        s_fGlobOffsetY = 0;
        float tempX = 20;
        WordNode tempNode;
        for (char c : sentence)
        {
          if (c == ' ')
          {
            wordNodes[i].setString(temp);
            wordNodes[i].autoSize();
            wordNodes[i].setPos(Vector2 {tempX, tempY});
            tempX += wordNodes[i++].getSize()->x + 20;
            temp.clear();
          }
          else temp += c;
        }
        wordNodes[i].setString(temp);
        wordNodes[i].autoSize();
        wordNodes[i].setPos(Vector2 {tempX, tempY});

        // Word classes
        wordClassNodes.clear();
        wordClassNodes.resize(wordCount);
        for (int i = 0; i<wordNodes.size(); i++)
        {
          wordClassNodes[i].setDataAuto(wordNodes[i].getData());
          wordClassNodes[i].setIndex(i);
          wordClassNodes[i].setPos(Vector2Add(*wordNodes[i].getPos(), {(wordNodes[i].getSize()->x/2)-(wordClassNodes[i].getSize()->x/2), -60.f}));
          wordNodes[i].setParent(&wordClassNodes[i]);
        }
      }
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL))
    {
      camera.target = GetScreenToWorld2D(Vector2Add(camera.offset, vDeltaPos), camera);
    }
    else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
      if (draggingWordNode)
      {
        draggingWordNode->movePos(vDeltaPosCamera);
        selectedWordPos[0] = wordNodes[selectedWord].getPos()->x;
        selectedWordPos[1] = wordNodes[selectedWord].getPos()->y;
      }
      else if (GridSpace::resizing)
        GridSpace::resize(vDeltaPosCamera);
    }
    else
    {
      if (draggingWordNode)
        draggingWordNode = NULL;
      if (GridSpace::resizing)
        GridSpace::resizing = GridSpace::Resizing::NONE;
    }


    
    // Draw
    BeginDrawing();
    ClearBackground(Color {40, 40, 40, 250});
    BeginMode2D(camera);

    GridSpace::draw();
    GridSpace::drawResizeLine(GetScreenToWorld2D(vCurrentPos, camera));
    
    for (WordNode word : wordNodes)
      word.drawNode();

    for (WordClassNode node : wordClassNodes)
      node.drawNode();

    // DrawCircleV(camera.target, 20.f, RED);
    // DrawCircleV(camera.offset, 20.f, BLUE);

    EndMode2D();

    // Sentece input
    DrawRectangleRec(sentenceRec, RAYWHITE);
    DrawRectangleLinesEx(sentenceRec, 5, (bIsTyping) ? RED : DARKGRAY);
    DrawTextEx(font, currentSentence.c_str(), Vector2{sentenceRec.x+10.f, sentenceRec.y+sentenceRec.height-45.f}, 30, 2, BLACK);
    if (bIsTyping)
    {
      if (GetTime() - cursorTimer >= 1 || GetTime() - idleTypingTimer <= 1)
        DrawLineEx({sentenceRec.x+MeasureTextEx(font, currentSentence.c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-45}, 
                   {sentenceRec.x+MeasureTextEx(font, currentSentence.c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-15}, 
                   2.f, BLACK);
      if (GetTime() - cursorTimer >= 2)
        cursorTimer = GetTime();
    }

    // imgui
		rlImGuiBegin();

    #ifdef IMGUI_HAS_DOCK
		  ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
    #endif


    if (ImGui::Begin("Test Window"))
    {
      if (ImGui::CollapsingHeader("Show/Hide"))
      {
        // ImGui::Checkbox("Show Demo Window", &showDemoWindow);
        ImGui::Checkbox("Show grid", GridSpace::getShowGrid());
        ImGui::Checkbox("Show bounds", &s_bShowNodeBounds);
        ImGui::Checkbox("Show lines", &s_bShowLines);
      }
      if (ImGui::CollapsingHeader("Select word"))
      {
        ImGui::TextUnformatted(wordNodes[selectedWord].getData()->c_str());
        if (ImGui::InputInt("Selected word", &selectedWord))
        {
          selectedWordPos[0] = wordNodes[selectedWord].getPos()->x;
          selectedWordPos[1] = wordNodes[selectedWord].getPos()->y;
        }
        if (ImGui::DragFloat2("Word pos", selectedWordPos, 1.f, 0.0f, GetScreenWidth()))
          wordNodes[selectedWord].setPos(Vector2 {selectedWordPos[0], selectedWordPos[1]});
      }
      if (ImGui::CollapsingHeader("Global vars"))
      {
        if (ImGui::InputInt("FontSize", &s_iFontSize))
        {
          float tempX = 20;
          float tempY = GetScreenHeight() -200;
          for (int i = 0; i<wordNodes.size(); i++)
          {
            wordNodes[i].autoSize();
            wordNodes[i].setPos(Vector2 {tempX, tempY});
            tempX += wordNodes[i].getSize()->x + 20;
          }
        }
        ImGui::DragFloat("Global Y offest", &s_fGlobOffsetY, 1.f, -fWinHeight, fWinHeight);
      }
      if (ImGui::CollapsingHeader("Grid params"))
      {
        if (ImGui::DragFloat("Grid width", GridSpace::getWidth(), 1.f, 0, 2000) ||
            ImGui::DragFloat("Grid height", GridSpace::getHeight(), 1.f, 0, 2000))
          GridSpace::updateGrid();
      }
      winWidthImGui = ImGui::GetWindowWidth();
      ImGui::TextUnformatted(to_string(winWidthImGui).c_str());
      ImGui::TextUnformatted(to_string(camera.zoom).c_str());
      float width = fWinWidth;
      ImGui::Text("Window width: %.3f", width);
      camera.offset.x = (GetScreenWidth() - winWidthImGui) / 2;
      camera.offset.y = (GetScreenHeight() - sentenceRec.height) / 2;
      if (ImGui::DragFloat("Window width", &fWinWidth, 1.f, 100, 2000) ||
          ImGui::DragFloat("Window height", &fWinHeight, 1.f, 100, 2000))
      {
        if (fWinWidth >= 100 && fWinHeight >= 100)
        {
          SetWindowSize(fWinWidth, fWinHeight);
          fWinWidth = GetScreenWidth();
          fWinHeight = GetScreenHeight();
          sentenceRec = {0, fWinHeight-60.f, (float)fWinWidth, 60};
          float x = fWinWidth / fDefaultWinWidth;
          camera.zoom = x - 0.3f;
        }
      }
      if (ImGui::Button("Center camera"))
        camera.target = Vector2 {fWinWidth/2.f, fWinHeight/2.f};
    }
    ImGui::End();

    if (showDemoWindow)
      ImGui::ShowDemoWindow(&showDemoWindow);

		rlImGuiEnd();

    EndDrawing();
  }

	rlImGuiShutdown();
  CloseWindow();

}
