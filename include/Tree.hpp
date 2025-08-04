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
  void dragNodes(const Vector2 mouseDeltaPos);

  bool selectNode(const Vector2 mousePos);
  bool hasSelectedNodes();

  bool isDraggingNodes();
  void setDraggingNodes(const bool b);
  bool isDoingBoxSelect();
  void setDoingBoxSelect(const bool b);

  // void posTagSentence(const std::string &sentence);

private:
  Node *m_root;
  std::vector<Node *> m_selectedNodes;

  Rectangle m_selectionRec;

  bool m_bDraggingNodes;
  bool m_bDoingBoxSelect;
};
