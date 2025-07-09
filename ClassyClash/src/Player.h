#pragma once

#include "raylib.h"
#include "Character.h"

namespace ClassyClash
{
	class Player : public Character
	{
	public:
		Player(const Vector2& windowDimensions);
		void Tick(const float deltaTime, const Rectangle& mapBounds, const Vector2& windowDimensions) override;
		~Player();

		bool IsInBounds(const Rectangle& bounds, const Vector2& windowDimensions) const;

		const Rectangle& GetWeaponCollisionRec() const { return _weaponCollisionRec; }

		const float GetHealth() const { return _health; }
		void TakeDamage(float damage);

	protected:
		const Vector2 GetVelocity() override;

	private:
		Texture _weapon;
		Rectangle _weaponCollisionRec;
		float _health{100.0f};
	};
}