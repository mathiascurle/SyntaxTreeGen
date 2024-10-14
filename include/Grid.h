#pragma once
#include "raylib.h"

namespace GridSpace 
{

void initGrid(int width, int height, int size);
void draw();
void drawResizeLine(Vector2 mousePos);
void resize(Vector2 delta);
void updateGrid();
void fitGridToScreen();

int isOverResize(Vector2 mousePos);
bool* getShowGrid();

float* getWidth();
float* getHeight();

inline float fWidth;
inline float fHeight;
inline float iSize;

inline bool bShowGrid;

inline Rectangle bottomLine;
inline Rectangle rightLine;
inline Rectangle bottomLineHitbox;
inline Rectangle rightLineHitbox;
  
enum Resizing
{
  NONE = 0, Bottom = 1, Right = 2
};
inline Resizing resizing;


}
