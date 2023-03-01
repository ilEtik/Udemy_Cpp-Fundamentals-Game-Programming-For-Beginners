#include "Character.h"
#include "raymath.h"

#include <cstdio>

namespace ClassyClash
{
	Character::Character(const Vector2* windowDimensions)
	{
		_playerTexture = LoadTexture("Assets/characters/knight_idle_spritesheet.png");
		_playerRunTexture = LoadTexture("Assets/characters/knight_run_spritesheet.png");
		_characterWidth = (float)_playerTexture.width / _maxAnimationFrames;
		_characterHeight = _playerTexture.height;

		_screenPosition =
		{
			windowDimensions->x / 2.f - 8.f * (0.5f * _characterWidth),
			windowDimensions->y / 2.f - 8.f * (0.5f * _characterHeight)
		};
		_worldPosition = _screenPosition;
		_playerSourceRect =
		{
			0.f,
			0.f,
			_characterWidth,
			_characterHeight
		};
		_PlayerTargetRect =
		{
			_screenPosition.x,
			_screenPosition.y,
			8.f * _characterWidth,
			8.f * _characterHeight
		};
	}

	void Character::Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions)
	{
		_previousWorldPosition = _worldPosition;

		Vector2 direction{0, 0};
		if (IsKeyDown(KEY_A))
		{
			direction.x -= 1.f;
		}
		if (IsKeyDown(KEY_D))
		{
			direction.x += 1.f;
		}
		if (IsKeyDown(KEY_W))
		{
			direction.y -= 1.f;
		}
		if (IsKeyDown(KEY_S))
		{
			direction.y += 1.f;
		}

		if (Vector2Length(direction) != 0.f)
		{
			Vector2 normalizedDirection = Vector2Scale(Vector2Normalize(direction), _movementSpeed);
			_worldPosition = Vector2Add(_worldPosition, normalizedDirection);

			_playerSourceRect.width = (direction.x < 0.f ? -1.f : 1.f) * _characterWidth;
		}

		Animate(deltaTime);

		DrawTexturePro((Vector2Length(direction) != 0.f ? _playerRunTexture : _playerTexture), _playerSourceRect, _PlayerTargetRect, {0.f, 0.f}, 0.f, WHITE);


		//std::printf("Player Position: (%f, %f) \n", _worldPosition.x, _worldPosition.x);
		if (!IsInBounds(mapBounds, windowDimensions))
		{
			UndoMovement();
		}
	}

	Character::~Character()
	{
		UnloadTexture(_playerTexture);
		UnloadTexture(_playerRunTexture);
	}

	void Character::UndoMovement()
	{
		_worldPosition = _previousWorldPosition;
	}

	void Character::Animate(const float* deltaTime)
	{
		// Update Animation Frame
		_currentFrameTimer += *deltaTime;
		if (_currentFrameTimer >= _maxFrameTimer)
		{
			_currentFrameTimer = 0.0f;
			_playerSourceRect.x = _currentAnimationFrame * _playerSourceRect.width;
			_currentAnimationFrame = (_currentAnimationFrame + 1) % _maxAnimationFrames;
		}
	}

	bool Character::IsInBounds(const Rectangle* bounds, const Vector2* windowDimensions) const
	{
		return _worldPosition.x > bounds->x &&
			_worldPosition.x + windowDimensions->x < bounds->width &&
			_worldPosition.y > bounds->y &&
			_worldPosition.y + windowDimensions->y < bounds->height;
	}
}