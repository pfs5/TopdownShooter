#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
#pragma region Parameters
	const float CAMERA_LERP_SPEED = 3.f;
#pragma endregion

	sf::View _view;
	const GameObject * const _playerObject;
public:
	Camera(const GameObject * const playerObject = nullptr);
	~Camera();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;
};

