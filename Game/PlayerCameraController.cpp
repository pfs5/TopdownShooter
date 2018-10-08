#include "PlayerCameraController.h"



PlayerCameraController::PlayerCameraController(ITransformable* playerTransform, Camera* camera):
	_playerTransform{playerTransform},
	_camera{camera}
{
}


PlayerCameraController::~PlayerCameraController()
{
}

void PlayerCameraController::update(float _dt)
{
	updateDirection(_dt);
	moveCamera(_dt);
}

void PlayerCameraController::draw()
{
	_directionLine.draw();
}

void PlayerCameraController::onCollision(Collider * _this, Collider * _other)
{
}

GameObject * PlayerCameraController::clone()
{
	return new PlayerCameraController{_playerTransform, _camera};
}

void PlayerCameraController::updateDirection(float dt)
{
	sf::Vector2f newDirection = (_playerTransform->getGlobalPosition() - _lastPlayerPosition) * dt;
	_lastPlayerPosition = _playerTransform->getGlobalPosition();

	float directionSmoothness = 0.99f;
	_currentDirection = _currentDirection * directionSmoothness + newDirection * (1.f - directionSmoothness);
	_targetCamPosition = _playerTransform->getGlobalPosition() + _currentDirection * 2e4f;

	_directionLine.setStartPoint(_playerTransform->getGlobalPosition());
	_directionLine.setEndPoint(_targetCamPosition);
}

void PlayerCameraController::moveCamera(float dt)
{
	sf::Vector2f moveVector = (_targetCamPosition - _camera->getGlobalPosition()) * 0.01f;
	_camera->move(moveVector);
}
