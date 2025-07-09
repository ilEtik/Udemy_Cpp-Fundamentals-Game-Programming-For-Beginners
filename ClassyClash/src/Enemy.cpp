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

		_movementSpeed = 6.0f;
	}

	void Enemy::Tick(const float deltaTime, const Rectangle& mapBounds, const Vector2& windowDimensions)
	{
		if (!_isAlive || _target == nullptr)
		{
			return;
		}

		_screenPosition = GetScreenPosition();

		Character::Tick(deltaTime, mapBounds, windowDimensions);

		if (CheckCollisionRecs(GetCollisionRec(), _target->GetCollisionRec()))
		{
			_target->TakeDamage(_damagePerSecond * deltaTime);
		}
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

	const Vector2 Enemy::GetScreenPosition() const
	{
		if (_target == nullptr)
		{
			return _worldPosition;
		}

		return Vector2Subtract(_worldPosition, _target->GetWorldPosition());
	}

	const Vector2 Enemy::GetVelocity()
	{
		if (!_target->IsAlive())
		{
			return {0.f, 0.f};
		}
		Vector2 direction = Vector2Subtract(_target->GetScreenPosition(), GetScreenPosition());

		if (Vector2Length(direction) < _radius)
		{
			return {};
		}

		return direction;
	}
}