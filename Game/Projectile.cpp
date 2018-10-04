#include "Projectile.h"
#include "ResourceManager.h"
#include "VectorOperations.h"
#include "Display.h"
#include "Util.h"
#include "Debug.h"
#include "IProjectileReactor.h"
#include "GameStateManager.h"

Projectile::Projectile(float mass, bool doesPenetrate) :
	_counter{0.f},
	_mass{mass},
	_doesPenetrate{doesPenetrate}
{
	setObjectLayer("PlayerProjectile");

	// Init sprite
	auto mainTex = ResourceManager::getTextureStatic(TEX_NAME_PROJECTILE);
	_mainSprite.setTexture(*mainTex);
	_mainSprite.setOrigin(VectorOperations::utof(mainTex->getSize()) / 2.f);

	// Init physics
	auto rb = createRigidBody();
	rb->setGravity(false);

	Collider* baseCollider = createCollider(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{30.f, 30.f});
}

Projectile::~Projectile()
{
}

void Projectile::update(float _dt)
{
	_counter += _dt;
	if (_counter > LIFETIME)
	{
		GameStateManager::destroyObject(this);
	}
}

void Projectile::draw()
{
	Display::draw(_mainSprite);
}

void Projectile::onCollision(Collider* _this, Collider* _other)
{
	auto reactor = dynamic_cast<IProjectileReactor*>(_other->getGameObject());
	if (reactor != nullptr)
	{
		ProjectileInfo info;
		info.velocity = getRigidBody()->getVelocity();
		info.mass = _mass;
		reactor->onHit(info);

		if (!_doesPenetrate)
		{
			GameStateManager::destroyObject(this);
		}
	}
}

GameObject* Projectile::clone()
{
	return new Projectile(_mass, _doesPenetrate);
}

void Projectile::setLocalPosition(const sf::Vector2f& _pos)
{
	GameObject::setLocalPosition(_pos);

	_mainSprite.setPosition(_pos);

	for (auto &col : _colliders)
	{
		col->setPosition(_pos);
	}
}

void Projectile::shootProjectile(const sf::Vector2f & velocity)
{
	// Rotate sprite
	float angle = VectorOperations::vectorAngle(velocity, sf::Vector2f{ 0.f, 1.f });
	angle *= velocity.x > 0.f ? -1.f : 1.f;

	_mainSprite.setRotation(Util::radianToDegree(angle));

	getRigidBody()->setVelocity(velocity);
}
