#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class Tree {
private:
  enum NodeType { WORD, POS, PHRASE, ROOT };

  class Node {
  public:
    Node(const char *data);
    Node();
    ~Node();

  public:
    NodeType type;
    std::string data = "";
    Node *parent;
    std::vector<Node *> m_children;

    Vector2 pos;
    Vector2 origin = {0, 0};
    Vector2 size = {20, 20};
    Rectangle bounds;
  };

public:
  Tree();
  ~Tree();
  void drawTree() const;
  void updateTree();
  void initSentence(std::string data);
  void addPhraseNode(Vector2 pos = {20, 20});
  void eraseSelectedNode();

  void addToSelectedNodes(Node *node);
  void resetSelectedNodes();
  void connectSelectedNodes();
  Node *startDraggingNode(Vector2 pos);
  bool dragNode(Vector2 delta);
  void resetDragging();
  void resetSelected();

  std::string getSelectedWordData();
  std::string getSelectedPhraseData();
  int *getSelectedWord();
  int *getSelectedPhrase();

  std::string *getSelectedNodeString();
  Rectangle *getSelectedNodeBounds();

  void setSelectedPhraseData(char *data);
  void autoSizeSelectedPhrase();

  void posTagSentence(const std::string &sentence);

private:
  Node *m_root;
  std::vector<Node *> m_selectedNodes;
};
