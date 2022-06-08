#include "raylib.h"

#include "interface.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	const int screenWidth = 1700;
	const int screenHeight = 700;

	InitWindow(screenWidth, screenHeight, "Music player");

	InitAudioDevice();

	Music music = LoadMusicStream("resources/Track.mp3");

	PlayMusicStream(music);
	PauseMusicStream(music);
	
	float volume = 0.45f;
	float pitch = 1.0f;
	float timePlayed = 0.0f;
	bool pause = true;

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);

		volume += 0.05f * GetMouseWheelMove();
		if (IsKeyDown(KEY_UP)) {
			volume += 0.025f;
		}
		if (IsKeyDown(KEY_DOWN)) {
			volume -= 0.025f;
		}
		if (volume < 0.0f)
			volume = 0.0f;
		if (volume > 1.0f)
			volume = 1.0f;
		
		if (IsKeyPressed(KEY_RIGHT))
			pitch += 0.05f;
		if (IsKeyPressed(KEY_LEFT))
			pitch -= 0.05f;
		if (pitch < 0.0f)
			pitch = 0.0f;
		SetMusicPitch(music, pitch);

		if (IsKeyPressed(KEY_R))
		{
			StopMusicStream(music);
			PlayMusicStream(music);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			pause = !pause;
		}

		if (pause) PauseMusicStream(music);
		else ResumeMusicStream(music);

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("PRESS R TO RESTART MUSIC", 15, 15, 20, LIGHTGRAY);
		DrawText("PRESS SPACE TO PAUSE/RESUME MUSIC", 15, 50, 20, LIGHTGRAY);
		DrawText("PRESS UP/DOWN OR USE MOUSEWHEEL TO CHANGE VOLUME", 15, 85, 20, LIGHTGRAY);

		DrawTimeBar(music, GetMousePosition(), (Vector2) { screenWidth, screenHeight });

		pause = DrawButtonPause(pause, GetMousePosition(), (Vector2) { screenWidth, screenHeight });

		volume = DrawSoundBar(music, volume, GetMousePosition(), (Vector2) { screenWidth, screenHeight });

		EndDrawing();
	}

	UnloadMusicStream(music);

	CloseAudioDevice();

	CloseWindow();

	return 0;
}