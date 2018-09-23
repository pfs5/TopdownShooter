#pragma once
#include <SFML/System/Vector2.hpp>

class ITransformable
{
public:
	inline virtual void setPosition(const sf::Vector2f &_pos) { _position = _pos; }
	inline const sf::Vector2f &getPosition() const { return _position; }

	protected:
	sf::Vector2f _position;

};
