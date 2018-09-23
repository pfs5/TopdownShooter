#pragma once
#include <SFML/System/Vector2.hpp>

/**
 *	Interface for an object reacting to a weapon e.g. recoil .
 */
class IWeaponReactor
{
public:
	virtual void onShoot() = 0;

	virtual void applyKnockback(sf::Vector2f velocity) = 0;
};