#include "Tree.hpp"
#include "shared_data.hpp"

Tree::Tree() {}

Tree::~Tree() {
  // Iteratively delete all parents/grandparents of word nodes
  Node *current;
  for (int i = 0; i < sentence.size(); i++) {
    current = sentence.get(i);
    while (current != m_root && current != nullptr) {
      Node *temp = current;
      current = current->parent;
      delete temp;
    }
  }
  delete m_root;
}

void Tree::init() {
  m_root = new Node("root", ROOT);
  sentence.push_back(new Node("", WORD, {10, 50}, m_root));
  // sentence.push_back(new Node("Hello", WORD, {10, 50}, m_root));
  // sentence.push_back(new Node("world", WORD, {100, 50}, m_root));
  // sentence.push_back(new Node("!", WORD, {200, 50}, m_root));
}

void Tree::draw() {
  LinkedList<Node *> q;
  q.push_back(m_root);
  int current = 0;
  while (current < q.size()) {
    for (int i = 0; i < q.get(current)->children.size(); i++) {
      if (q.get(current)->children.get(i)) {
        q.push_back(q.get(current)->children.get(i));
      }
    }
    q.get(current)->draw();
    // printf("Drew: %s\n", q.get(current)->data.c_str());
    current++;
  }
}

void Tree::update() {};

void Tree::updateBounds() { m_root->updateBounds(); }

void Tree::setNewSentence(const std::string_view &string) {
  // Update loadedSentence
  Globals.loadedSentence = string;
  // Empty the list of words
  while (sentence.size()) {
    sentence.pop();
  }
  // Seperate words at ' ' and fill list
  for (int pos, npos = 0; pos < string.size();) {
    npos = string.find(' ', pos);
    sentence.push_back(
        new Node(Globals.loadedSentence.substr(pos, npos).c_str()));
    pos = (pos < npos) ? pos : pos + 1;
  }
}

// void Tree::dragNodes(const Vector2 mouseDeltaPos) {}
// bool Tree::selectNode(const Vector2 mousePos) {
//   if (CheckCollisionPointRec(mousePos, m_root->bounds)) {
//     m_selectedNodes.push_back(m_root);
//     return true;
//   }
//   return false;
// }
// bool Tree::hasSelectedNodes() { return !m_selectedNodes.empty(); }
// bool Tree::isDraggingNodes() { return m_bDraggingNodes; }
// void Tree::setDraggingNodes(const bool b) { m_bDraggingNodes = b; }
// bool Tree::isDoingBoxSelect() { return m_bDoingBoxSelect; }
// void Tree::setDoingBoxSelect(const bool b) { m_bDoingBoxSelect = b; }
