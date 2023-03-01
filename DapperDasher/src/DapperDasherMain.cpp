#include "raylib.h"

#include <iostream>

#define OUT

namespace Dasher
{
	bool EnableCollisionDebugging{false};

	struct EntityData
	{
		Vector2 Position{0, 0};
		Rectangle Rect{0, 0, 0, 0};
		int AnimationFrame{0};
		float AnimationUpdateTime{1.0f / 2.0f};
		float AnimationRunningTime{0.0f};
	};

	const char* Title{"Dapper Dasher"};
	const Vector2 WindowDimensions{850, 500};
	const int TargetFPS{60};

	const int Gravity{1900};
	const int GroundHeight{35};

	EntityData Player;
	Texture2D PlayerTexture;
	int playerVelocity{0};
	int jumpForce{800};

	const int NebulaAmount{5};
	EntityData NebulaArray[NebulaAmount];
	Texture2D NebulaTexture;
	int nebulaVelocity{400};
	int NebulaXOffsetMin = 375;
	int NebulaXOffsetMax = 525;

	float BackgroundPositionX{0.0f};
	Texture2D Background;
	float MidgroundPositionX{0.0f};
	Texture2D Midground;
	float ForegroundPositionX{0.0f};
	Texture2D Foreground;

	float FinishLine;
	bool Collision{false};
	bool PlayerPassedFinishLine{false};

#pragma region Initialize

	void InitializeLevel()
	{
		Background = LoadTexture("Assets/textures/far-buildings.png");
		Midground = LoadTexture("Assets/textures/back-buildings.png");
		Foreground = LoadTexture("Assets/textures/foreground.png");
	}

	void InitializePlayer()
	{
		PlayerTexture = LoadTexture("Assets/textures/scarfy.png");
		Player.Rect.width = PlayerTexture.width / 6.0f;
		Player.Rect.height = PlayerTexture.height;
		Player.Rect.x = 0;
		Player.Rect.y = 0;
		Player.AnimationUpdateTime = 1.0f / 12.0f;

		Player.Position.x = (WindowDimensions.x / 2) - (Player.Rect.width / 2);
		Player.Position.y = WindowDimensions.y - Player.Rect.height - GroundHeight;
	}

	void InitializeNebula()
	{
		NebulaTexture = LoadTexture("Assets/textures/12_nebula_spritesheet.png");

		int nextXOffset{0};
		int lastXOffset{0};
		for (EntityData & i : NebulaArray)
		{
			i.Rect = {0, 0, NebulaTexture.width / 8.0f, NebulaTexture.height / 8.0f};
			i.AnimationFrame = 0;
			i.AnimationUpdateTime = 1.0f / 32.0f;
			i.AnimationRunningTime = 0.0f;

			i.Position.x = WindowDimensions.x + lastXOffset + nextXOffset;
			i.Position.y = WindowDimensions.y - i.Rect.height - GroundHeight;
			nextXOffset = GetRandomValue(NebulaXOffsetMin, NebulaXOffsetMax);
			lastXOffset += nextXOffset;
		}
	}

	void InitializeGame()
	{
		InitializeLevel();
		InitializePlayer();
		InitializeNebula();

		FinishLine = NebulaArray[NebulaAmount - 1].Position.x + 300;
	}

#pragma endregion

#pragma region UpdateFunctions

