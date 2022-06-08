#pragma once

#include "raylib.h"
#include <math.h>

void DrawTimeBar(Music music, Vector2 mousePos, Vector2 screenSize);
bool DrawButtonPause(bool onPause, Vector2 mousePos, Vector2 screenSize);
float DrawSoundBar(Music music, float volume, Vector2 mousePos, Vector2 screenSize);