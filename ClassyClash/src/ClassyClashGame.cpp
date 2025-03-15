#include "ClassyClashGame.h"
#include "Player.h"
#include "Prop.h"
#include "Enemy.h"

#include "raymath.h"

#include <iostream>

#define DEBUG true

namespace ClassyClash
{
	Game::Game()
	{
		InitWindow(WindowDimensions.x, WindowDimensions.y, Title);
		SetTargetFPS(TargetFps);

		_mapTexture = LoadTexture("Assets/WorldMap.png");

		int boundOffsetLeft = 70;
		int boundOffsetTop = 90;
		int boundOffsetRight = 70;
		int boundOffsetBottom = 75;

		float halfWidth = WindowDimensions.x * 0.5f;
		float halfHeight = WindowDimensions.y * 0.5f;

		_mapBounds =
		{
			-halfWidth + boundOffsetLeft,
			-halfHeight + boundOffsetTop,
			(_mapTexture.width * _mapScale) + (halfWidth - boundOffsetRight),
			(_mapTexture.height * _mapScale) + (halfHeight - boundOffsetBottom)
		};
	}

	int Game::Run()
	{
		Player player(&WindowDimensions);

		Prop props[2]
		{
			Prop(Vector2{ 1000, 1000 }, "Assets/nature_tileset/Bush.png"),
			Prop(Vector2{ 1550, 750 }, "Assets/nature_tileset/Rock.png")
		};

		Enemy goblin(Vector2{1000, 750}, "Assets/characters/goblin_idle_spritesheet.png", "Assets/characters/goblin_run_spritesheet.png");
		goblin.SetTarget(&player);

		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(BLACK);

			const float frameTime = GetFrameTime();

			const Vector2 playerPosition = player.GetWorldPosition();

			DrawMap(playerPosition);

			for (Prop prop : props)
			{
				prop.Render(playerPosition);
			}

			player.Tick(&frameTime, &_mapBounds, &WindowDimensions);
			const Rectangle playerCollider = player.GetCollisionRec();
#if DEBUG
			DrawRectangleLinesEx(playerCollider, 3, BLUE);
#endif

			goblin.Tick(&frameTime, &_mapBounds, &WindowDimensions);
			const Rectangle enemyCollider = goblin.GetCollisionRec();
#if DEBUG
			DrawRectangleLinesEx(enemyCollider, 3, RED);
#endif

			for (Prop prop : props)
			{
				const Rectangle propCollider = prop.GetCollisionRec(playerPosition);
#if DEBUG
				DrawRectangleLinesEx(propCollider, 3, PINK);
#endif

				if (CheckCollisionRecs(playerCollider, propCollider))
				{
					player.UndoMovement();
					break;
				}
			}

			EndDrawing();
		}

		return 0;
	}

	Game::~Game()
	{
		UnloadTexture(_mapTexture);

		CloseWindow();
	}

	void Game::DrawMap(const Vector2 knightWorldPosition)
	{
		_mapPosition = Vector2Scale({knightWorldPosition.x, knightWorldPosition.y}, -1.f);
		DrawTextureEx(_mapTexture, _mapPosition, 0.f, _mapScale, WHITE);
	}
}