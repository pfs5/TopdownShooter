#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(float mass, bool doesPenetrate = false);
	~Projectile() override;

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f& _pos) override;

	void shootProjectile(const sf::Vector2f &velocity);

	inline void setDirection(const sf::Vector2f &direction) { _direction = direction; }
	inline void setVelocity(const sf::Vector2f &velocity) { getRigidBody()->setVelocity(velocity); }

private:
	/* ------------------------- Members ------------------------------------------------- */
	// Constants
	const std::string TEX_NAME_PROJECTILE = "prototype-1-player-projectile";
	const float LIFETIME = 3.f;

	float _counter;

	// Parameters
	float _mass;
	bool _doesPenetrate;

	// Movement
	sf::Vector2f _direction;

	// Visuals
	sf::Sprite _mainSprite;
};
