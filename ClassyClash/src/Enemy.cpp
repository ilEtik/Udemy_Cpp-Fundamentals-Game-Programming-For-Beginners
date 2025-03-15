#include "Enemy.h"
#include "raymath.h"

#include <cstdio>

namespace ClassyClash
{
	Enemy::Enemy(Vector2 position, const char* idleTextureName, const char* runTextureName) 
	{
		_worldPosition = position;
		_idleTexture = LoadTexture(idleTextureName);
		_runTexture = LoadTexture(runTextureName);

		_characterWidth = static_cast<float>(_idleTexture.width) / _maxAnimationFrames;
		_characterHeight = _idleTexture.height;

		_playerSourceRect =
		{
			0.f,
			0.f,
			_characterWidth,
			_characterHeight
		};

		_playerTargetRect =
		{
			0,
			0,
			_characterWidth * _scale,
			_characterHeight * _scale
		};

		_movementSpeed = 60.0f;

		log = true;
	}



	void Enemy::Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions)
	{
		_screenPosition = GetScreenPosition();

		Character::Tick(deltaTime, mapBounds, windowDimensions);
	}

	Enemy::~Enemy()
	{
		UnloadTexture(_idleTexture);
		UnloadTexture(_runTexture);
	}

	void Enemy::SetTarget(Player* target)
	{
		_target = target;
	}

	const Vector2 Enemy::GetScreenPosition()
	{
		return Vector2Subtract(_worldPosition, _target->GetWorldPosition());
	}

	const Vector2 Enemy::GetDirection()
	{
		Vector2 direction = Vector2Subtract(_target->GetScreenPosition(), GetScreenPosition());
		return direction;
	}
}