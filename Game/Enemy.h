#pragma once

#include "GameObject.h"
#include "IWeaponReactor.h"
#include "MainCharacter.h"
#include "UILine.h"
#include "IProjectileReactor.h"

class Enemy : public GameObject, public IProjectileReactor
{
public:
	Enemy(const MainCharacter * mainCharacter, float hp = 100.f);
	~Enemy();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;

	// IProjectileReactor
	void onHit(ProjectileInfo projectileInfo) override;

private:

	/* ------------------------- Members ------------------------------------------------- */
	// Constants
	const std::string TEX_NAME_ENEMY = "prototype-1-player";

	const float MOVEMENT_SPEED = 200.f;
	const float SIZE_SCALE = 0.4f;
	const float ATTACK_DISTANCE = 50.f;
	const float RECOIL_DAMP_TIME = .5f;
	const float INVINCIBILITY_TIME = .1;	// time of enemy being invincible after getting hit

	// Visuals
	sf::Sprite _sprite;

	const MainCharacter *_mainCharacter;

	bool _isTrackingPlayer;
	sf::Vector2f _externalVelocity;
	sf::Vector2f _initialRecoilVelocity;
	float _recoilTimer;
	float _invincibilityTimer;

	// State
	float _hp;

	// Debug UI
	UILine _testLine;
private:
	/* ------------------------- Functions ------------------------------------------------ */
	void followPlayer(float dt);
	void applyDrag(float dt);

	void spawnExplosion();
};

