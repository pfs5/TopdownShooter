#include "BasicWeapon.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Projectile.h"
#include "FloatOperations.h"

BasicWeapon::BasicWeapon(IWeaponReactor * reactor, const BasicWeaponDescription &description) :
	IPlayerWeapon {reactor},
	_description{description},
	_firePeriod{1.f / description.rateOfFire},
	_fireTimer{0.f},
	_isShooting{false}
{
}

BasicWeapon::~BasicWeapon()
{
}

void BasicWeapon::shootWeapon()
{
	shoot();
}

void BasicWeapon::setIsShooting(bool value)
{
	_isShooting = value;
}

void BasicWeapon::update(float dt)
{
	if (_isShooting)
	{
		_fireTimer += dt;

		if (_fireTimer > _firePeriod)
		{
			_fireTimer = 0.f;
			shoot();
		}
	}
}

void BasicWeapon::setDirection(sf::Vector2f dir)
{
	_direction = dir;
}

void BasicWeapon::setLocalPosition(const sf::Vector2f& _pos)
{
	IPlayerWeapon::setLocalPosition(_pos);
}

void BasicWeapon::shoot() const
{
	auto projectile = dynamic_cast<Projectile*>(GameStateManager::instantiate(&Projectile{}));
	projectile->setLocalPosition(_globalPosition);
	projectile->shootProjectile(_direction * 500.f);

	_reactor->onShoot();
	_reactor->applyKnockback(-_direction * _description.recoil);
}

BasicWeaponDescription & BasicWeaponDescription::setRateOfFire(float rof)
{
	rateOfFire = rof;
	return *this;
}

BasicWeaponDescription & BasicWeaponDescription::setRecoil(float rec)
{
	recoil = rec;
	return *this;
}
