#include "Prop.h"
#include "raymath.h"

namespace ClassyClash
{
	Prop::Prop(const Vector2 position, const char* textureName)
		: _texture(LoadTexture(textureName)), _worldPosition(position)
	{
	}

	void Prop::Render(const Vector2 playerPosition)
	{
		_screenPosition = Vector2Subtract(_worldPosition, playerPosition);
		DrawTextureEx(_texture, _screenPosition, 0.f, _scale, WHITE);
	}

	const Rectangle Prop::GetCollisionRec(const Vector2 playerPosition)
	{
		_screenPosition = Vector2Subtract(_worldPosition, playerPosition);

		return Rectangle
		{
			_screenPosition.x,
			_screenPosition.y,
			_texture.width * _scale,
			_texture.height * _scale
		};
	}
}