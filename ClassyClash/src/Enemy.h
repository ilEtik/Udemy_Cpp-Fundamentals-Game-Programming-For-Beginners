#pragma once

#include "raylib.h"
#include "Character.h"
#include "Player.h"

namespace ClassyClash
{
	class Enemy : public Character
	{
	public:
		Enemy(Vector2 position, const char* idleTextureName, const char* runTextureName);
		void Tick(const float* deltaTime, const Rectangle* mapBounds, const Vector2* windowDimensions) override;
		~Enemy();

		void SetTarget(Player* target);

		const Vector2 GetScreenPosition() const override;

	protected:
		const Vector2 GetVelocity() override;

	private:
		Player* _target;
	};
}