#include "Grid.h"

void GridSpace::initGrid(int width, int height, int size)
{
  fWidth = width;
  fHeight = height;
  iSize = size;

  resizing = NONE;

  bShowGrid = true;
  bottomLine = {-10, fHeight, fWidth+20, 10};
  rightLine = {fWidth, -10, 10, fHeight+20};
  bottomLineHitbox = {bottomLine.x, bottomLine.y-10, bottomLine.width, bottomLine.height+20};
  rightLineHitbox = {rightLine.x-10, rightLine.y, rightLine.width+20, rightLine.height};
}

void GridSpace::draw()
{
DrawRectangle(0, 0, fWidth, fHeight, RAYWHITE);
  DrawRectangleLinesEx(Rectangle {-10, -10, fWidth+20.f, fHeight+20.f}, 10.f, BLACK);
  if (bShowGrid)
  {
    int row = 0;
    int col = 0;
    while (row <= fHeight)
    {
      DrawLine(0, row, fWidth, row, GRAY); 
      row += iSize;
    }
    while (col <= fWidth)
    {
      DrawLine(col, 0, col, fHeight, GRAY); 
      col += iSize;
    }
  }
}

void GridSpace::drawResizeLine(Vector2 mousePos)
{
  if (isOverResize(mousePos) == 1 || resizing == Bottom)
    DrawRectangleRec(bottomLine, RED);

  if (isOverResize(mousePos) == 2 || resizing == Right)
    DrawRectangleRec(rightLine, RED);
}

void GridSpace::resize(Vector2 delta)
{
  if (resizing == Bottom)
    fHeight -= delta.y;
  else if (resizing == Right)
    fWidth -= delta.x;
  updateGrid();
}

void GridSpace::updateGrid()
{
  bottomLine.y = fHeight;
  bottomLineHitbox.y = bottomLine.y-10;
  rightLine.height = fHeight+20;
  rightLineHitbox.height = rightLine.height;

  rightLine.x = fWidth;
  rightLineHitbox.x = rightLine.x-10;
  bottomLine.width = fWidth+20;
  bottomLineHitbox.width = bottomLine.width;
}

void GridSpace::fitGridToScreen()
{
  fWidth = GetScreenWidth();
  fHeight = GetScreenHeight();

  bottomLine = {-10, fHeight, fWidth+20, 10};
  rightLine = {fWidth, -10, 10, fHeight+20};
  bottomLineHitbox = {bottomLine.x, bottomLine.y-10, bottomLine.width, bottomLine.height+20};
  rightLineHitbox = {rightLine.x-10, rightLine.y, rightLine.width+20, rightLine.height};
}

bool* GridSpace::getShowGrid()
{
  return &bShowGrid;
}

int GridSpace::isOverResize(Vector2 mousePos)
{
  if (CheckCollisionPointRec(mousePos, rightLineHitbox))
    return Resizing::Right;
  else if (CheckCollisionPointRec(mousePos, bottomLineHitbox))
    return Resizing::Bottom;
  else return Resizing::NONE;
}

float* GridSpace::getWidth()
{
  return &fWidth;
}

float* GridSpace::getHeight()
{
  return &fHeight;
}
