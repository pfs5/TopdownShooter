#pragma once
#include "GameObject.h"

class MainCharacter : public GameObject
{
public:
	MainCharacter();
	~MainCharacter();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setPosition(const sf::Vector2f &_pos) override;


private:

	/* ------------------------- Members ------------------------------------------------- */
	// Constants
	const float MOVEMENT_SPEED = 500.f;
	const std::string TEX_NAME_PLAYER = "prototype-1-player";
	const float SIZE_SCALE = 0.7f;

	// Visuals
	sf::Sprite _sprite;

private:
	/* ------------------------- Functions ------------------------------------------------ */
	void movement(float dt);
};

