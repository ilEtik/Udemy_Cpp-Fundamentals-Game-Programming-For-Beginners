#pragma once

#include "raylib.h"

namespace ClassyClash
{
	class Prop
	{
	public:
		Prop(const Vector2 worldPosition, const char* textureName);

		void Render(const Vector2 playerPosition);

		const Rectangle GetCollisionRec(const Vector2 playerPosition);

	private:
		const Texture2D _texture;

		const Vector2 _worldPosition{};
		Vector2 _screenPosition{};

		const float _scale{8.0f};
	};
}