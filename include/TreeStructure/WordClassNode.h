#pragma once
#include "ConnectorNode.h"

enum WordClassEnum
{
  None = 0, Noun, Verb, Determiner, Adjective, 
  Adverb, Preposition, Modal
};

class WordClassNode : public ConnectorNode
{
public:
  WordClassNode();
  void drawNode();
  void setData(WordClassEnum wordClass);
  void setDataAuto(std::string* data);
  void setIndex(int i);

private:
  WordClassEnum m_dataEnum;
  std::string m_sData;
  int m_iIndex;
};
