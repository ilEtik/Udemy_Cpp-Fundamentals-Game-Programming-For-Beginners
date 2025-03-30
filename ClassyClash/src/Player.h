#pragma once

#include "raylib.h"
#include "Character.h"

namespace ClassyClash
{
	class Player : public Character
	{
	public:
		Player(const Vector2* windowDimensions);
		void Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions) override;
		~Player();

		bool IsInBounds(const Rectangle* bounds, const Vector2* windowDimensions) const;

	protected:
		const Vector2 GetVelocity() override;
	};
}