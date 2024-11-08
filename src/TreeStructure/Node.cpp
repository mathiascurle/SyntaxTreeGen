#include "Node.h"
#include "raymath.h"

Node::Node()
{
  m_vPos = {0, 0};
  m_vSize = {0, 0};
}

void Node::setPos(Vector2 pos)
{
  m_vPos = pos;
}

void Node::setSize(Vector2 size)
{
  m_vSize = size;
}

void Node::movePos(Vector2 delta)
{
  m_vPos = Vector2Subtract(m_vPos, delta);
}

void Node::setParent(Node* parent)
{
  m_parent = parent;
}

Vector2* Node::getPos()
{
  return &m_vPos;
}

Vector2* Node::getSize()
{
  return &m_vSize;
}

Node* Node::getParent()
{
  return m_parent;
}

void Node::drawNode()
{
  if (s_bShowNodeBounds)
  {
    DrawRectangleV(m_vPos, m_vSize, RAYWHITE);
    DrawRectangleLinesEx(Rectangle {m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y}, 2, BLACK);
  }
  DrawTextEx(GetFontDefault(), m_sData.c_str(), Vector2Add(m_vPos, s_vTextOffset), s_iFontSize, s_iSpacing, BLACK);
  if (m_parent && s_bShowLines)
    drawLineToParent();
}

void Node::drawLineToParent()
{
  if (m_parent)
  {
  DrawLineEx({m_vPos.x+(m_vSize.x/2), m_vPos.y}, 
             {m_parent->getPos()->x+(m_parent->getSize()->x/2), 
              m_parent->getPos()->y+m_parent->getSize()->y}, 
              2.f, BLACK);
  }
}
