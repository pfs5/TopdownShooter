#pragma once
#include "IPlayerWeapon.h"

class BasicWeapon : public IPlayerWeapon
{
public:
	BasicWeapon(IWeaponReactor* reactor);
	~BasicWeapon();

	void shootWeapon() override;
	void setDirection(sf::Vector2f dir) override;

	void setLocalPosition(const sf::Vector2f& _pos) override;
private:
	sf::Vector2f _direction;
};
