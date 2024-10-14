#include "SentenceTree.h"

SentenceTree::SentenceTree()
{
  head = NULL;
  size = 0;
}

void SentenceTree::push_back(Word x)
{
  Node *newNode = new Node(x);
  if (head == NULL)
  {
    head = newNode;
    return;
  }
  newNode->left = head;
  head->parent = newNode;
}

void SentenceTree::pop_back()
{
}

void SentenceTree::draw(Vector2 pos)
{

}


SentenceTree::Node::Node()
{
  parent = NULL;
  left   = NULL;
  right  = NULL;
}

SentenceTree::Node::Node(Word x)
{

}
