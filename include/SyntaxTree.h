#pragma once
#include "Grid.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace SyntaxTree
{

enum PhraseTypes
{
  NP, VP, AdjP, AdvP, PP
};

enum NodeType
{
  WORD, POS, PHRASE, ROOT
};


inline int s_iFontSize = 32;
inline int s_iSpacing = 2;
inline Vector2 s_vTextPadding = {10, 5};

inline float s_fGlobOffsetY;
inline bool  s_bShowNodeBounds = true;
inline bool  s_bShowLines = false;
inline bool  s_bShowHighlights = true;


class Node
{
protected:
  Node() = default;
  Node(string data);

public:
  void drawNode();
  void drawNode(bool isSelected);
  void drawHighlight();
  void autoSize();
  void movePos(Vector2 delta);

  void setData(string data);
  void setOrigin(Vector2 pos);
  void setPos(Vector2 pos);
  void setSize(Vector2 size);
  void setParent(Node* parent);

  Vector2* getPos();
  Vector2* getSize();
  Vector2  getTopV();
  Vector2  getBotV();
  string   getData();
  string*  getDataPtr();
  Node*    getParent();
  NodeType getNodeType();
  Rectangle* getBounds();

  bool hasParent();
  void addChild(Node* node);

protected:
  Vector2  m_vOrigin {0,0};
  Vector2  m_vPos;
  Vector2  m_vSize = {20,20};
  Rectangle m_bounds;
  string   m_sData = "";
  Node*    m_parent;
  NodeType m_nodeType;

  vector<Node*> m_children;
};


class PoS : public Node
{
public:
  PoS();
};


class Word : public Node
{
public:
  Word(Node* root = NULL);

public:
  PoS m_PoS;
};


class NonLeaf : public Node
{
protected:
  NonLeaf() = default;
  NonLeaf(string data);
};


class Phrase : public NonLeaf
{
public:
  Phrase(Node* root = NULL);
  Phrase(string data);
};


class Root : public Node
{
public:
  Root();
  /*void addChild(Phrase* phraseNode);*/
  Node* getChild(int pos);
  bool hasChildren();

/*private:*/
/*  vector<Node*> m_children;*/
};



class Tree
{
public:
  Tree();
  void drawTree();
  void updateTree();
  void initSentence(string data);
  void addPhraseNode(Vector2 pos = {20, 20});
  void eraseSelectedNode();

  void addToSelectedNodes(Node* node);
  void resetSelectedNodes();
  void connectSelectedNodes();
  Node* startDraggingNode(Vector2 pos);
  bool dragNode(Vector2 delta);
  void resetDragging();
  void resetSelected();

  string getSelectedWordData();
  string getSelectedPhraseData();
  int*   getSelectedWord();
  int*   getSelectedPhrase();
  
  string* getSelectedNodeString();
  Rectangle* getSelectedNodeBounds();

  void setSelectedPhraseData(char* data);
  void autoSizeSelectedPhrase();

private:
  Root           m_root;
  vector<Phrase> m_phraseNodes;
  vector<PoS>    m_PoSNodes;
  vector<Word>   m_wordNodes;

  int   m_iSelectedWord = 0;
  int   m_iSelectedPhrase = 0;

  Node* m_firstSelectedNode = nullptr;
  Node* m_secondSelectedNode = nullptr;
  vector<Node*> m_selectedNodes;

  Node* m_draggingNode;
};


}
