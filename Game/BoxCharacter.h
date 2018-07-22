#pragma once
#include "GameObject.h"

class BoxCharacter : public GameObject {
#pragma region Enums
public:
	enum PLAYER_NUMBER {
		PlayerOne,
		PlayerTwo
	};
#pragma endregion
#pragma region Parameters
private:
	const float AIM_VISUAL_DISTANCE = 75;
	const float RECOIL_DRAG_COEFF = 0.9f;
#pragma endregion
private:
	PLAYER_NUMBER m_playerNo;

	// Visuals
	sf::RectangleShape m_shape;
	sf::CircleShape m_aimShape;

	// State
	sf::Vector2f m_aimDirection;
public:
	BoxCharacter(PLAYER_NUMBER _playerNo);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void movement();
	void aim();
	void shoot();
};