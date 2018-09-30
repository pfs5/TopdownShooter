#pragma once
#include "IWeaponReactor.h"
#include "ITransformable.h"

/**
 *		Interface representing a weapon held by the player
 */
class IPlayerWeapon : public ITransformable
{
public:
	IPlayerWeapon(IWeaponReactor * reactor) : _reactor{ reactor }{}
	virtual ~IPlayerWeapon() = default;

	virtual void shootWeapon() = 0;					// used for single shots
	virtual void setIsShooting(bool value) = 0;
	virtual void update(float dt) = 0;			

	virtual float getReloadPercentage() const = 0;

	virtual void setDirection(sf::Vector2f dir) = 0;

	void setLocalPosition(const sf::Vector2f& _pos) override;

protected:
	IWeaponReactor * _reactor;
};

inline void IPlayerWeapon::setLocalPosition(const sf::Vector2f& _pos)
{
	ITransformable::setLocalPosition(_pos);
}
