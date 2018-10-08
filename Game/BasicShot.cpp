#include "BasicShot.h"
#include "Display.h"
#include "GameStateManager.h"
#include "VectorOperations.h" 
#include "Debug.h"
#include "Rendering.h"

BasicShot::BasicShot() : m_destructionTime{DESTROY_DELAY} {
	float size = 10.f;

	// Init shape
	m_shape.setRadius(size / 2);
	m_shape.setFillColor(sf::Color{ 200, 200, 200 });
	m_shape.setOrigin(size / 2.f, size / 2.f);

	// Physics
	auto rb = createRigidBody();
	rb->setGravity(false);

	auto baseCol = createCollider();
	baseCol->setSize(sf::Vector2f{ size, size });
}

BasicShot::~BasicShot() {
}

void BasicShot::shoot(sf::Vector2f _direction) {
	getRigidBody()->setVelocity(_direction);
}

float BasicShot::getHitPower() {
	return HIT_POWER;
}

sf::Vector2f BasicShot::getDirection() {
	return getRigidBody()->getVelocity() / VectorOperations::norm(getRigidBody()->getVelocity());
}

void BasicShot::destroy() {
	GameStateManager::destroyObject(this);
}

void BasicShot::update(float _dt) {
	if ((m_destructionTime -= _dt) < 0) {
		GameStateManager::destroyObject(this);
	}
}

void BasicShot::draw() { 
	Rendering::draw(m_shape);
}

void BasicShot::onCollision(Collider * _this, Collider * _other) {
}

GameObject * BasicShot::clone() {
	return new BasicShot();
}

void BasicShot::setLocalPosition(const sf::Vector2f &_pos) {
	GameObject::setLocalPosition(_pos);

	m_shape.setPosition(_pos);

	for (const auto &col : _colliders) { col->setPosition(_pos); }
}
