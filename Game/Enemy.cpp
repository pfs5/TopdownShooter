#include "Enemy.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "PhysicsEngine.h"
#include "Debug.h"
#include "ParticleSystem.h"
#include "GameStateManager.h"

Enemy::Enemy(const MainCharacter * mainCharacter, float hp) :
	_isTrackingPlayer{false},
	_externalVelocity{sf::Vector2f{0.f, 0.f}},
	_initialRecoilVelocity{sf::Vector2f{0.f, 0.f}},
	_recoilTimer{0.f},
	_invincibilityTimer{0.f},
	_hp{hp},
	_testLine{2.f}
{
	_mainCharacter = mainCharacter;

	auto enemyTex = ResourceManager::getTextureStatic(TEX_NAME_ENEMY);
	_sprite.setTexture(*enemyTex);
	_sprite.setColor(sf::Color(255, 0, 0));
	_sprite.setOrigin(VectorOperations::utof(enemyTex->getSize()) / 2.f);
	_sprite.setScale(SIZE_SCALE, SIZE_SCALE);

	auto baseCol = createCollider(sf::Vector2f{ 0.f , 0.f }, VectorOperations::utof(enemyTex->getSize()) * SIZE_SCALE);
	auto rb = createRigidBody();
	rb->setGravity(false);

	baseCol->setStatic(false);
	baseCol->setTrigger(false, rb);
}


Enemy::~Enemy()
{
}

void Enemy::update(float _dt)
{
	if (!_mainCharacter)
		return;

	// move towards main character
	followPlayer(_dt);
	applyDrag(_dt);

	if (_invincibilityTimer < INVINCIBILITY_TIME)
	{
		_invincibilityTimer += _dt;
	}
}

void Enemy::draw()
{
	Display::draw(_sprite);

	_testLine.draw();
}

void Enemy::onCollision(Collider * _this, Collider * _other)
{
}

GameObject * Enemy::clone()
{
	return nullptr;
}

void Enemy::setLocalPosition(const sf::Vector2f & _pos)
{
	GameObject::setLocalPosition(_pos);

	_sprite.setPosition(_globalPosition);

	for (const auto &col : _colliders)
	{
		col->setPosition(_globalPosition);
	}
}

void Enemy::onHit(ProjectileInfo projectileInfo)
{
	if (_invincibilityTimer < INVINCIBILITY_TIME)
	{
		return;
	}

	_invincibilityTimer = 0.f;

	_initialRecoilVelocity = projectileInfo.velocity * projectileInfo.mass * 10.f;
	_recoilTimer = 0.f;

	_hp -= projectileInfo.mass * VectorOperations::norm(projectileInfo.velocity);

	if (_hp < 0.f)
	{
		spawnExplosion();
		GameStateManager::destroyObject(this);
	}
}

void Enemy::followPlayer(float dt)
{
	RaycastData raycastData = PhysicsEngine::getInstance().raycast2(getGlobalPosition(),
		_mainCharacter->getGlobalPosition() - getGlobalPosition(),
		std::vector<std::string>{"Player", "Map"});

	if (raycastData.hitCollider != nullptr && raycastData.hitCollider->getGameObject()->getObjectTag() == "Player")
	{
		auto playerPosition = _mainCharacter->getGlobalPosition();
		auto playerEnemyDirection = playerPosition - getGlobalPosition();

		if (VectorOperations::norm(playerEnemyDirection) <= ATTACK_DISTANCE)
			return;

		playerEnemyDirection = VectorOperations::normalize(playerEnemyDirection);
		getRigidBody()->setVelocity(playerEnemyDirection * MOVEMENT_SPEED + _externalVelocity);

		_isTrackingPlayer = true;
	} else
	{
		_isTrackingPlayer = false;
		getRigidBody()->setVelocity(_externalVelocity);
	}

	_testLine.setVisible(_isTrackingPlayer);

	_testLine.setStartPoint(getGlobalPosition());
	_testLine.setEndPoint(raycastData.hitPoint);
}

void Enemy::applyDrag(float dt)
{
	// Linear damping
	_externalVelocity = (-_initialRecoilVelocity / RECOIL_DAMP_TIME) * _recoilTimer + _initialRecoilVelocity;

	_recoilTimer = std::min(RECOIL_DAMP_TIME, _recoilTimer + dt);
}

void Enemy::spawnExplosion()
{
	ParticleSystem explosion {
		ResourceManager::getTextureStatic("default"),
		50u,
		true,
		true
	};

	explosion.setInitialAcceleration(sf::Vector2f{ 0.f, 0.f });
	explosion.setInitialVelocity(sf::Vector2f{ -200.f, -200.f }, sf::Vector2f{ 200.f, 200.f });
	explosion.setLifetime(3.f);
	explosion.setSpawnRate(0.5f);
	explosion.setScale(sf::Vector2f{ 0.2f, 0.2f });
	explosion.setAlphaInTime(new Functions::LinearFunction{ Functions::LinearFunction::twoPoints(sf::Vector2f{ 0.f, 1.f }, sf::Vector2f{ .5f, 0.f }) });
	explosion.setDestroyTime(10.f);

	auto newExpl = GameStateManager::instantiate(&explosion);
	newExpl->setLocalPosition(getGlobalPosition());
}
