#include "Typing.h"
#include "raylib.h"
#include "shared_data.hpp"

void Typing::update() {
  // Move cursor
  // Delete at cursor
  // Write at cursor
  if (Globals.mouse.leftPressed) {
    if (CheckCollisionPointRec(Globals.mouse.pos, inputBox)) {
      bIsTyping = true;
    } else {
      bIsTyping = false;
    }
  }

  if (bIsTyping) {
    if (IsKeyPressed(KEY_ENTER)) {
      Globals.tree.setNewSentence(Globals.currentSentence);
    }
    // Deletion
    else if (IsKeyPressed(KEY_BACKSPACE)) {
      if (IsKeyDown(KEY_LEFT_CONTROL)) {
        // Delete word
        if (Globals.currentSentence.size()) {
          int pos = Globals.currentSentence
                        .substr(0, cursorPos.sentenceIdx -
                                       ((cursorPos.sentenceIdx == 0) ? 0 : 1))
                        .rfind(' ');
          if (pos != Globals.currentSentence.npos) {
            Globals.currentSentence.erase(pos, cursorPos.sentenceIdx-1);
            cursorPos.sentenceIdx = pos;
          } else {
            Globals.currentSentence = "";
            cursorPos.sentenceIdx = 0;
          }
        }
      } else {
        // Delete one character
        if (Globals.currentSentence.size())
          Globals.currentSentence.erase(--cursorPos.sentenceIdx);
      }
    } else if (IsKeyDown(KEY_BACKSPACE)) {
      // Continuous deletion with timer
    }
    // Moving left/right
    else if (IsKeyPressed(KEY_LEFT)) {
      if (IsKeyDown(KEY_LEFT_CONTROL)) {
        int pos = Globals.currentSentence
                      .substr(0, cursorPos.sentenceIdx -
                                     ((cursorPos.sentenceIdx == 0) ? 0 : 1))
                      .rfind(' ');
        if (pos >= 0 && pos <= Globals.currentSentence.size())
          cursorPos.sentenceIdx = pos + 1;
        else if (pos == Globals.currentSentence.npos)
          cursorPos.sentenceIdx = 0;
      } else {
        cursorPos.sentenceIdx -= (cursorPos.sentenceIdx <= 0) ? 0 : 1;
      }
    } else if (IsKeyDown(KEY_LEFT)) {
    } else if (IsKeyPressed(KEY_RIGHT)) {
      if (IsKeyDown(KEY_LEFT_CONTROL)) {
        // Fix this to actually find first character of next word
        int pos = Globals.currentSentence.find(' ', cursorPos.sentenceIdx);
        if (pos > 0 && pos <= Globals.currentSentence.size())
          cursorPos.sentenceIdx = pos + 1;
        else if (pos == Globals.currentSentence.npos)
          cursorPos.sentenceIdx = Globals.currentSentence.size();
      } else {
        cursorPos.sentenceIdx +=
            (cursorPos.sentenceIdx >= Globals.currentSentence.size()) ? 0 : 1;
      }
    } else if (IsKeyDown(KEY_RIGHT)) {
    }
    // Writing
    else {
      int key = GetCharPressed();
      if (key != 0) {
        Globals.currentSentence.insert(Globals.currentSentence.begin() +
                                           cursorPos.sentenceIdx++,
                                       char(key));
      }
    }
  }
}

void Typing::drawInWorld() {}

void Typing::drawStatic() {
  drawInputBox();
  drawCursor();
  // Draw bounds
}

void Typing::drawInputBox() {
  DrawRectangleRec(inputBox, RAYWHITE);
  DrawRectangleLinesEx(inputBox, 2.f, (Typing::bIsTyping) ? RED : BLACK);

  DrawTextEx(Globals.fontData.font, Globals.currentSentence.c_str(),
             {inputBox.x + 10, inputBox.y + 5}, Globals.fontData.bigSize,
             Globals.fontData.spacing, BLACK);
}

void Typing::drawCursor() {
  Rectangle measure = getCursorCoords();
  DrawLineEx({measure.x, measure.y}, {measure.width, measure.height}, 2.f,
             BLACK);
}

Rectangle Typing::getCursorCoords() {
  std::string substring =
      Globals.currentSentence.substr(0, cursorPos.sentenceIdx);
  Vector2 measure =
      MeasureTextEx(Globals.fontData.font, substring.c_str(),
                    Globals.fontData.bigSize, Globals.fontData.spacing);
  return {Typing::inputBox.x + measure.x + 12,
          Typing::inputBox.y + Typing::inputBox.height * 0.2f,
          Typing::inputBox.x + measure.x + 12,
          Typing::inputBox.y + Typing::inputBox.height * 0.8f};
}

/*
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
               // Typing::s_bounds->y+Typing::s_bounds->height-45},
               {Typing::s_bounds->x + measure.x + 12,
                Typing::s_bounds->y + Typing::s_bounds->height * 0.8f},
               // Typing::s_bounds->y+Typing::s_bounds->height-15},
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
  // cout<<"Is typing - "<<(s_bIsTyping ? "yes" : "no")<<endl;
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
*/
