#pragma once

#include "raylib.h"

namespace ClassyClash
{
	class Character
	{
	public:
		virtual void Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions);
		void UndoMovement();

		const Vector2 GetWorldPosition()
		{
			return _worldPosition;
		}
		virtual const Vector2 GetScreenPosition()
		{
			return _screenPosition;
		}
		const Rectangle GetCollisionRec();

	protected:
		Vector2 _screenPosition{};
		Vector2 _worldPosition{};
		Vector2 _previousWorldPosition{};
		float _movementSpeed{8.0f};

		float _characterWidth{};
		float _characterHeight{};

		Rectangle _playerSourceRect;
		Rectangle _playerTargetRect;

		Texture2D _idleTexture;
		Texture2D _runTexture;

		/// <summary>
		/// 1: right; -1: left
		/// </summary>
		float _facingDirection{1.f};

		float _currentFrameTimer{};
		const float _maxFrameTimer{1.f / 12.f};
		int _currentAnimationFrame{};
		const int _maxAnimationFrames{6};

		float _scale{8.0f};

		bool log = false;

	protected:
		virtual const Vector2 GetDirection() = 0;
		void Animate(const float* deltaTime);
	};
}