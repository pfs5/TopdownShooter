#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "UILine.h"

class PlayerCameraController : public GameObject
{
public:
	PlayerCameraController(ITransformable* playerTransform, Camera* camera);
	~PlayerCameraController();

// GameObject
public:
	void update(float _dt) override;

	void draw() override;

	void onCollision(Collider * _this, Collider * _other) override;

	GameObject * clone() override;

private:
	ITransformable* _playerTransform;
	Camera* _camera;

	sf::Vector2f _lastPlayerPosition;
	sf::Vector2f _currentDirection;
	sf::Vector2f _targetCamPosition;

	UILine _directionLine;

private:
	void updateDirection(float dt);
	void moveCamera(float dt);
};

