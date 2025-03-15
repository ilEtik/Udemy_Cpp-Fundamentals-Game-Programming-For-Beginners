#include "Character.h"
#include "raymath.h"

#include <cstdio>

namespace ClassyClash
{
	void Character::Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions)
	{
		_previousWorldPosition = _worldPosition;

		Animate(deltaTime);

		Vector2 direction = GetDirection();

		bool isMoving = Vector2Length(direction) != 0.f;

		if (isMoving)
		{
			Vector2 normalizedDirection = Vector2Scale(Vector2Normalize(direction), _movementSpeed);
			_worldPosition = Vector2Add(_worldPosition, normalizedDirection);
			_playerSourceRect.width = (normalizedDirection.x < 0.f ? -1.f : 1.f) * _characterWidth;

			if (log)
				std::printf("worldPosition: (%f, %f) \n", _worldPosition.x, _worldPosition.y);
		}

		Vector2 screenPosition = GetScreenPosition();

		//if (log)
		//	std::printf("screenPosition: (%f, %f) \n", screenPosition.x, screenPosition.y);

		_playerTargetRect.x = screenPosition.x;
		_playerTargetRect.y = screenPosition.y;
		DrawTexturePro(isMoving ? _runTexture : _idleTexture, _playerSourceRect, _playerTargetRect, {0.f, 0.f}, 0.f, WHITE);
	}

	void Character::UndoMovement()
	{
		_worldPosition = _previousWorldPosition;
	}

	const Rectangle Character::GetCollisionRec()
	{
		return _playerTargetRect;
	}

	void Character::Animate(const float* deltaTime)
	{
		// Update Animation Frame
		_currentFrameTimer += *deltaTime;
		if (_currentFrameTimer >= _maxFrameTimer)
		{
			_currentFrameTimer = 0.0f;
			_playerSourceRect.x = _currentAnimationFrame * _characterWidth;
			_currentAnimationFrame = (_currentAnimationFrame + 1) % _maxAnimationFrames;
		}
	}
}