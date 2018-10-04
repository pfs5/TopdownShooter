#pragma once
#include "IPlayerWeapon.h"
#include <SFML/Graphics/Color.hpp>

/**
* Class that holds settings for a particular weapon
*/
class BasicWeaponDescription
{
public:
	float rateOfFire = 0.f;							// projectiles per second
	float recoil = 0.f;
	float projectileMass = 0.f;
	bool doesPenetrate = false;

public:
	BasicWeaponDescription& setRateOfFire(float rof);
	BasicWeaponDescription& setRecoil(float rec);
	BasicWeaponDescription& setProjectileMass(float mass);
	BasicWeaponDescription& setDoesPenetrate(bool value);
};

class BasicWeapon : public IPlayerWeapon
{
public:
	BasicWeapon(IWeaponReactor* reactor, const BasicWeaponDescription &description = BasicWeaponDescription{});
	~BasicWeapon();

	void shootWeapon() override;
	void setIsShooting(bool value) override;
	void update(float dt) override;
	float getReloadPercentage() const override;

	void setDirection(sf::Vector2f dir) override;

	void setLocalPosition(const sf::Vector2f& _pos) override;

protected:
	float _firePeriod;

	sf::Vector2f _direction;
	float _fireTimer;
	bool _isShooting;

protected:
	virtual void shoot() const;

private:
	BasicWeaponDescription _description;
};