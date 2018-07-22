#pragma once
#include "GameObject.h"

class BasicShot : public GameObject {
#pragma region Parameters
	const float DESTROY_DELAY = 10.f;
	const float HIT_POWER = 500.f;
#pragma endregion

	// Visual
	sf::CircleShape m_shape;

	// State
	float m_destructionTime;
public:
	BasicShot();
	~BasicShot();

	void shoot(sf::Vector2f _direction);
	float getHitPower();
	sf::Vector2f getDirection();
	void destroy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};