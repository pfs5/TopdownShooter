#pragma once
#include "IPlayerWeapon.h"

class BasicWeapon : public IPlayerWeapon
{
public:
	BasicWeapon(IWeaponReactor* reactor);
	~BasicWeapon();

	void shootWeapon() override;
	void setDirection(sf::Vector2f dir) override;

private:
	sf::Vector2f _direction;
};