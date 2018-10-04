#include "BasicShotgun.h"
#include "Projectile.h"
#include "GameStateManager.h"
#include "VectorOperations.h"

BasicShotgunDescription & BasicShotgunDescription::setRateOfFire(float rof)
{
	BasicWeaponDescription::setRateOfFire(rof);
	return *this;
}

BasicShotgunDescription & BasicShotgunDescription::setRecoil(float rec)
{
	BasicWeaponDescription::setRecoil(rec);
	return *this;
}

BasicShotgunDescription & BasicShotgunDescription::setProjectileMass(float mass)
{
	BasicWeaponDescription::setProjectileMass(mass);
	return *this;
}

BasicShotgunDescription & BasicShotgunDescription::setDoesPenetrate(bool value)
{
	BasicWeaponDescription::setDoesPenetrate(value);
	return *this;
}

BasicShotgunDescription& BasicShotgunDescription::setBurstBulletCount(int value)
{
	burstBulletCount = value;
	return *this;
}

BasicShotgun::BasicShotgun(IWeaponReactor * reactor, const BasicShotgunDescription & description) :
	BasicWeapon{ reactor, description }, _description{ description }
{
}

void BasicShotgun::shoot() const
{
	for (int i = 0; i < _description.burstBulletCount; ++i)
	{
		auto projectile = dynamic_cast<Projectile*>(GameStateManager::instantiate(&Projectile{ _description.projectileMass, _description.doesPenetrate }, 2));
		projectile->setLocalPosition(_globalPosition);

		sf::Vector2f dir = VectorOperations::rotate(_direction, Util::randomFloat(-10.f, 10.f));
		projectile->shootProjectile(dir * Util::randomFloat(900.f, 1100.f));
	}

	_reactor->onShoot();
	_reactor->applyKnockback(-_direction * _description.recoil);
}
