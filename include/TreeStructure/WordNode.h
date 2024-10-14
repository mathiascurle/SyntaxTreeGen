#pragma once
#include "Node.h"

class WordNode : public Node
{
public:
  WordNode();
  WordNode(std::string word);

public:
  void setString(std::string str);
  void autoSize();
  void drawNode();
  void movePos(Vector2 delta);
  std::string* getData();

private:
  std::string m_sData;

};
