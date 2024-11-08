#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>

class Node
{
protected:
  Node();

public:
  void setPos(Vector2 pos);
  void setSize(Vector2 size);
  void movePos(Vector2 delta);
  void setParent(Node* parent);

  Vector2* getPos();
  Vector2* getSize();
  Node*    getParent();

  void drawNode();
  void drawLineToParent();

protected:
  Vector2 m_vPos;
  Vector2 m_vSize;

  std::string m_sData = "";

  Node* m_parent;
};


inline int s_iSpacing = 2;
inline int s_iFontSize = 32;
inline Vector2 s_vTextOffset = {5, 5};

inline float s_fGlobOffsetY;
inline bool  s_bShowNodeBounds = true;
inline bool  s_bShowLines = false;
