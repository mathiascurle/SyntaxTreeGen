#include "Tree.hpp"
#include "raylib.h"

Tree::Node::Node() {}
Tree::Node::Node(const char *x) {
  data = x;
}
Tree::Node::~Node() {}

Tree::Tree() {
  m_root = new Node("root");
}
Tree::~Tree() {
  delete m_root;
}

void Tree::drawTree() const {}
void Tree::dragNodes(const Vector2 mouseDeltaPos) {}
bool Tree::selectNode(const Vector2 mousePos) {
  if (CheckCollisionPointRec(mousePos, m_root->bounds)) {
    m_selectedNodes.push_back(m_root);
    return true;
  }
  return false;
}
bool Tree::hasSelectedNodes() { return !m_selectedNodes.empty(); }
bool Tree::isDraggingNodes() { return m_bDraggingNodes; }
void Tree::setDraggingNodes(const bool b) { m_bDraggingNodes = b; }
bool Tree::isDoingBoxSelect() { return m_bDoingBoxSelect; }
void Tree::setDoingBoxSelect(const bool b) { m_bDoingBoxSelect = b; }
