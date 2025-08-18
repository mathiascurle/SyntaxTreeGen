#pragma once
#include "raylib.h"

// TODO: Fix world to screen stuff with resizing
// TODO: Snapping to grid function

namespace GridSpace {

void initGrid(Rectangle rect, int size);
void draw();
void update();

void drawResizeLine(Vector2 mousePos);
void resize();

inline Rectangle bounds;
inline float iSize;
inline bool bShowGrid;

inline Rectangle bottomLine;
inline Rectangle rightLine;
inline Rectangle bottomLineHitbox;
inline Rectangle rightLineHitbox;
inline Rectangle rightLowCornerBox;

enum Resizing {
  NONE = 0,
  Bottom = 1,
  Right = 2,
  Both = 3,
};
inline Resizing resizing;

} // namespace GridSpace
