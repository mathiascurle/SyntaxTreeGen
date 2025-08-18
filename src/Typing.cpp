#include "Typing.h"

void Typing::drawCursor() {
  if (!s_string)
    return;
  if (GetTime() - Typing::s_fCursorTimer >= 1 ||
      GetTime() - Typing::s_fIdleTypingTimer <= 1) {
    Vector2 measure =
        MeasureTextEx(Typing::s_font,
                      s_string->substr(0, Typing::s_iTypingPos).c_str(), 32, 2);
    DrawLineEx({Typing::s_bounds->x + measure.x + 12,
                Typing::s_bounds->y + Typing::s_bounds->height * 0.2f},
               /*Typing::s_bounds->y+Typing::s_bounds->height-45}, */
               {Typing::s_bounds->x + measure.x + 12,
                Typing::s_bounds->y + Typing::s_bounds->height * 0.8f},
               /*Typing::s_bounds->y+Typing::s_bounds->height-15}, */
               2.f, BLACK);
  }
  if (GetTime() - Typing::s_fCursorTimer >= 2)
    Typing::s_fCursorTimer = GetTime();
}

void Typing::drawSelectedBounds() {
  if (s_bounds)
    DrawRectangleLinesEx(*s_bounds, 5, RED);
}

void Typing::setWorkingString(std::string *str, Rectangle *rect) {
  Typing::s_string = str;
  Typing::s_bounds = rect;
  Typing::s_bIsTyping = str || rect;
  if (s_bIsTyping)
    s_iTypingPos = s_string->size();
  /*cout<<"Is typing - "<<(s_bIsTyping ? "yes" : "no")<<endl;*/
}

void Typing::moveCursor() {
  if (!s_string)
    return;
  if (IsKeyPressed(KEY_LEFT) && Typing::s_iTypingPos > 0) {
    Typing::s_fHoldTimer = GetTime();
    Typing::s_iTypingPos--;
    Typing::s_fIdleTypingTimer = GetTime();
  } else if (IsKeyDown(KEY_LEFT) && Typing::s_iTypingPos > 0) {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f) {
        Typing::s_iTypingPos--;
        Typing::s_fHoldSpeedTimer = GetTime();
      }
    Typing::s_fIdleTypingTimer = GetTime();
  } else if (IsKeyPressed(KEY_RIGHT) &&
             Typing::s_iTypingPos < Typing::s_string->size()) {
    Typing::s_fHoldTimer = GetTime();
    Typing::s_iTypingPos++;
    Typing::s_fIdleTypingTimer = GetTime();
  } else if (IsKeyDown(KEY_RIGHT) &&
             Typing::s_iTypingPos < Typing::s_string->size()) {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f) {
        Typing::s_iTypingPos++;
        Typing::s_fHoldSpeedTimer = GetTime();
      }
    Typing::s_fIdleTypingTimer = GetTime();
  }
}

void Typing::deleteAtCursor() {
  if (!s_string)
    return;
  if (IsKeyPressed(KEY_BACKSPACE)) {
    Typing::s_fHoldTimer = GetTime();
    if (Typing::s_string->size() > 0 && Typing::s_iTypingPos > 0)
      Typing::s_string->erase(-1 + Typing::s_iTypingPos--, 1);
  } else if (IsKeyDown(KEY_BACKSPACE)) {
    if ((GetTime() - Typing::s_fHoldTimer) > 0.4f)
      if (GetTime() - Typing::s_fHoldSpeedTimer > 0.08f)
        if (Typing::s_string->size() > 0 && Typing::s_iTypingPos > 0) {
          Typing::s_string->erase(-1 + Typing::s_iTypingPos--, 1);
          Typing::s_fHoldSpeedTimer = GetTime();
        }
    Typing::s_fIdleTypingTimer = GetTime();
  }
}

void Typing::writeAtCursor() {
  if (!s_string)
    return;
  int key = GetCharPressed();
  if (key != 0) {
    Typing::s_string->insert(Typing::s_string->begin() + Typing::s_iTypingPos++,
                             char(key));
    Typing::s_fIdleTypingTimer = GetTime();
  }
}

bool Typing::isTyping() { return s_bIsTyping; }
