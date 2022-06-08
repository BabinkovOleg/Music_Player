#include "interface.h"
#include <stdio.h>

void DrawTimeBar(Music music, Vector2 mousePos, Vector2 screenSize) {
	DrawRectangle(screenSize.x / 10 - 1, screenSize.y * 8 / 10 - 1, screenSize.x * 8 / 10 + 2, screenSize.y / 50 + 2, BLACK);
	DrawRectangle(screenSize.x / 10, screenSize.y * 8 / 10, screenSize.x * 8 / 10, screenSize.y / 50, LIGHTGRAY);
	DrawRectangle(screenSize.x / 10, screenSize.y * 8 / 10, screenSize.x * 8 / 10 * GetMusicTimePlayed(music) / GetMusicTimeLength(music), screenSize.y / 50, GRAY);
	
	int playedMinutes = (int)GetMusicTimePlayed(music) / 60, PlayedSeconds = (int)GetMusicTimePlayed(music) % 60, TotalMinutes = (int)GetMusicTimeLength(music) / 60, TotalSeconds = (int)GetMusicTimeLength(music) % 60;
	DrawText(TextFormat("%d:%02d/%d:%02d", playedMinutes, PlayedSeconds, TotalMinutes, TotalSeconds), screenSize.x / 10, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50, 20, BLACK);
	
	if (CheckCollisionPointRec(mousePos, (Rectangle) { screenSize.x / 10, screenSize.y * 8 / 10, screenSize.x * 8 / 10, screenSize.y / 50 })) {
		DrawRectangle(screenSize.x / 10, screenSize.y * 8 / 10, mousePos.x - screenSize.x / 10, screenSize.y / 50, RED);
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			SeekMusicStream(music, GetMusicTimeLength(music) * (mousePos.x - screenSize.x / 10) / (screenSize.x * 8 / 10));
		}
	}
}

bool DrawButtonPause(bool onPause, Vector2 mousePos, Vector2 screenSize) {
	float pauseBtnWidth = screenSize.x / 25;
	float pauseBtnHeight = pauseBtnWidth * 2 / sqrt(3);

	Color btnColor = BLACK;
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, (Rectangle) { screenSize.x / 2 - pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50 , pauseBtnWidth, pauseBtnHeight })) {
		btnColor = RED;
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, (Rectangle) { screenSize.x / 2 - pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50, pauseBtnWidth, pauseBtnHeight })) {
		onPause = !onPause;
	}

	if (onPause) {
		DrawTriangle((Vector2) { screenSize.x / 2 - pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50 },
				(Vector2) {	screenSize.x / 2 - pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50 + pauseBtnHeight },
				(Vector2) {	screenSize.x / 2 + pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50 + pauseBtnHeight / 2 },
				btnColor);
	}
	else {
		DrawRectangle(screenSize.x / 2 - pauseBtnWidth / 2, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50,
			pauseBtnWidth / 3, pauseBtnHeight, btnColor);
		DrawRectangle(screenSize.x / 2 + pauseBtnWidth / 6, screenSize.y * 8 / 10 + 1 + screenSize.y / 50 + screenSize.y / 50,
			pauseBtnWidth / 3, pauseBtnHeight, btnColor);
	}

	return onPause;
}

float DrawSoundBar(Music music, float volume, Vector2 mousePos, Vector2 screenSize) {
	Rectangle r1, r2, r3;
	r1.width = screenSize.y / 50 + 2;
	r1.height = screenSize.y / 4;
	r1.x = screenSize.x * 9 / 10 + 19;
	r1.y = screenSize.y * 41 / 50 - r1.height;
	r1.height += 2;
	
	r2.x = r1.x + 1;
	r2.y = r1.y + 1;
	r2.width = r1.width - 2;
	r2.height = r1.height - 2;

	r3.x = r2.x;
	r3.width = r2.width;
	r3.y = r2.y + (1 - volume) * r2.height;
	r3.height = volume * r2.height;

	DrawRectangleRec(r1, BLACK);
	DrawRectangleRec(r2, LIGHTGRAY);
	DrawRectangleRec(r3, GRAY);

	if (CheckCollisionPointRec(mousePos, r2)) {
		Rectangle r4;
		r4.x = r2.x;
		r4.width = r2.width;
		r4.y = mousePos.y;
		r4.height = r2.height - (r4.y - r2.y);
		DrawRectangleRec(r4, RED);
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			volume = r4.height / r2.height;
	}

	DrawText(TextFormat("%3d%%", (int)(volume * 100)), r2.x - r2.width, r2.y + r2.height + screenSize.y / 50, 20, BLACK);

	SetMusicVolume(music, volume);

	return volume;
}