	void UpdateBackground(const float deltaTime)
	{
		int textureSizeMultiplier = 3.0f;

		BackgroundPositionX -= 20 * deltaTime;
		if (BackgroundPositionX <= 0 - Background.width * textureSizeMultiplier)
		{
			BackgroundPositionX = 0.0f;
		}

		MidgroundPositionX -= 40 * deltaTime;
		if (MidgroundPositionX <= 0 - Midground.width * textureSizeMultiplier)
		{
			MidgroundPositionX = 0.0f;
		}

		ForegroundPositionX -= 80 * deltaTime;
		if (ForegroundPositionX <= 0 - Foreground.width * textureSizeMultiplier)
		{
			ForegroundPositionX = 0.0f;
		}

		DrawTextureEx(Background, {BackgroundPositionX, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
		DrawTextureEx(Background, {BackgroundPositionX + Background.width * textureSizeMultiplier, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
		DrawTextureEx(Midground, {MidgroundPositionX, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
		DrawTextureEx(Midground, {MidgroundPositionX + Midground.width * textureSizeMultiplier, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
		DrawTextureEx(Foreground, {ForegroundPositionX, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
		DrawTextureEx(Foreground, {ForegroundPositionX + Foreground.width * textureSizeMultiplier, -75.0f}, 0.0f, textureSizeMultiplier, WHITE);
	}

	bool IsPlayerGrounded()
	{
		return Player.Position.y >= WindowDimensions.y - Player.Rect.height - GroundHeight;
	}

	bool IsVisibleInWindowHorizontal(const EntityData* data, int width)
	{
		return data->Position.x >= 0 - width || data->Position.x <= WindowDimensions.x;
	}

	bool IsGameOver()
	{
		return Collision || PlayerPassedFinishLine;
	}

	void UpdateAnimation(EntityData* data, const float deltaTime, int maxFrame)
	{
		data->AnimationRunningTime += deltaTime;

		if (data->AnimationRunningTime >= Player.AnimationUpdateTime)
		{
			data->AnimationRunningTime = 0.0f;
			data->Rect.x = data->AnimationFrame * data->Rect.width;
			data->AnimationFrame = (data->AnimationFrame + 1) % maxFrame;
		}
	}

	void UpdatePlayer(const float deltaTime)
	{
		if (IsPlayerGrounded())
		{
			playerVelocity = 0;

			if (IsKeyDown(KEY_SPACE) && !IsGameOver())
			{
				playerVelocity = -jumpForce;
			}

			UpdateAnimation(&Player, deltaTime, 6);
		}
		else
		{
			playerVelocity += Gravity * deltaTime;
		}

		Player.Position.y += playerVelocity * deltaTime;
		DrawTextureRec(PlayerTexture, Player.Rect, Player.Position, WHITE);
	}

	void UpdateNebula(const float deltaTime, OUT EntityData& nebula)
	{
		nebula.Position.x -= nebulaVelocity * deltaTime;

		//Check if nebula is visible to draw it.
		if (!IsVisibleInWindowHorizontal(&nebula, NebulaTexture.width))
		{
			return;
		}

		UpdateAnimation(&nebula, deltaTime, 8);
		DrawTextureRec(NebulaTexture, nebula.Rect, nebula.Position, WHITE);
	}

	void CheckForGameOver(const float deltaTime)
	{
		if (Collision)
		{
			DrawText("Game Over!", WindowDimensions.x / 2 - 175, WindowDimensions.y / 2 - 50, 75, WHITE);
			return;
		}

		if (PlayerPassedFinishLine)
		{
			DrawText("You Win!", WindowDimensions.x / 2 - 125, WindowDimensions.y / 2 - 50, 75, WHITE);
			return;
		}

		for (const EntityData & nebula : NebulaArray)
		{
			if (!IsVisibleInWindowHorizontal(&nebula, NebulaTexture.width))
			{
				continue;
			}

			float pad{25};
			Rectangle nebRect{
				nebula.Position.x + pad,
				nebula.Position.y + pad,
				nebula.Rect.width - 2 * pad,
				nebula.Rect.height - 2 * pad,
			};

			Rectangle playerRect{
				Player.Position.x + pad,
				Player.Position.y,
				Player.Rect.width - 2 * pad,
				Player.Rect.height,
			};

			if (EnableCollisionDebugging)
			{
				DrawRectangle(nebRect.x, nebRect.y, nebRect.width, nebRect.height, BLUE);
				DrawRectangle(playerRect.x, playerRect.y, playerRect.width, playerRect.height, GREEN);
			}
			if (CheckCollisionRecs(nebRect, playerRect))
			{
				Collision = true;
				std::cout << "Collide" << std::endl;
				return;
			}
		}

		FinishLine -= nebulaVelocity * deltaTime;

		if (Player.Position.x >= FinishLine)
		{
			PlayerPassedFinishLine = true;
		}
	}

	void RunLevel(const float deltaTime)
	{
		UpdateBackground(deltaTime);

		for (EntityData & i : NebulaArray)
		{
			UpdateNebula(deltaTime, i);
		}

		UpdatePlayer(deltaTime);

		CheckForGameOver(deltaTime);
	}

#pragma endregion

	void DeinitializeGame()
	{
		UnloadTexture(Background);
		UnloadTexture(Midground);
		UnloadTexture(Foreground);
		UnloadTexture(PlayerTexture);
		UnloadTexture(NebulaTexture);
	}
}

int main()
{
	InitWindow(Dasher::WindowDimensions.x, Dasher::WindowDimensions.y, Dasher::Title);
	SetTargetFPS(60);

	Dasher::InitializeGame();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Dasher::RunLevel(GetFrameTime());

		EndDrawing();
	}

	Dasher::DeinitializeGame();
	CloseWindow();
}
