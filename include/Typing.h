#pragma once

#include "raylib.h"
#include <string>
using namespace std;

namespace Typing 
{

inline float s_fHoldTimer = 0; 
inline float s_fHoldSpeedTimer = 0; 
inline float s_fCursorTimer = 0;
inline float s_fIdleTypingTimer = 0;
inline int   s_iTypingPos = 0;

inline string* s_string;


void setWorkingString(string* str);
void moveCursor();
void deleteAtCursor();
  
}
