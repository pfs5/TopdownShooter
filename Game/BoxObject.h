#pragma once
#include "GameObject.h"

class BoxObject : public GameObject
{
public:
	BoxObject(const sf::Vector2f &size, float mass);
	~BoxObject();

// GameObject
public:
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f& _pos) override;
private:
	sf::Vector2f _size;

	sf::Sprite _sprite;
};

