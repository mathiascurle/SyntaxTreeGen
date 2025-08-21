#include "Tree.hpp"
#include "raylib.h"
#include "shared_data.hpp"

Tree::Node::Node(const char *_data, NodeType _type, Vector2 _pos,
                 Node *_parent) {
  data = _data;
  parent = _parent;
  if (parent)
    parent->children.push_back(this);
  bounds.x = _pos.x;
  bounds.y = _pos.y;
  updateBounds();
}

Tree::Node::~Node() {
  if (parent) {
    // Remove parents pointer to this
    for (int i = 0; i < parent->children.size(); i++) {
      if (parent->children.get(i) == this) {
        parent->children.remove(i);
      }
    }
    if (children.size()) {
      // If node has a parent and children, connect them
      for (int i = 0; i < children.size(); i++) {
        children.get(i)->parent = parent;
        parent->children.push_back(children.get(i));
      }
    }
  }
}

void Tree::Node::draw() {
  DrawRectangleLinesEx(bounds, 2.f, BLACK);
  DrawTextEx(Globals.fontData.font, data.c_str(),
             {bounds.x + textOffset.x, bounds.y + textOffset.y},
             Globals.fontData.size, Globals.fontData.spacing, BLACK);
  DrawCircleV(topConnector, 4.f, BLUE);
  DrawCircleV(bottomConnector, 4.f, RED);

  // Draw line to children
  for (int i = 0; i < children.size(); i++) {
    DrawLineV(bottomConnector, children.get(i)->topConnector, BLACK);
  }
}

void Tree::Node::updateBounds() {
  // Make offset so that the middle of new node is where mouse is
  Vector2 size = MeasureTextEx(Globals.fontData.font, data.c_str(),
                               Globals.fontData.size, Globals.fontData.spacing);
  bounds.width = size.x + (textOffset.x * 2);
  bounds.height = size.y + (textOffset.y * 2);

  topConnector = {bounds.x + (bounds.width / 2), bounds.y};
  bottomConnector = {bounds.x + (bounds.width / 2), bounds.y + bounds.height};
}
