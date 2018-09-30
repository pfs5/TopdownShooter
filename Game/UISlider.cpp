#include "UISlider.h"
#include "Display.h"
#include "Util.h"
#include "Debug.h"

UISlider::UISlider(const sf::Vector2f &size, const sf::Color &backgroundColor, const sf::Color &fillColor) :
	_isVisible{true},
	_size{size},
	_value{0.f}
{
	initVisuals(backgroundColor, fillColor);
}

UISlider::~UISlider()
{
}

void UISlider::setLocalPosition(const sf::Vector2f & _pos)
{
	UIElement::setLocalPosition(_pos);
}

void UISlider::draw()
{
	if (!_isVisible)
	{
		return;
	}

	_backgroundShape.setPosition(_globalPosition);
	_fillShape.setPosition(_globalPosition - _size / 2.f);

	Display::draw(_backgroundShape);
	Display::draw(_fillShape);
}

void UISlider::setVisible(bool value)
{
	_isVisible = value;
}

void UISlider::setValue(float value)
{
	_value = Util::clamp(value, 0.f, 1.f);
	updateShape();
}

float UISlider::getValue() const
{
	return _value;
}

void UISlider::initVisuals(const sf::Color &bgColor, const sf::Color &fillColor)
{
	_backgroundShape.setSize(_size);
	_backgroundShape.setOrigin(_size / 2.f);
	_backgroundShape.setFillColor(bgColor);

	_fillShape.setSize(sf::Vector2f{_size.x * _value, _size.y});
	_fillShape.setOrigin(sf::Vector2f{ 0.f, 0.f });
	_fillShape.setFillColor(fillColor);
}

void UISlider::updateShape()
{
	_fillShape.setSize(sf::Vector2f{ _size.x * _value, _size.y });
}
