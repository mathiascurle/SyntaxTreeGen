#include "WordNode.h"

WordNode::WordNode()
{
}

WordNode::WordNode(std::string word)
{
  m_sData = word;
}

void WordNode::setString(std::string str)
{
  m_sData.clear();
  m_sData.assign(str);
}

void WordNode::autoSize()
{
  m_vSize = MeasureTextEx(GetFontDefault(), m_sData.c_str(), s_iFontSize, s_iSpacing);
  m_vSize.x += (s_vTextOffset.x + s_vTextOffset.x);
  m_vSize.y += (s_vTextOffset.y + s_vTextOffset.y-2);
}

void WordNode::drawNode()
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

void WordNode::movePos(Vector2 delta)
{
  m_vPos = Vector2Subtract(m_vPos, delta);
  m_parent->movePos(delta);
}

std::string* WordNode::getData()
{
  return &m_sData;
}
