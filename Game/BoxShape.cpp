#include "BoxShape.h"
#include "Display.h"
#include "Debug.h"
#include "Rendering.h"

BoxShape::BoxShape(sf::Vector2f size, sf::Color color) :
	_shape{size}
{
	
	_shape.setFillColor(color);
	_shape.setOrigin(_shape.getSize() / 2.f);
}

BoxShape::~BoxShape()
{
}

void BoxShape::update(float _dt)
{
}

void BoxShape::draw()
{
	Rendering::draw(_shape);
}

void BoxShape::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* BoxShape::clone()
{
	return new BoxShape(_shape.getSize(), _shape.getFillColor());
}

void BoxShape::setLocalPosition(const sf::Vector2f& _pos)
{
	GameObject::setLocalPosition(_pos);

	_shape.setPosition(_globalPosition);
}

void BoxShape::setSize(const sf::Vector2f& size)
{
	_shape.setSize(size);
}

void BoxShape::setColor(const sf::Color& color)
{
	_shape.setFillColor(color);
}
