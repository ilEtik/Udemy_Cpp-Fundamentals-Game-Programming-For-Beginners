#pragma once

#include "raylib.h"

namespace ClassyClash
{
	static class Game
	{
	 public:
		const char *Title {"Classy Clash"};
		const Vector2 WindowDimensions {384*2, 384*2};
		const int TargetFps {60};

	 public:
		Game();
		int Run();
		~Game();

	 private:
		Texture2D _mapTexture;
		Vector2 _mapPosition {0, 0};
		float _speed {4.5f};
	};
}