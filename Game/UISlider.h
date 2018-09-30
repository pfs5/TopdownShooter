#pragma once
#include "UIElement.h"
#include <SFML/Graphics/RectangleShape.hpp>

class UISlider : public UIElement
{
public:
	UISlider(const sf::Vector2f &size, const sf::Color &backgroundColor = sf::Color::White, const sf::Color &fillColor = sf::Color::Cyan);
	~UISlider() override;

	void setLocalPosition(const sf::Vector2f& _pos) override;
	void draw() override;
	void setVisible(bool value) override;

	// Slider methods
	void setValue(float value);
	float getValue() const;

private:
	// UI
	bool _isVisible;

	// Data
	sf::Vector2f _size;
	float _value;			// [0, 1] range

	// Visuals
	sf::RectangleShape _backgroundShape;
	sf::RectangleShape _fillShape;

private:
	void initVisuals(const sf::Color &bgColor, const sf::Color &fillColor);
	void updateShape();
};
