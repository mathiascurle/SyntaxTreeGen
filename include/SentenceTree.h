#pragma once
#include <string>
#include "raylib.h"
using namespace std;

struct Word
{
  string  data;
  Vector2 pos;
  int     index;
};


class SentenceTree
{
public:
  SentenceTree();
  void push_back(Word x);
  void pop_back();
  void draw(Vector2 pos);

private:
  class Node;

private:
  Node *head;
  int   size;
};


class SentenceTree::Node
{
public:
  Node();
  Node(Word x);

public:
  Word  data;
  Node *parent;
  Node *left;
  Node *right;
};

//   void draw(Vector2 pos)
//   {
//     DrawTextEx(GetFontDefault(), origin.data.data.c_str(), pos, 20, 5, BLACK);
//   }
