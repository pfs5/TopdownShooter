#include "BoxCharacter.h"
#include "Display.h"
#include "Input.h"
#include "Debug.h"

BoxCharacter::BoxCharacter() {
	// Init visual
	m_shape.setFillColor(sf::Color{150, 150, 150});
	m_shape.setSize(sf::Vector2f{ 50.f, 50.f });
	
}

void BoxCharacter::update(float _dt) {
	movement();
}

void BoxCharacter::draw() {
	Display::draw(m_shape);
}

void BoxCharacter::onCollision(Collider * _this, Collider * _other) {
}

GameObject * BoxCharacter::clone() {
	return new BoxCharacter();
}

void BoxCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	for (const auto &col : m_colliders) { col->setPosition(_pos); }

	m_shape.setPosition(_pos);
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
