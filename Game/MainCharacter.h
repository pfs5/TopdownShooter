#pragma once
#include "GameObject.h"

class MainCharacter : public GameObject
{
#pragma region Parameters
	const float MOVEMENT_SPEED = 10.f;
	const float SHAPE_SIZE = 25.f;
#pragma endregion

	sf::CircleShape _debugShape;
public:
	MainCharacter();
	~MainCharacter();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setPosition(const sf::Vector2f &_pos) override;

private:
	void movement(float dt);
};

