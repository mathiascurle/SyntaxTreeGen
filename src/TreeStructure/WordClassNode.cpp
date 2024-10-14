#include "WordClassNode.h"

WordClassNode::WordClassNode()
{
  m_dataEnum = None;
}

void WordClassNode::drawNode()
{
  if (s_bShowNodeBounds)
  {
    DrawRectangleV({m_vPos.x, m_vPos.y}, m_vSize, RAYWHITE);
    DrawRectangleLinesEx(Rectangle {m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y}, 2, BLACK);
  }
  DrawTextEx(GetFontDefault(), m_sData.c_str(), Vector2Add(m_vPos, {s_vTextOffset.x, s_vTextOffset.y}), s_iFontSize, s_iSpacing, BLACK);
}

void WordClassNode::setData(WordClassEnum wordClass)
{
  m_dataEnum = wordClass;
  switch (m_dataEnum) 
  {
    case Noun:
      m_sData = "N";
      break;
    case Verb:
      m_sData = "V";
      break;
    case Determiner:
      m_sData = "DT";
      break;
    case Adjective:
      m_sData = "Adj";
      break;
    case Adverb:
      m_sData = "Adv";
      break;
    case Preposition:
      m_sData = "P";
      break;
    default:
      m_sData = "?";
      break;
  }
  m_vSize = MeasureTextEx(GetFontDefault(), m_sData.c_str(), s_iFontSize, s_iSpacing);
  m_vSize.x += (s_vTextOffset.x + s_vTextOffset.x);
  m_vSize.y += (s_vTextOffset.y + s_vTextOffset.y-2);
}

void WordClassNode::setDataAuto(std::string* data)
{
  WordClassEnum wordClass = None;

  if 
    (
      *data == "The" || *data == "the" ||
      *data == "A" || *data == "a" || 
      *data == "An" || *data == "an" ||
      *data == "One" || *data == "one" ||
      *data == "Two" || *data == "two" ||
      *data == "Three" || *data == "three" ||
      *data == "Four" || *data == "four" ||
      *data == "Five" || *data == "five" ||
      *data == "Six" || *data == "six" ||
      *data == "Seven" || *data == "seven" ||
      *data == "Eight" || *data == "eight" ||
      *data == "Nine" || *data == "nine" ||
      *data == "Ten" || *data == "ten" ||
      *data == "Eleven" || *data == "eleven" ||
      *data == "Twelve" || *data == "twelve" ||
      *data == "Thirteen" || *data == "thirteen" ||
      *data == "Fourteen" || *data == "fourteen" ||
      *data == "Fifteen" || *data == "fifteen" ||
      *data == "Sixteen" || *data == "sixteen" ||
      *data == "Seventeen" || *data == "seventeen" ||
      *data == "Eighteen" || *data == "eighteen" ||
      *data == "Nineteen" || *data == "nineteen" ||
      *data == "Twenty" || *data == "twenty" ||
      *data == "Thirty" || *data == "thirty" ||
      *data == "Fourty" || *data == "fourty" ||
      *data == "Fifty" || *data == "fifty" ||
      *data == "Sixty" || *data == "sixty" ||
      *data == "Seventy" || *data == "seventy" ||
      *data == "Eighty" || *data == "eighty" ||
      *data == "Ninety" || *data == "ninety" ||
      *data == "Hundred" || *data == "hundred" ||
      *data == "Thousand" || *data == "thousand" ||
      *data == "Million" || *data == "million" ||
      *data == "Billion" || *data == "billion"
    )
    wordClass = Determiner;
  else if 
    (
      *data == "Aboard" || *data == "Aboard" ||
      *data == "About" || *data == "about" || 
      *data == "Above" || *data == "above" || 
      *data == "Across" || *data == "across" || 
      *data == "After" || *data == "after" || 
      *data == "Against" || *data == "against" || 
      *data == "Along" || *data == "along" || 
      *data == "Amid" || *data == "amid" || 
      *data == "Among" || *data == "among" || 
      *data == "Around" || *data == "around" || 
      *data == "As" || *data == "as" || 
      *data == "At" || *data == "at" || 
      *data == "Before" || *data == "aefore" || 
      *data == "Behind" || *data == "aehind" || 
      *data == "Below" || *data == "aelow" || 
      *data == "Beneath" || *data == "aeneath" || 
      *data == "Beside" || *data == "aeside" || 
      *data == "Besides" || *data == "aesides" || 
      *data == "Between" || *data == "aetween" || 
      *data == "Beyond" || *data == "aeyond" || 
      *data == "But" || *data == "aut" || 
      *data == "By" || *data == "ay" || 
      *data == "Concerning" || *data == "concerning" || 
      *data == "Considering" || *data == "considering" || 
      *data == "Despite" || *data == "despite" || 
      *data == "Down" || *data == "down" || 
      *data == "During" || *data == "during" || 
      *data == "Except" || *data == "except" || 
      *data == "Excepting" || *data == "excepting" || 
      *data == "Excluding" || *data == "excluding" ||
      *data == "Following" || *data == "following" ||
      *data == "For" || *data == "for" ||
      *data == "From" || *data == "from" ||
      *data == "In" || *data == "in" ||
      *data == "Inside" || *data == "inside" ||
      *data == "Into" || *data == "into" ||
      *data == "Like" || *data == "like" ||
      *data == "Minus" || *data == "minus" ||
      *data == "Near" || *data == "near" ||
      *data == "Of" || *data == "of" ||
      *data == "Off" || *data == "off" ||
      *data == "On" || *data == "on" ||
      *data == "Onto" || *data == "onto" ||
      *data == "Opposite" || *data == "opposite" ||
      *data == "Outside" || *data == "outside" ||
      *data == "Over" || *data == "over" ||
      *data == "Past" || *data == "past" ||
      *data == "Per" || *data == "per" ||
      *data == "Plus" || *data == "plus" ||
      *data == "Regarding" || *data == "regarding" ||
      *data == "Round" || *data == "round" ||
      *data == "Save" || *data == "dave" ||
      *data == "Since" || *data == "since" ||
      *data == "Than" || *data == "than" ||
      *data == "Through" || *data == "through" ||
      *data == "To" || *data == "to" ||
      *data == "Toward" || *data == "toward" ||
      *data == "Towards" || *data == "towards" ||
      *data == "Under" || *data == "under" ||
      *data == "Underneath" || *data == "underneath" ||
      *data == "Unlike" || *data == "unlike" ||
      *data == "Until" || *data == "until" ||
      *data == "Up" || *data == "up" ||
      *data == "Upon" || *data == "upon" ||
      *data == "Versus" || *data == "versus" ||
      *data == "Via" || *data == "via" ||
      *data == "With" || *data == "with" ||
      *data == "Within" || *data == "within" ||
      *data == "Without" || *data == "without"
    )
    wordClass = Preposition;

  setData(wordClass);
}

void WordClassNode::setIndex(int i)
{
  m_iIndex = i;
}
