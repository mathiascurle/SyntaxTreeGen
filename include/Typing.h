#pragma once
#include "raylib.h"
#include <string>
#include <iostream>
using namespace std;

namespace Typing 
{

inline bool  s_bIsTyping = false;
inline float s_fHoldTimer = 0; 
inline float s_fHoldSpeedTimer = 0; 
inline float s_fCursorTimer = 0;
inline float s_fIdleTypingTimer = 0;
inline int   s_iTypingPos = 0;

inline string* s_string;
inline Rectangle* s_bounds;


void drawCursor();
void drawSelectedBounds();
void setWorkingString(string* str, Rectangle* rect = nullptr);
void moveCursor();
void deleteAtCursor();
void writeAtCursor();

bool isTyping();
  
}
