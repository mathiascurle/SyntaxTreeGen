#include "Tree.hpp"
#include "Grid.hpp"
#include "shared_data.hpp"

Tree::Tree() {}

Tree::~Tree() {
  // Iteratively delete all parents/grandparents of word nodes
  Node *current;
  for (int i = 0; i < sentence.size(); i++) {
    // printf("At %i: \n", i);
    current = sentence.get(i);
    while (current != m_root && current != nullptr) {
      Node *temp = current;
      current = current->parent;
      // printf("Deleting: %s\n", temp->data.c_str());
      delete temp;
    }
  }
  delete m_root;
}

void Tree::init() {
  m_root = new Node("root", ROOT, {GridSpace::iSize, GridSpace::iSize});
  // sentence.push_back(new Node("Hello", WORD, {10, 50}, m_root));
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

void Tree::setNewSentence() {
  // Update loadedSentence
  Globals.loadedSentence = Globals.currentSentence;
  // Empty the list of words
  while (sentence.size() != 0) {
    // sentence.pop();
    printf("Popped %s\n", sentence.pop()->data.c_str());
  }
  // Seperate words at ' ' and fill list
  Vector2 vPos = {GridSpace::iSize, GridSpace::bounds.y + GridSpace::bounds.height - 100};
  for (int pos = 0, npos = 0; pos < Globals.loadedSentence.size();) {
    npos = Globals.loadedSentence.find(' ', pos);
    if (npos == Globals.loadedSentence.npos)
      npos = Globals.loadedSentence.size(); // if end of sentence
    std::string word = Globals.loadedSentence.substr(pos, npos-pos);
    sentence.push_back(new Node(word.c_str(), WORD, vPos, m_root));
    pos = (pos < npos) ? npos : pos + 1;
    vPos.x += MeasureTextEx(Globals.fontData.font, word.c_str(),
                            Globals.fontData.size, Globals.fontData.spacing)
                  .x + 20;
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
