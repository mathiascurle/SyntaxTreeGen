#pragma once
#include "ConnectorNode.h"

enum PhraseTypes
{
  NP, VP, AdjP, AdvP, PP
};

class PhraseNode : public ConnectorNode
{
public:
  PhraseNode();
};
