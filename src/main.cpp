#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "Grid.h"
#include "TreeStructure.h"
#include "SyntaxTree.h"

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

  GridSpace::initGrid(fWinWidth, fWinHeight, 20);

  Camera2D camera;
  camera.target = Vector2 {fWinWidth/2.f, fWinHeight/2.f};
  // camera.target = Vector2 {50.f, (fWinHeight-60)/2.f}; // for ImGui on right
  camera.offset = camera.target;
  // camera.target = Vector2 {0, 0};
  // camera.offset = Vector2 {0, 0};
  camera.rotation = 0;
  camera.zoom = 0.7;

  string sentence;
  string currentSentence = "The quick brown fox";

  // Containers
  SyntaxTree::Tree tree;
  vector<WordNode> wordNodes(1);
  vector<WordClassNode> wordClassNodes(1);
  vector<PhraseNode> phraseNodes(1);
  phraseNodes[0].setPos({100, 100});
  phraseNodes[0].setSize({20, 20});

  float winWidthImGui = 300;
  int iTypingPos = currentSentence.size();
  Rectangle sentenceRec = {0, fWinHeight-60.f, fWinWidth-winWidthImGui, 60};
  bool bIsTyping = false;
  bool showDemoWindow = false;
  /*int selectedWord = 0;*/
  /*static float selectedWordPos[2] = {wordNodes[selectedWord].getPos()->x, wordNodes[selectedWord].getPos()->y};*/

  Font font = GetFontDefault();
  char phraseBuffer[255] = "";

  float deleteTimer = 0; 
  float deleteSpeedTimer = 0; 
  float cursorTimer = 0;
  float idleTypingTimer = 0;

  Vector2 vCurrentPos;
  Vector2 vDeltaPos;
  Vector2 vDeltaPosCamera;
  Vector2 vMousePrevPos;


  while (!WindowShouldClose())
  {
    // camera.target.x = (*GridSpace::getWidth()/2)-300;
    // camera.target.y = (*GridSpace::getHeight()/2)-60;
    // screen = 1000-300, 600-60
    // grid = 1000, 600
    // fit grid to screen
    // camera.target = Vector2 {0, 0};
    // camera.offset = Vector2Add(camera.target, {20, (fWinHeight-60-(*GridSpace::getHeight()*camera.zoom))/2});

    // Update
    if (IsWindowResized())
    {
      fWinWidth = GetScreenWidth();
      fWinHeight = GetScreenHeight();
      sentenceRec = {0, fWinHeight-60.f, fWinWidth-winWidthImGui, 60};
      // float x = fWinWidth / fDefaultWinWidth;
      // float y = fWinHeight / fDefaultWinHeight;
      // camera.zoom = x - 0.4f;
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

      if (!tree.startDraggingNode(GetScreenToWorld2D(vCurrentPos, camera)) && IsKeyDown(KEY_LEFT_CONTROL))
        tree.resetSelected();

      // Start resizing
      int side = GridSpace::isOverResize(GetScreenToWorld2D(vCurrentPos, camera));
      if (side == 1)
        GridSpace::resizing = GridSpace::Resizing::Bottom;
      else if (side == 2)
        GridSpace::resizing = GridSpace::Resizing::Right;
    }

    if (bIsTyping)
    {
      // Writing
      int key = GetCharPressed();
      if (IsKeyPressed(KEY_LEFT) && iTypingPos > 0)
      {
        deleteTimer = GetTime();
        iTypingPos--;
        idleTypingTimer = GetTime();
      }
      else if (IsKeyDown(KEY_LEFT) && iTypingPos >0)
      {
        if ((GetTime() - deleteTimer) > 0.4f)
          if (GetTime() - deleteSpeedTimer > 0.08f)
          {
            iTypingPos--;
            deleteSpeedTimer = GetTime();
          }
        idleTypingTimer = GetTime();
      }
      else if (IsKeyPressed(KEY_RIGHT) && iTypingPos < currentSentence.size())
      {
        deleteTimer = GetTime();
        iTypingPos++;
        idleTypingTimer = GetTime();
      }
      else if (IsKeyDown(KEY_RIGHT) && iTypingPos < currentSentence.size())
      {
        if ((GetTime() - deleteTimer) > 0.4f)
          if (GetTime() - deleteSpeedTimer > 0.08f)
          {
            iTypingPos++;
            deleteSpeedTimer = GetTime();
          }
        idleTypingTimer = GetTime();
      }
      else if (IsKeyPressed(KEY_BACKSPACE))
      {
        deleteTimer = GetTime();
        if (currentSentence.size() > 0 && iTypingPos > 0)
          currentSentence.erase(-1 + iTypingPos--, 1);
      }
      else if (IsKeyDown(KEY_BACKSPACE))
      {
        if ((GetTime() - deleteTimer) > 0.4f)
          if (GetTime() - deleteSpeedTimer > 0.08f)
            if (currentSentence.size() > 0 && iTypingPos > 0)
            {
              currentSentence.erase(-1 + iTypingPos--, 1);
              deleteSpeedTimer = GetTime();
            }
        idleTypingTimer = GetTime();
      }
      else if (IsKeyDown(KEY_LEFT_SUPER) && IsKeyPressed(KEY_V))
      {
        string text = GetClipboardText();
        currentSentence.insert(iTypingPos, text);
        iTypingPos += text.size();
        idleTypingTimer = GetTime();
      }
      else if (key != 0)
      {
        currentSentence.insert(currentSentence.begin()+iTypingPos++, char(key));
        idleTypingTimer = GetTime();
      }
      if (IsKeyPressed(KEY_ENTER))
      {
        sentence = currentSentence;
        // // Word classes
        // for (int i = 0; i<wordNodes.size(); i++)
        // {
        //   wordClassNodes[i].setDataAuto(wordNodes[i].getData());
        //   wordClassNodes[i].setIndex(i);
        //   wordClassNodes[i].setPos(Vector2Add(*wordNodes[i].getPos(), {(wordNodes[i].getSize()->x/2)-(wordClassNodes[i].getSize()->x/2), -60.f}));
        //   wordNodes[i].setParent(&wordClassNodes[i]);
        // }
        tree.initSentence(sentence);
      }
    }
    else 
    {
      if (IsKeyPressed(KEY_C))
        tree.connectSelectedNodes();
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) || 
       (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL)))
    {
      camera.target = GetScreenToWorld2D(Vector2Add(camera.offset, vDeltaPos), camera);
    }
    else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
      if (!tree.dragNode(vDeltaPosCamera))
        if (GridSpace::resizing)
          GridSpace::resize(vDeltaPosCamera);
    }
    else
    {
      tree.resetDragging();
      if (GridSpace::resizing)
        GridSpace::resizing = GridSpace::Resizing::NONE;
    }


    
    // Draw
    BeginDrawing();
    ClearBackground(Color {40, 40, 40, 250});
    BeginMode2D(camera);

    GridSpace::draw();
    GridSpace::drawResizeLine(GetScreenToWorld2D(vCurrentPos, camera));
    
    tree.drawTree();

    // for (WordNode word : wordNodes)
    //   word.drawNode();
    //
    // for (WordClassNode node : wordClassNodes)
    //   node.drawNode();
    //
    // for (PhraseNode node : phraseNodes)
    //   node.drawNode();


    // DrawCircleV(camera.target, 20.f, RED);
    // DrawCircleV(camera.offset, 20.f, BLUE);

    EndMode2D();

    // DrawCircleV(camera.target, 10.f, RED);
    // DrawCircleV(camera.offset, 10.f, BLUE);

    // Sentece input
    DrawRectangleRec(sentenceRec, RAYWHITE);
    DrawRectangleLinesEx(sentenceRec, 5, (bIsTyping) ? RED : DARKGRAY);
    DrawTextEx(font, currentSentence.c_str(), Vector2{sentenceRec.x+10.f, sentenceRec.y+sentenceRec.height-45.f}, 30, 2, BLACK);
    if (bIsTyping)
    {
      if (GetTime() - cursorTimer >= 1 || GetTime() - idleTypingTimer <= 1)
        DrawLineEx({sentenceRec.x+MeasureTextEx(font, currentSentence.substr(0, iTypingPos).c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-45}, 
                   {sentenceRec.x+MeasureTextEx(font, currentSentence.substr(0, iTypingPos).c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-15}, 
                   2.f, BLACK);
        // DrawLineEx({sentenceRec.x+MeasureTextEx(font, currentSentence.c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-45}, 
        //            {sentenceRec.x+MeasureTextEx(font, currentSentence.c_str(), 30, 2).x+12, sentenceRec.y+sentenceRec.height-15}, 
        //            2.f, BLACK);
      if (GetTime() - cursorTimer >= 2)
        cursorTimer = GetTime();
    }

    // imgui
		rlImGuiBegin();

    #ifdef IMGUI_HAS_DOCK
		  ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
    #endif

    ImGui::SetNextWindowPos(ImVec2(fWinWidth-winWidthImGui, 0));
    ImGui::SetNextWindowSize(ImVec2(winWidthImGui, fWinHeight));

    if (ImGui::Begin("Side bar"))
    {
      if (ImGui::CollapsingHeader("Show/Hide"))
      {
        ImGui::Checkbox("Show Demo Window", &showDemoWindow);
        ImGui::Checkbox("Show grid", GridSpace::getShowGrid());
        ImGui::Checkbox("Show bounds", &SyntaxTree::s_bShowNodeBounds);
        ImGui::Checkbox("Show lines", &SyntaxTree::s_bShowLines);
      }
      if (ImGui::CollapsingHeader("Selected word"))
      {
        ImGui::TextUnformatted(tree.getSelectedWordData().c_str());
        if (ImGui::InputInt("Word index", tree.getSelectedWord()))
        {
          // selectedWordPos[0] = wordNodes[selectedWord].getPos()->x;
          // selectedWordPos[1] = wordNodes[selectedWord].getPos()->y;
        }
        // if (ImGui::DragFloat2("Word pos", selectedWordPos, 1.f, 0.0f, GetScreenWidth()))
        //   wordNodes[selectedWord].setPos(Vector2 {selectedWordPos[0], selectedWordPos[1]});
      }
      if (ImGui::CollapsingHeader("Selected phrase"))
      {
        /*ImGui::TextUnformatted(tree.getSelectedPhraseData().c_str());*/
        strcpy(phraseBuffer, tree.getSelectedPhraseData().c_str());
        if (ImGui::InputText("Phrase type", phraseBuffer, IM_ARRAYSIZE(phraseBuffer)))
        {
          tree.setSelectedPhraseData(phraseBuffer);
        }
        /*if (ImGui::Button("Connect to selected word"))*/
        /*  tree.connectWordToPhrase();*/
        if (ImGui::InputInt("Phrase index", tree.getSelectedPhrase()))
        {
        }
      }
      if (ImGui::CollapsingHeader("Node management"))
      {
        if (ImGui::Button("Connect selected nodes"))
          tree.connectSelectedNodes();
        if (ImGui::Button("Add phrase node"))
          tree.addPhraseNode();
        ImGui::Button("Add empty node");
      }
      if (ImGui::CollapsingHeader("Global vars"))
      {
        if (ImGui::InputInt("FontSize", &SyntaxTree::s_iFontSize))
        {
          // float tempX = 20;
          // float tempY = GetScreenHeight() -200;
          // for (int i = 0; i<wordNodes.size(); i++)
          // {
          //   wordNodes[i].autoSize();
          //   wordNodes[i].setPos(Vector2 {tempX, tempY});
          //   tempX += wordNodes[i].getSize()->x + 20;
          // }
        }
        ImGui::DragFloat("Global Y offest", &SyntaxTree::s_fGlobOffsetY, 1.f, -fWinHeight, fWinHeight);
      }
      if (ImGui::CollapsingHeader("Grid params"))
      {
        if (ImGui::DragFloat("Grid width", GridSpace::getWidth(), 1.f, 0, 2000) ||
            ImGui::DragFloat("Grid height", GridSpace::getHeight(), 1.f, 0, 2000))
          GridSpace::updateGrid();
      }
      if (ImGui::CollapsingHeader("Div debug"))
      {
        ImGui::Text("ImGui window width: %.2f", ImGui::GetWindowWidth());
        ImGui::Text("Camera zoom %.2f", camera.zoom);
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
        ImGui::Text("%i", iTypingPos);
        ImGui::Text("%c", currentSentence[iTypingPos-1]);
        ImGui::Text("Camera target x %.2f", camera.target.x);
        ImGui::Text("Camera target y %.2f", camera.target.y);
        ImGui::Text("Camera offset x %.2f", camera.offset.x);
        ImGui::Text("Camera offset y %.2f", camera.offset.y);
      }
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
