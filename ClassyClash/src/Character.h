#pragma once

#include "raylib.h"

namespace ClassyClash
{
	class Character
	{
	public:
		Character(const Vector2* windowDimensions);
		void Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions);
		~Character();
		const Vector2* GetWorldPosition() 
		{
			return &_worldPosition;
		}

	private:
		Vector2 _screenPosition{};
		Vector2 _worldPosition{};
		Vector2 _previousWorldPosition{};
		const float _movementSpeed{8.f};
		
		float _characterWidth{};
		float _characterHeight{};

		Rectangle _playerSourceRect;
		Rectangle _PlayerTargetRect;

		Texture2D _playerTexture;
		Texture2D _playerRunTexture;

		/// <summary>
		/// 1: right; -1: left
		/// </summary>
		float _facingDirection{1.f};

		float _currentFrameTimer{};
		const float _maxFrameTimer{1.f / 12.f};
		int _currentAnimationFrame{};
		const int _maxAnimationFrames{6};

	private:
		void UndoMovement();
		void Animate(const float* deltaTime);
		bool IsInBounds(const Rectangle* bounds, const Vector2* windowDimensions) const;
	};
}