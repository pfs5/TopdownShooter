#pragma once

#include "GameObject.h"
#include "IWeaponReactor.h"
#include "MainCharacter.h"
#include "UILine.h"

class Enemy : public GameObject, public IWeaponReactor
{
public:
	Enemy(const MainCharacter * mainCharacter);
	~Enemy();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;

	// IWeaponReactor
	void onShoot() override;
	void applyKnockback(sf::Vector2f velocity) override;

private:

	/* ------------------------- Members ------------------------------------------------- */
	// Constants
	const std::string TEX_NAME_ENEMY = "prototype-1-player";

	const float MOVEMENT_SPEED = 200.f;
	const float SIZE_SCALE = 0.7f;
	const float ATTACK_DISTANCE = 50.f;

	// Visuals
	sf::Sprite _sprite;

	const MainCharacter *_mainCharacter;

	bool _isTrackingPlayer;

	// Debug UI
	UILine _testLine;
	UILine _testLine2;
	UILine _testLine3;
	UILine _testLine4;
private:
	/* ------------------------- Functions ------------------------------------------------ */
	void followPlayer(float dt);
};

