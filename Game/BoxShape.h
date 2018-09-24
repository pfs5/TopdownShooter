#pragma once
#include "GameObject.h"

class BoxShape : public GameObject
{
public:
	BoxShape(sf::Vector2f size = sf::Vector2f{100.f, 100.f}, sf::Color color = sf::Color::Red);
	~BoxShape() override;
	
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f& _pos) override;

	void setSize(const sf::Vector2f &size);
	void setColor(const sf::Color &color);

private:
	// Visuals
	sf::RectangleShape _shape;
};
