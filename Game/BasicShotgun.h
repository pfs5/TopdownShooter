#pragma once
#include "BasicWeapon.h"

class BasicShotgunDescription : public BasicWeaponDescription
{
public:
	int burstBulletCount = 1;

	BasicShotgunDescription& setRateOfFire(float rof);
	BasicShotgunDescription& setRecoil(float rec);
	BasicShotgunDescription& setProjectileMass(float mass);
	BasicShotgunDescription& setDoesPenetrate(bool value);
	BasicShotgunDescription& setBurstBulletCount(int value);
};

class BasicShotgun : public BasicWeapon
{
public:
	BasicShotgun(IWeaponReactor* reactor, const BasicShotgunDescription &description = BasicShotgunDescription{});

protected:
	void shoot() const override;

private:
	BasicShotgunDescription _description;
};