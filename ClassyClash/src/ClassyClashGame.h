#pragma once

#include "raylib.h"

namespace ClassyClash
{

	class Game
	{

	public:
		const char* Title{"Classy Clash"};
		const int TargetFps{60};
		const Vector2 WindowDimensions{800, 800};

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
		void DrawMap(const Vector2* knightWorldPosition);
	};
}