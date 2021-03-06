#include "BoxCharacter.h"
#include "Display.h"
#include "Input.h"
#include "VectorOperations.h"
#include "GameStateManager.h"
#include "BasicShot.h"
#include "Debug.h"
#include "Rendering.h"

BoxCharacter::BoxCharacter(PLAYER_NUMBER _playerNo) : m_playerNo{ _playerNo } {
	// Init visual
	m_shape.setFillColor(sf::Color{150, 150, 150});
	m_shape.setSize(sf::Vector2f{ 50.f, 50.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	
	m_aimShape.setFillColor(sf::Color::Transparent);
	m_aimShape.setOutlineColor(sf::Color::Red);
	m_aimShape.setOutlineThickness(3.f);
	m_aimShape.setRadius(2.f);
	m_aimShape.setOrigin(m_aimShape.getRadius() / 2.f, m_aimShape.getRadius() / 2.f);

	// Physics
	auto baseCol = createCollider();
	baseCol->setSize(m_shape.getSize());

	auto rb = createRigidBody();
	rb->setGravity(false);
}

void BoxCharacter::update(float _dt) {
	if (m_playerNo == PlayerOne) {
		movement();
		aim();
		shoot();
	}

	// Drag
	auto vel = getRigidBody()->getVelocity() * RECOIL_DRAG_COEFF;
	getRigidBody()->setVelocity(vel);
}

void BoxCharacter::draw() {
	Rendering::draw(m_shape);
	Rendering::draw(m_aimShape);
}

void BoxCharacter::onCollision(Collider * _this, Collider * _other) {
	static const int bulletOneLayer = PhysicsLayers::layerNumber("Bullet1");
	static const int bulletTwoLayer = PhysicsLayers::layerNumber("Bullet2");

	int otherLayerNo = _other->getGameObject()->getLayerNumber();
	
	if (m_playerNo == PlayerOne && otherLayerNo == bulletTwoLayer ||
		m_playerNo == PlayerTwo && otherLayerNo == bulletOneLayer) {

		// Hit by bullet
		auto bullet = dynamic_cast<BasicShot*>(_other->getGameObject());
		if (bullet) {
			float hitPower = bullet->getHitPower();
			sf::Vector2f recoilDir = bullet->getDirection();
			bullet->destroy();

			// Recoil
			_rigidBody->setVelocity(recoilDir * hitPower);
		}
	}
}

GameObject * BoxCharacter::clone() {
	return new BoxCharacter(m_playerNo);
}

void BoxCharacter::setLocalPosition(const sf::Vector2f &_pos) {
	GameObject::setLocalPosition(_pos);
	
	_localPosition = _pos;
	for (const auto &col : _colliders) { col->setPosition(_pos); }

	m_shape.setPosition(_pos);
	m_aimShape.setPosition(_pos + m_aimDirection * AIM_VISUAL_DISTANCE);
}

void BoxCharacter::movement() {
	float SPEED = 7.f;
	
	float dx = 0.f;
	float dy = 0.f;

	if (Input::getKey(Input::W)) { dy -= SPEED; }
	if (Input::getKey(Input::A)) { dx -= SPEED; }
	if (Input::getKey(Input::S)) { dy += SPEED; }
	if (Input::getKey(Input::D)) { dx += SPEED; }

	move(sf::Vector2f{dx, dy});
}

void BoxCharacter::aim() {
	auto mousePos = static_cast<sf::Vector2f>(Input::getMousePosition());
	m_aimDirection = mousePos - getLocalPosition();
	m_aimDirection /= VectorOperations::norm(m_aimDirection);
}

void BoxCharacter::shoot() {
	if (Input::getKeyDown(Input::SPACE)) {
		auto newShot = dynamic_cast<BasicShot*>(GameStateManager::instantiate(&BasicShot{}));
		if (newShot) {
			auto pos = getLocalPosition();
			newShot->setLocalPosition(getLocalPosition());
			newShot->setObjectLayer("Bullet1");
			newShot->shoot(m_aimDirection * 500.f);
		}
	}
}
