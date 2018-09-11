#include "MainCharacter.h"
#include "Input.h"
#include "Display.h"

MainCharacter::MainCharacter()
{
	_debugShape.setFillColor(sf::Color{ 150, 150, 150 });
	_debugShape.setOutlineColor(sf::Color{ 100, 100, 100 });
	_debugShape.setRadius(SHAPE_SIZE);
	_debugShape.setOrigin(_debugShape.getRadius() / 2.f, _debugShape.getRadius() / 2.f);
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::update(float _dt)
{
	movement(_dt);
}

void MainCharacter::draw()
{
	Display::draw(_debugShape);
}

void MainCharacter::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* MainCharacter::clone()
{
	return new MainCharacter();
}

void MainCharacter::setPosition(const sf::Vector2f & _pos)
{
	m_position = _pos;

	_debugShape.setPosition(_pos);
}

void MainCharacter::movement(float dt)
{
	float dx = 0.f;
	float dy = 0.f;

	if (Input::getKey(Input::W)) { dy -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::A)) { dx -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::S)) { dy += MOVEMENT_SPEED; }
	if (Input::getKey(Input::D)) { dx += MOVEMENT_SPEED; }

	move(sf::Vector2f{ dx, dy });
}
