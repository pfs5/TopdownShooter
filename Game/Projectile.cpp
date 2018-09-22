#include "Projectile.h"
#include "ResourceManager.h"
#include "VectorOperations.h"
#include "Display.h"
#include "Util.h"
#include "Debug.h"

Projectile::Projectile()
{
	// Init sprite
	auto mainTex = ResourceManager::getTextureStatic(TEX_NAME_PROJECTILE);
	_mainSprite.setTexture(*mainTex);
	_mainSprite.setOrigin(VectorOperations::utof(mainTex->getSize()) / 2.f);

	// Init physics
	auto rb = createRigidBody();
	rb->setGravity(false);
}

Projectile::~Projectile()
{
}

void Projectile::update(float _dt)
{
}

void Projectile::draw()
{
	Display::draw(_mainSprite);
}

void Projectile::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* Projectile::clone()
{
	return new Projectile();
}

void Projectile::setPosition(const sf::Vector2f& _pos)
{
	_position = _pos;

	_mainSprite.setPosition(_pos);
}

void Projectile::shootProjectile(const sf::Vector2f & velocity)
{
	// Rotate sprite
	float angle = VectorOperations::vectorAngle(velocity, sf::Vector2f{ 0.f, 1.f });
	angle *= velocity.x > 0.f ? -1.f : 1.f;

	_mainSprite.setRotation(Util::radianToDegree(angle));

	getRigidBody()->setVelocity(velocity);
}
