#pragma once
#include <GameObject.h>
class GamePerimeter : public GameObject {
	// Visuals
	sf::RectangleShape m_shapeTop;
	sf::RectangleShape m_shapeBottom;
	sf::RectangleShape m_shapeLeft;
	sf::RectangleShape m_shapeRight;
	sf::RectangleShape m_shapeMiddle;
public:
	GamePerimeter();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};