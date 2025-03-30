#include "Prop.h"
#include "raymath.h"

#include <iostream>

namespace ClassyClash
{
	Prop::Prop(const Vector2 position, const char* textureName)
		: _texture(LoadTexture(textureName)), 
			_worldPosition(position)
	{
	}

	Prop::~Prop()
	{
		UnloadTexture(_texture);
	}

	void Prop::Render(const Vector2 playerPosition)
	{
		_screenPosition = Vector2Subtract(_worldPosition, playerPosition);
		DrawTextureEx(_texture, _screenPosition, 0.f, _scale, WHITE);
	}

	const Rectangle Prop::GetCollisionRec(const Vector2 playerPosition) const
	{
		Vector2 screenPosition = Vector2Subtract(_worldPosition, playerPosition);

		return Rectangle
		{
			screenPosition.x,
			screenPosition.y,
			_texture.width * _scale,
			_texture.height * _scale
		};
	}
}