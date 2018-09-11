#include "Camera.h"
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

Camera::Camera(const GameObject * const playerObject) :
	_view{ playerObject->getPosition(), VectorOperations::utof(Display::getWindow().getSize()) },
	_playerObject {playerObject}
{
	Display::getWindow().setView(_view);
}


Camera::~Camera()
{
}

void Camera::update(float _dt)
{
	// Follow player
	sf::Vector2f newCenter = _view.getCenter() + (_playerObject->getPosition() - _view.getCenter()) * _dt * CAMERA_LERP_SPEED;
	_view.setCenter(newCenter);
	Display::getWindow().setView(_view);
}

void Camera::draw()
{
}

void Camera::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* Camera::clone()
{
	return new Camera{ _playerObject };
}

void Camera::setPosition(const sf::Vector2f & _pos)
{
}
