#pragma once

#include "GameObject.h"
#include "IWeaponReactor.h"
#include "MainCharacter.h"

class Enemy : public GameObject, public IWeaponReactor
{
public:
	Enemy(const MainCharacter * mainCharacter, sf::Color color = sf::Color(255, 0, 0));
	Enemy(sf::Color color = sf::Color(255, 0, 0));
	~Enemy();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;

	// IWeaponReactor
	void onShoot() override;
	void applyKnockback(sf::Vector2f velocity) override;

	void attack(const MainCharacter * mainCharacter);

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

private:
	/* ------------------------- Functions ------------------------------------------------ */
	void followPlayer(float dt);
};

