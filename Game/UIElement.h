#pragma once
#include "ITransformable.h"

class UIElement : public ITransformable
{
public:
	virtual ~UIElement() = default;

	virtual void setLocalPosition(const sf::Vector2f& _pos) override;

	virtual void draw() = 0;
};

inline void UIElement::setLocalPosition(const sf::Vector2f& _pos)
{
	ITransformable::setLocalPosition(_pos);
}
