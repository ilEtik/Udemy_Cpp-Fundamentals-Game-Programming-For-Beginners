#include "Character.h"
#include "raymath.h"
#include "ClassyClashGame.h"

namespace ClassyClash
{
	void Character::Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions)
	{
		_velocity = GetVelocity();

		_previousWorldPosition = _worldPosition;

		Animate(deltaTime);

		const bool isMoving = IsMoving();

		if (isMoving)
		{
			Vector2 normalizedVelocity = Vector2Scale(Vector2Normalize(_velocity), _movementSpeed);
			_worldPosition = Vector2Add(_worldPosition, normalizedVelocity);
			_playerSourceRect.width = (normalizedVelocity.x < 0.f ? -1.f : 1.f) * _characterWidth;

			Vector2 screenPosition = GetScreenPosition();

			DEBUG_POSITION(Vector2Add(screenPosition, normalizedVelocity), RED);

			_playerTargetRect.x = screenPosition.x;
			_playerTargetRect.y = screenPosition.y;
		}

		DrawTexturePro(isMoving ? _runTexture : _idleTexture, _playerSourceRect, _playerTargetRect, {0.f, 0.f}, 0.f, WHITE);
	}

	void Character::UndoMovement()
	{
		_worldPosition = _previousWorldPosition;
	}

	const Rectangle Character::GetCollisionRec() const
	{
		return _playerTargetRect;
	}

	const bool Character::IsMoving() const
	{
		return Vector2Length(_velocity) != 0.f;
	}

	void Character::Animate(const float* deltaTime)
	{
		_currentFrameTimer += *deltaTime;
		if (_currentFrameTimer >= _maxFrameTimer)
		{
			_currentFrameTimer = 0.0f;
			_playerSourceRect.x = _currentAnimationFrame * _characterWidth;
			_currentAnimationFrame = (_currentAnimationFrame + 1) % _maxAnimationFrames;
		}
	}
}