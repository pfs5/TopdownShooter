#include "BasicWeapon.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Projectile.h"

BasicWeapon::BasicWeapon(IWeaponReactor * reactor) :
	IPlayerWeapon {reactor}
{
}

BasicWeapon::~BasicWeapon()
{
}

void BasicWeapon::shootWeapon()
{
	auto projectile = dynamic_cast<Projectile*>(GameStateManager::instantiate(&Projectile{}));
	projectile->setLocalPosition(_globalPosition);
	projectile->shootProjectile(_direction * 500.f);
}

void BasicWeapon::setDirection(sf::Vector2f dir)
{
	_direction = dir;
}

void BasicWeapon::setLocalPosition(const sf::Vector2f& _pos)
{
	IPlayerWeapon::setLocalPosition(_pos);
}
