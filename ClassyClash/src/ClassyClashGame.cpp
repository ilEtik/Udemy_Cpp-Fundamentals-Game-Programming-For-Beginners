#pragma once

#include "ClassyClashGame.h"
#include "Character.h"
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
		_mapBounds = {0, 0, _mapTexture.width * _mapScale, _mapTexture.height * _mapScale};
	}

	int Game::Run()
	{
		Character knight(&WindowDimensions);

		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(WHITE);

			const float frameTime = GetFrameTime();

			DrawMap(knight.GetWorldPosition());

			knight.Tick(&frameTime, &_mapBounds, &WindowDimensions);

			EndDrawing();
		}

		return 0;
	}

	Game::~Game()
	{
		UnloadTexture(_mapTexture);
		CloseWindow();
	}

	void Game::DrawMap(const Vector2* knightWorldPosition)
	{
		_mapPosition = Vector2Scale({knightWorldPosition->x, knightWorldPosition->y}, -1.f);
		DrawTextureEx(_mapTexture, _mapPosition, 0.f, _mapScale, WHITE);
	}
}