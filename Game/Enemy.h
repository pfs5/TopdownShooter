#pragma once

#include "GameObject.h"
#include "IWeaponReactor.h"
#include "MainCharacter.h"
#include "UILine.h"
#include "IProjectileReactor.h"

class IEnemyDestroyObserver;

class Enemy : public GameObject, public IProjectileReactor
{
public:
	Enemy(const MainCharacter * mainCharacter, float hp = 100.f);
	~Enemy();

	void attachObserver(IEnemyDestroyObserver *o);

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

	const float MOVEMENT_SPEED = 200.f;		// 200
	const float SIZE_SCALE = 0.4f;
	const float ATTACK_DISTANCE = 50.f;
	const float RECOIL_DAMP_TIME = .5f;
	const float INVINCIBILITY_TIME = .1f;	// time of enemy being invincible after getting hit
	const float SQUARED_RANGE = 500.f * 500.f;

	std::vector<IEnemyDestroyObserver*> _observers;

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

