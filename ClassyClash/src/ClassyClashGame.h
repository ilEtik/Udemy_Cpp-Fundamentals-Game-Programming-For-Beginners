#pragma once

#include <iostream>
#include <array>

#include "raylib.h"
#include "Player.h"
#include "Prop.h"

#ifdef _DEBUG
#define DEBUG_COLLIDER(collider, color) DrawRectangleLinesEx(collider, 3, color)
#else
#define DEBUG_COLLIDER(collider, color)
#endif

#ifdef _DEBUG
#define DEBUG_POSITION(position, color) DrawCircleV(position, 5, color)
#else
#define DEBUG_POSITION(position, color)
#endif

namespace ClassyClash
{
	class Game
	{

	public:
		const char* Title{"Classy Clash"};
		const int TargetFps{60};
		const Vector2 WindowDimensions{1920, 1080};

	public:
		Game();
		int Run();
		~Game();

	private:
		Texture2D _mapTexture;
		Vector2 _mapPosition{0, 0};
		const float _mapScale = 4.f;
		Rectangle _mapBounds;

	private:
		void DrawMap(const Vector2& knightWorldPosition);

		template <std::size_t N>
		bool CheckPlayerCollisions(const Player& player, const std::array<Prop, N>& props);
	};
}