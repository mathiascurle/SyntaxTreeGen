#include "SyntaxTree.h"
using namespace SyntaxTree;

Node::Node(string data)
{
  m_sData = data;
  this->autoSize();
}

void Node::drawNode()
{
  if (s_bShowNodeBounds)
  {
    DrawRectangleV(m_vPos, m_vSize, RAYWHITE);
    DrawRectangleLinesEx(Rectangle {m_vPos.x, 
                                    m_vPos.y, 
                                    m_vSize.x, 
                                    m_vSize.y}, 
                         2, 
                         BLACK);
  }
  DrawTextEx(Typing::s_font, 
             m_sData.c_str(), 
             Vector2Add(m_vPos, s_vTextPadding),
             s_iFontSize, 
             s_iSpacing, 
             BLACK);
}

void Node::drawNode(bool isSelected)
{
  if (s_bShowNodeBounds)
  {
    DrawRectangleV(m_vPos, m_vSize, RAYWHITE);
    DrawRectangleLinesEx(Rectangle {m_vPos.x, 
                                    m_vPos.y, 
                                    m_vSize.x, 
                                    m_vSize.y}, 
                         (isSelected && s_bShowHighlights) ? 5 : 2, 
                         BLACK);
  }
  DrawTextEx(Typing::s_font, 
             m_sData.c_str(), 
             Vector2Add(m_vPos, s_vTextPadding),
             s_iFontSize, 
             s_iSpacing, 
             BLACK);
}

void Node::drawHighlight()
{
  DrawRectangleLinesEx(Rectangle {m_vPos.x, 
                                  m_vPos.y, 
                                  m_vSize.x, 
                                  m_vSize.y}, 
                       5, 
                       RED);
}

void Node::autoSize()
{
  Vector2 measure = MeasureTextEx(Typing::s_font,
                                  m_sData.c_str(),
                                  s_iFontSize,
                                  s_iSpacing);
  m_vSize.x = measure.x + (s_vTextPadding.x*2);
  m_vSize.y = measure.y + (s_vTextPadding.y*2);
  m_bounds.width = m_vSize.x;
  m_bounds.height = m_vSize.y;
}

void Node::setData(string data)
{
  m_sData = data;
  this->autoSize();
}

void Node::movePos(Vector2 delta)
{
  m_vPos = Vector2Subtract(m_vPos, delta);
  m_bounds.x = m_vPos.x;
  m_bounds.y = m_vPos.y;
}

void Node::setOrigin(Vector2 pos)
{
  m_vOrigin = pos;
  m_vPos = m_vOrigin;
}

void Node::setPos(Vector2 pos)
{
  m_vPos = pos;
  m_bounds.x = m_vPos.x;
  m_bounds.y = m_vPos.y;
}

void Node::setSize(Vector2 size)
{
  m_vSize = size;
}

void Node::setParent(Node* parent)
{
  m_parent = parent;
}

Vector2* Node::getPos()
{
  return &m_vPos;
}

Vector2* Node::getSize()
{
  return &m_vSize;
}

Vector2 Node::getTopV()
{
  return Vector2 {m_vPos.x + (m_vSize.x/2), m_vPos.y};
}

Vector2 Node::getBotV()
{
  return Vector2 {m_vPos.x + (m_vSize.x/2), m_vPos.y + m_vSize.y};
}

string Node::getData()
{
  return m_sData;
}


string* Node::getDataPtr()
{
  return &m_sData;
}

Node* Node::getParent()
{
  return m_parent;
}

NodeType Node::getNodeType()
{
  return m_nodeType;
}

Rectangle* Node::getBounds()
{
  return &m_bounds;
}

bool Node::hasParent()
{
  return m_parent;
}

void Node::addChild(Node* node)
{
  if (node)
    m_children.push_back(node);
}


PoS::PoS()
{
  m_nodeType = NodeType::POS;
}


Word::Word(Node* root)
{
  m_nodeType = NodeType::WORD;
  m_parent = root;
}


NonLeaf::NonLeaf(string data) : Node(data)
{
  m_vPos = {20, 20};
}


