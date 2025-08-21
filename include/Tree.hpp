#pragma once
#include "LinkedList.hpp"
#include "raylib.h"
#include <string>

class Tree {
private:
  enum NodeType { NONE, WORD, POS, PHRASE, ROOT };

  class Node {
  public:
    Node(const char *_data = "null", NodeType _type = NONE, Vector2 _pos = {10, 10}, Node* _parent = nullptr);
    ~Node();
    void draw();
    void updateBounds();

  public:
    NodeType type;
    std::string data = "";
    Node *parent = nullptr;
    LinkedList<Node *> children;

    Rectangle bounds = {10, 10, 20, 20};
    Vector2 textOffset = {5.f, 2.5f};

    Vector2 topConnector;
    Vector2 bottomConnector;
  };

  // class WordNode : Node {
  // public:
  //   std::string partOfSpeech = "";
  // };

public:
  Tree();
  ~Tree();
  void init();
  void draw();
  void update();

  void updateBounds();
  void setNewSentence(const std::string_view& string);
  // void dragNodes(const Vector2 mouseDeltaPos);

  // bool selectNode(const Vector2 mousePos);
  // bool hasSelectedNodes();

  // bool isDraggingNodes();
  // void setDraggingNodes(const bool b);
  // bool isDoingBoxSelect();
  // void setDoingBoxSelect(const bool b);

  // void posTagSentence(const std::string &sentence);

public:
  LinkedList<Node*> sentence;

private:
  Node *m_root;

  // std::vector<Node *> m_selectedNodes;
  // Rectangle m_selectionRec;

  // bool m_bDraggingNodes;
  // bool m_bDoingBoxSelect;
};
