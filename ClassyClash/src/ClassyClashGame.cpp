#include "ClassyClashGame.h"
#include "Player.h"
#include "Prop.h"
#include "Enemy.h"
#include "raymath.h"

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

		std::array<Prop, 2> props
		{
			Prop(Vector2{1550, 750}, "Assets/nature_tileset/Rock.png"),
			Prop(Vector2{1000, 1000}, "Assets/nature_tileset/Bush.png")
		};

		//Enemy goblin(Vector2{1000, 750}, "Assets/characters/goblin_idle_spritesheet.png", "Assets/characters/goblin_run_spritesheet.png");
		//goblin.SetTarget(&player);

		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(BLACK);

			const float frameTime = GetFrameTime();

			const Vector2 playerPosition = player.GetWorldPosition();

			DrawMap(playerPosition);

			for (Prop& prop : props)
			{
				prop.Render(playerPosition);
			}

			player.Tick(&frameTime, &_mapBounds, &WindowDimensions);

			if (CheckPlayerCollisions(player, props))
			{
				player.UndoMovement();
			}

			//goblin.Tick(&frameTime, &_mapBounds, &WindowDimensions);
			//const Rectangle enemyCollider = goblin.GetCollisionRec();
			//DEBUG_COLLIDER(enemyCollider, RED);

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
		_mapPosition = Vector2Scale(knightWorldPosition, -1.f);
		DrawTextureEx(_mapTexture, _mapPosition, 0.f, _mapScale, WHITE);
	}

	template <std::size_t N>
	bool Game::CheckPlayerCollisions(const Player& player, const std::array<Prop, N>& props)
	{
		const Rectangle playerCollider = player.GetCollisionRec();
		const Vector2 playerPosition = player.GetWorldPosition();

		std::printf("Previous Player Position: (%f, %f) \n", playerPosition.x, playerPosition.y);
		
		DEBUG_COLLIDER(playerCollider, BLUE);

		for (const Prop& prop : props)
		{
			const Rectangle propCollider = prop.GetCollisionRec(playerPosition);

			DEBUG_COLLIDER(propCollider, PINK);

			if (CheckCollisionRecs(playerCollider, propCollider))
			{
				std::printf("Player Collider Position: (%f, %f) \n", playerCollider.x, playerCollider.y);
				std::printf("Prop Collider: (%f, %f, %f, %f) \n", propCollider.x, propCollider.y, propCollider.width, propCollider.height);

				return true;
			}
		}

		return false;
	}
}