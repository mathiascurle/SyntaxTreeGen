#include "Grid.h"
#include "raylib.h"
#include "shared_data.hpp"

void GridSpace::initGrid(Rectangle rect, int size) {
  bounds.x = rect.x;
  bounds.y = rect.y;
  bounds.width = rect.width;
  bounds.height = rect.height;
  iSize = size;

  resizing = NONE;

  bShowGrid = true;
  bottomLine = {-10, bounds.height, bounds.width + 20, 10};
  rightLine = {bounds.width, -10, 10, bounds.height + 20};
  bottomLineHitbox = {bottomLine.x, bottomLine.y - 10, bottomLine.width,
                      bottomLine.height + 20};
  rightLineHitbox = {rightLine.x - 10, rightLine.y, rightLine.width + 20,
                     rightLine.height};
  rightLowCornerBox = {bounds.x+bounds.width-10, bounds.y+bounds.height-10, 30, 30};
}

void GridSpace::update() {
  if (Globals.mouse.leftPressed) { // Started dragging
    if (CheckCollisionPointRec(Globals.mouse.worldPos, rightLowCornerBox))
      resizing = Both;
    else if (CheckCollisionPointRec(Globals.mouse.worldPos, bottomLineHitbox))
      resizing = Bottom;
    else if (CheckCollisionPointRec(Globals.mouse.worldPos, rightLineHitbox))
      resizing = Right;
  } else if (!Globals.mouse.leftDown && resizing != NONE) { // Stop dragging
    resizing = NONE;
  }

  if (resizing != NONE) { // Resize
    resize();
  }
}

void GridSpace::draw() {
  DrawRectangleRec(bounds, RAYWHITE);
  DrawRectangleLinesEx(Rectangle{bounds.x - 10, bounds.y - 10,
                                 bounds.width + 20.f, bounds.height + 20.f},
                       10.f, BLACK);
  if (bShowGrid) {
    int row = 0;
    int col = 0;
    while (row <= bounds.height) {
      DrawLine(bounds.x, bounds.y + row, bounds.x + bounds.width,
               bounds.y + row, GRAY);
      row += iSize;
    }
    while (col <= bounds.width) {
      DrawLine(bounds.x + col, bounds.y, bounds.x + col,
               bounds.y + bounds.height, GRAY);
      col += iSize;
    }
  }

  if (resizing == Both) {
    DrawRectangleRec(rightLowCornerBox, RED);
  } else if (resizing == Bottom)
    DrawRectangleRec(bottomLine, RED);
  else if (resizing == Right)
    DrawRectangleRec(rightLine, RED);
}

void GridSpace::resize() {
  if (resizing == Bottom)
    bounds.height += Globals.mouse.deltaPos.y;
  else if (resizing == Right)
    bounds.width += Globals.mouse.deltaPos.x;
  else if (resizing == Both) {
    bounds.width += Globals.mouse.deltaPos.x;
    bounds.height += Globals.mouse.deltaPos.y;
  }

  bottomLine.y = bounds.height;
  bottomLineHitbox.y = bottomLine.y - 10;
  rightLine.height = bounds.height + 20;
  rightLineHitbox.height = rightLine.height;

  rightLine.x = bounds.width;
  rightLineHitbox.x = rightLine.x - 10;
  bottomLine.width = bounds.width + 20;
  bottomLineHitbox.width = bottomLine.width;
  rightLowCornerBox = {bounds.x+bounds.width-10, bounds.y+bounds.height-10, 30, 30};
}
