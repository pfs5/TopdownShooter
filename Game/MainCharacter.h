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
	const std::string TEX_NAME_PLAYER = "prototype-1-player";
	const std::string TEX_NAME_CROSSHAIR = "prototype-1-player-crosshair";

	const float MOVEMENT_SPEED = 500.f;
	const float SIZE_SCALE = 0.7f;
	const float CROSSHAIR_DISTANCE = 100.f;

	// Visuals
	sf::Sprite _sprite;
	sf::Sprite _crosshairSprite;

	// Shooting
	sf::Vector2f _aimDirection;

private:
	/* ------------------------- Functions ------------------------------------------------ */
	void moveAction(float dt);
	void aimAction();
};

