#pragma once
#include <SFML/System/Vector2.hpp>

struct ProjectileInfo
{
	sf::Vector2f velocity;
	float mass;
};

class IProjectileReactor
{
public:
	virtual void onHit(ProjectileInfo projectileInfo) = 0;
};