#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(IWeaponReactor * reactor) :
	IPlayerWeapon {reactor}
{
}

BasicWeapon::~BasicWeapon()
{
}

void BasicWeapon::shootWeapon()
{

}

void BasicWeapon::setDirection(sf::Vector2f dir)
{
	_direction = dir;
}
