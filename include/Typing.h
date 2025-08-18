#pragma once
#include "raylib.h"
#include <string>

namespace Typing {

inline Font s_font;

inline bool s_bIsTyping = false;
inline float s_fHoldTimer = 0;       // Delay before typing held down key
inline float s_fHoldSpeedTimer = 0;  // Speed of typing held down key
inline float s_fCursorTimer = 0;     // Cursor blinking speed
inline float s_fIdleTypingTimer = 0; // Delay until cursor starts blinking
inline int s_iTypingPos = 0;         // Index of character under cursor

inline std::string *s_string; // Pointer to working string
inline Rectangle *s_bounds;   // Pointer to typing area bounds

void drawCursor();
void drawSelectedBounds();
void setWorkingString(std::string *str, Rectangle *rect = nullptr);
void moveCursor();
void deleteAtCursor();
void writeAtCursor();

bool isTyping();

} // namespace Typing
