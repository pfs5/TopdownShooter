#include "Enemy.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "PhysicsEngine.h"
#include "Debug.h"

Enemy::Enemy(const MainCharacter * mainCharacter) :
	_isTrackingPlayer{false},
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

void Enemy::onShoot()
{
}

void Enemy::applyKnockback(sf::Vector2f velocity)
{
}

void Enemy::followPlayer(float dt)
{
	RaycastData raycastData = PhysicsEngine::getInstance().raycast2(getGlobalPosition(),
		_mainCharacter->getGlobalPosition() - getGlobalPosition(),
		std::vector<std::string>{"Player", "Map"});

	_isTrackingPlayer = false;
	if (raycastData.hitCollider != nullptr && raycastData.hitCollider->getGameObject()->getObjectTag() == "Player")
	{
		auto playerPosition = _mainCharacter->getGlobalPosition();
		auto playerEnemyDirection = playerPosition - getGlobalPosition();

		if (VectorOperations::norm(playerEnemyDirection) <= ATTACK_DISTANCE)
			return;

		playerEnemyDirection = VectorOperations::normalize(playerEnemyDirection);
		move(playerEnemyDirection * MOVEMENT_SPEED * dt);

		_isTrackingPlayer = true;
	}

	_testLine.setVisible(_isTrackingPlayer);

	_testLine.setStartPoint(getGlobalPosition());
	_testLine.setEndPoint(raycastData.hitPoint);
}