Phrase::Phrase(Node* root)
{
  m_nodeType = NodeType::PHRASE;
  m_parent = root;
}

Phrase::Phrase(string data) : NonLeaf(data)
{
  m_nodeType = NodeType::PHRASE;
}


Root::Root()
{
  m_nodeType = NodeType::ROOT;
  m_sData = "Sentence";
  this->autoSize();
  m_vPos = {20, 20};
  /*m_vPos = {(GetScreenWidth()/2)-(m_vSize.x/2), 20};*/
}

/*void Root::addChild(Phrase* phraseNode)*/
/*{*/
/*  m_children.push_back(phraseNode);*/
/*}*/

Node* Root::getChild(int pos)
{
  return m_children[pos];
}

bool Root::hasChildren()
{
  return m_children.size();
}





Tree::Tree()
{
}

void Tree::drawTree()
{
  m_root.drawNode(&m_root == m_firstSelectedNode);

  for (int i=0; i<m_wordNodes.size(); i++)
  {
    m_wordNodes[i].drawNode(&m_wordNodes[i] == m_firstSelectedNode);
    if (m_wordNodes[i].getParent())
      DrawLineEx(m_wordNodes[i].getTopV(), m_wordNodes[i].getParent()->getBotV(), 2, BLACK);
  }
  for (int i=0; i<m_phraseNodes.size(); i++)
  {
    m_phraseNodes[i].drawNode(&m_phraseNodes[i] == m_firstSelectedNode);
    if (m_phraseNodes[i].getParent())
      DrawLineEx(m_phraseNodes[i].getTopV(), m_phraseNodes[i].getParent()->getBotV(), 2, BLACK);
  }
}

void Tree::initSentence(string data)
{
  int wordCount = 1;
  for (char c : data)
    if (c == ' ') wordCount++;
  int i = 0;
  string temp = "";
  m_wordNodes.clear();
  m_wordNodes.resize(wordCount);
  float tempY = *GridSpace::getHeight() * 0.8f;
  float tempX = 20;
  for (char c : data)
  {
    if (c == ' ')
    {
      m_wordNodes[i].setData(temp);
      m_wordNodes[i].setOrigin(Vector2 {tempX, tempY});
      m_wordNodes[i].setParent(&m_root);
      tempX += m_wordNodes[i++].getSize()->x + 20;
      temp.clear();
    }
    else temp += c;
  }
  m_wordNodes[i].setData(temp);
  m_wordNodes[i].setOrigin(Vector2 {tempX, tempY});
  m_wordNodes[i].setParent(&m_root);

  tempX = m_wordNodes.front().getPos()->x;
  m_root.setOrigin({tempX + ((m_wordNodes.back().getPos()->x+m_wordNodes.back().getSize()->x-tempX)/2) - (m_root.getSize()->x/2) ,20});
}

void Tree::addPhraseNode(Vector2 pos)
{
  m_phraseNodes.emplace_back("phrase");
  m_phraseNodes.back().setPos(pos);
  if (m_firstSelectedNode)
  {
    m_phraseNodes.back().setParent(m_firstSelectedNode);
    m_firstSelectedNode->addChild(&m_phraseNodes.back());
  }
  else
  {
    m_phraseNodes.back().setParent(&m_root);
    m_root.addChild(&m_phraseNodes.back());
  }
}

void Tree::eraseSelectedNode()
{
  if (m_firstSelectedNode && m_iSelectedPhrase < m_phraseNodes.size())
  {
    m_phraseNodes.erase(m_phraseNodes.begin() + m_iSelectedPhrase);
  }
}

void Tree::addToSelectedNodes(Node* node)
{
  m_selectedNodes.push_back(node);
}

void Tree::resetSelectedNodes()
{
  m_selectedNodes.clear();
}

