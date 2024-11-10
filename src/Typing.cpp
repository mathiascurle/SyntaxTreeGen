#include "Typing.h"

void Typing::setWorkingString(string* str)
{
  Typing::s_string = str;
}

void Typing::moveCursor()
{
  if (IsKeyPressed(KEY_LEFT) && Typing::s_iTypingPos > 0)
  {
    Typing::s_fHoldTimer = GetTime();
    Typing::s_iTypingPos--;
    Typing::s_fIdleTypingTimer = GetTime();
  }
  else if (IsKeyDown(KEY_LEFT) && Typing::s_iTypingPos >0)
  {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f)
      {
        Typing::s_iTypingPos--;
        Typing::s_fHoldSpeedTimer = GetTime();
      }
    Typing::s_fIdleTypingTimer = GetTime();
  }
  else if (IsKeyPressed(KEY_RIGHT) && Typing::s_iTypingPos < Typing::s_string->size())
  {
    Typing::s_fHoldTimer = GetTime();
    Typing::s_iTypingPos++;
    Typing::s_fIdleTypingTimer = GetTime();
  }
  else if (IsKeyDown(KEY_RIGHT) && Typing::s_iTypingPos < Typing::s_string->size())
  {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f)
      {
        Typing::s_iTypingPos++;
        Typing::s_fHoldSpeedTimer = GetTime();
      }
    Typing::s_fIdleTypingTimer = GetTime();
  }
}

void Typing::deleteAtCursor()
{
  if (IsKeyPressed(KEY_BACKSPACE))
  {
    Typing::s_fHoldTimer = GetTime();
    if (Typing::s_string->size() > 0 && Typing::s_iTypingPos > 0)
      Typing::s_string->erase(-1 + Typing::s_iTypingPos--, 1);
  }
  else if (IsKeyDown(KEY_BACKSPACE))
  {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f)
        if (Typing::s_string->size() > 0 && Typing::s_iTypingPos > 0)
        {
          Typing::s_string->erase(-1 + Typing::s_iTypingPos--, 1);
          Typing::s_fHoldSpeedTimer = GetTime();
        }
    Typing::s_fIdleTypingTimer = GetTime();
  }
}
