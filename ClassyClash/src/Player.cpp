#include "Player.h"
#include "raymath.h"

namespace ClassyClash
{
	Player::Player(const Vector2* windowDimensions)
	{
		_idleTexture = LoadTexture("Assets/characters/knight_idle_spritesheet.png");
		_runTexture = LoadTexture("Assets/characters/knight_run_spritesheet.png");
		_characterWidth = static_cast<float>(_idleTexture.width) / _maxAnimationFrames;
		_characterHeight = _idleTexture.height;

		_screenPosition =
		{
			(windowDimensions->x * 0.5f) - _scale * (0.5f * _characterWidth),
			(windowDimensions->y * 0.5f) - _scale * (0.5f * _characterHeight)
		};
		_worldPosition = _screenPosition;
		_playerSourceRect =
		{
			0.f,
			0.f,
			_characterWidth,
			_characterHeight
		};
		_playerTargetRect =
		{
			_screenPosition.x,
			_screenPosition.y,
			_characterWidth * _scale,
			_characterHeight * _scale
		};
	}

	void Player::Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions)
	{
		Character::Tick(deltaTime, mapBounds, windowDimensions);

		//std::printf("Player Position: (%f, %f) \n", _worldPosition.x, _worldPosition.x);
		if (!IsInBounds(mapBounds, windowDimensions))
		{
			UndoMovement();
		}
	}

	Player::~Player()
	{
		UnloadTexture(_idleTexture);
		UnloadTexture(_runTexture);
	}

	const Vector2 Player::GetVelocity()
	{
		Vector2 direction{};
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
		return direction;
	}

	bool Player::IsInBounds(const Rectangle* bounds, const Vector2* windowDimensions) const
	{
		return _worldPosition.x > bounds->x &&
			_worldPosition.x + windowDimensions->x < bounds->width &&
			_worldPosition.y > bounds->y &&
			_worldPosition.y + windowDimensions->y < bounds->height;
	}
}