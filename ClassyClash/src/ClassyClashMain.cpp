
#include "raylib.h"

int main()
{
	InitWindow(800, 450, "");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		EndDrawing();
	}

	CloseWindow();
}
