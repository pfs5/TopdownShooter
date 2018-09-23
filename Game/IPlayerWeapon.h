#pragma once
#include "IWeaponReactor.h"
/**
 *		Interface representing a weapon held by the player
 */
class IPlayerWeapon
{
public:
	IPlayerWeapon(IWeaponReactor * reactor) : _reactor{ reactor }{}
	virtual ~IPlayerWeapon() = default;

	virtual void shootWeapon() = 0;

	virtual void setDirection(sf::Vector2f dir) = 0;

private:
	IWeaponReactor * _reactor;
};