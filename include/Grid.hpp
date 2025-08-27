#pragma once
#include "raylib.h"

// TODO: Fix world to screen stuff with resizing
// TODO: Snapping to grid function

namespace GridSpace {

void initGrid(Rectangle rect, int size);
void draw();
void update();
void resize();

inline Rectangle bounds;
inline float iSize;

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

enum class GridType {
  NONE = 0,
  REGULAR = 1,
  BULLET = 2,
};
inline GridType gridType = GridType::REGULAR;

} // namespace GridSpace
