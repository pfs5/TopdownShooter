#pragma once
#include "GameObject.h"

class BoxCharacter : public GameObject {
	sf::RectangleShape m_shape;
public:
	BoxCharacter();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void movement();
};