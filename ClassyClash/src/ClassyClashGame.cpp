#pragma once

#include "Game.h"
#include "raymath.h"

#include <iostream>

namespace ClassyClash
{
	Game::Game()
	{
		InitWindow(WindowDimensions.x, WindowDimensions.y, Title);
		SetTargetFPS(TargetFps);

		//Load Assets
		_mapTexture = LoadTexture("Assets/WorldMap.png");
	}

	int Game::Run()
	{
		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(WHITE);

			Vector2 direction {0, 0};
			if (IsKeyDown(KEY_A))
			{
				direction.x -= 1.0f;
			}
			if (IsKeyDown(KEY_D))
			{
				direction.x += 1.0f;
			}
			if (IsKeyDown(KEY_W))
			{
				direction.y -= 1.0f;
			}
			if (IsKeyDown(KEY_S))
			{
				direction.y += 1.0f;
			}

			if (Vector2Length(direction) != 0.0f)
			{
				Vector2 normalizedPos = Vector2Scale(Vector2Normalize(direction), _speed);
				_mapPosition = Vector2Subtract(_mapPosition, normalizedPos);
			}

			DrawTextureEx(_mapTexture, _mapPosition, 0.0, 4.0, WHITE);

			EndDrawing();
		}

		return 0;
	}

	Game::~Game()
	{
		CloseWindow();
	}
}