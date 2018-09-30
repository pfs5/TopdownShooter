#include "Enemy.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"



Enemy::Enemy(const MainCharacter * mainCharacter, sf::Color color) : Enemy(color)
{
	_mainCharacter = mainCharacter;
}

Enemy::Enemy(sf::Color color)
{
	auto enemyTex = ResourceManager::getTextureStatic(TEX_NAME_ENEMY);
	_sprite.setTexture(*enemyTex);
	_sprite.setColor(color);
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

void Enemy::attack(const MainCharacter * mainCharacter)
{
	_mainCharacter = mainCharacter;
}

void Enemy::followPlayer(float dt)
{
	auto playerPosition = _mainCharacter->getGlobalPosition();
	auto playerEnemyDirection = playerPosition - getGlobalPosition();

	if (VectorOperations::norm(playerEnemyDirection) <= ATTACK_DISTANCE)
		return;

	playerEnemyDirection = VectorOperations::normalize(playerEnemyDirection);
	move(playerEnemyDirection * MOVEMENT_SPEED * dt);
}
