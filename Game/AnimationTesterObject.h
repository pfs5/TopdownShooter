#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class AnimationTesterObject : public GameObject
{
public:
	AnimationTesterObject();
	~AnimationTesterObject();

// GameObject
public:
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;

	void setLocalPosition(const sf::Vector2f& _pos) override;
private:
	AnimationController _animation;
	bool _isMoving;
};