void Tree::connectSelectedNodes()
{
  if (!m_firstSelectedNode || !m_secondSelectedNode)
    return;
  int type1 = m_firstSelectedNode->getNodeType();
  int type2 = m_secondSelectedNode->getNodeType();
  if ((type1 == NodeType::WORD && type2 == NodeType::WORD) ||
      (m_firstSelectedNode == m_secondSelectedNode))
    return;

  if (m_firstSelectedNode->getPos()->y < m_secondSelectedNode->getPos()->y)
  {
    m_firstSelectedNode->addChild(m_secondSelectedNode);
    m_secondSelectedNode->setParent(m_firstSelectedNode);
  }
  else 
  {
    m_secondSelectedNode->addChild(m_firstSelectedNode);
    m_firstSelectedNode->setParent(m_secondSelectedNode);
  }
}

Node* Tree::startDraggingNode(Vector2 pos)
{
  Vector2 tempPos  = *m_root.getPos();
  Vector2 tempSize = *m_root.getSize();
  if (CheckCollisionPointRec(pos,
                             Rectangle{
                             tempPos.x, 
                             tempPos.y, 
                             tempSize.x, 
                             tempSize.y}))
  {
    m_draggingNode = &m_root;
    m_secondSelectedNode = m_firstSelectedNode;
    m_firstSelectedNode = m_draggingNode;
    return m_draggingNode;
  }

  for (int i = 0; i<m_wordNodes.size(); i++)
  {
    tempPos  = *m_wordNodes[i].getPos();
    tempSize = *m_wordNodes[i].getSize();
    if (CheckCollisionPointRec(pos,
                               Rectangle{
                               tempPos.x, 
                               tempPos.y, 
                               tempSize.x, 
                               tempSize.y}))
    {
      m_draggingNode = &m_wordNodes[i];
      m_iSelectedWord = i;
      m_secondSelectedNode = m_firstSelectedNode;
      m_firstSelectedNode = m_draggingNode;
      return m_draggingNode;
    }
  }

  for (int i = 0; i<m_phraseNodes.size(); i++)
  {
    tempPos  = *m_phraseNodes[i].getPos();
    tempSize = *m_phraseNodes[i].getSize();
    if (CheckCollisionPointRec(pos,
                               Rectangle{
                               tempPos.x, 
                               tempPos.y, 
                               tempSize.x, 
                               tempSize.y}))
    {
      m_draggingNode = &m_phraseNodes[i];
      m_iSelectedPhrase = i;
      m_secondSelectedNode = m_firstSelectedNode;
      m_firstSelectedNode = m_draggingNode;
      return m_draggingNode;
    }
  }
  return nullptr;
}

bool Tree::dragNode(Vector2 delta)
{
  if (!m_draggingNode)
    return false;
  m_draggingNode->movePos(delta);
  return true;
}

void Tree::resetDragging()
{
  if (m_draggingNode)
    m_draggingNode = nullptr;
}

void Tree::resetSelected()
{
  m_firstSelectedNode = nullptr;
  m_secondSelectedNode = nullptr;
}

string Tree::getSelectedWordData()
{
  if (m_iSelectedWord < m_wordNodes.size() && m_iSelectedWord >= 0)
    return m_wordNodes[m_iSelectedWord].getData();
  return "";
}

string Tree::getSelectedPhraseData()
{
  if (m_iSelectedPhrase < m_phraseNodes.size() && m_iSelectedPhrase >= 0)
    return m_phraseNodes[m_iSelectedPhrase].getData();
  return "";
}

int* Tree::getSelectedWord()
{
  return &m_iSelectedWord;
}

int* Tree::getSelectedPhrase()
{
  return &m_iSelectedPhrase;
}

string* Tree::getSelectedNodeString()
{
  if (m_firstSelectedNode)
    return m_firstSelectedNode->getDataPtr();
  return nullptr;
}

Rectangle* Tree::getSelectedNodeBounds()
{
  if (m_firstSelectedNode)
    return m_firstSelectedNode->getBounds();
  return nullptr;
}

void Tree::setSelectedPhraseData(char* data)
{
  m_phraseNodes[m_iSelectedPhrase].setData(data);
}

void Tree::autoSizeSelectedPhrase()
{
  if (m_firstSelectedNode)
    m_firstSelectedNode->autoSize();
}
