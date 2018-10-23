#include "AnimationTesterObject.h"
#include "Input.h"
#include "FloatOperations.h"

AnimationTesterObject::AnimationTesterObject() :
	_isMoving {false}
{
	_animation.load("dummy-character", true);
	_animation.setSize(sf::Vector2f{ 100.f, 100.f });
}

AnimationTesterObject::~AnimationTesterObject()
{
}

void AnimationTesterObject::update(float _dt)
{
	_animation.update(_dt);

	const float speed = 100.f;

	float dx = 0.f;
	dx += Input::getKey(Input::D) ? speed : 0.f;
	dx += Input::getKey(Input::A) ? -speed : 0.f;

	if (FloatOperations::compare(dx, 0.f) != 0)
	{
		// Start move
		if (!_isMoving)
		{
			_isMoving = true;
			_animation.setTrigger("start-walk", true);
		}
	}
	else
	{
		// Stop move
		if (_isMoving)
		{
			_isMoving = false;
			_animation.setTrigger("stop-walk", true);
		}
	}

	move(sf::Vector2f{ dx, 0.f } *_dt);
}

void AnimationTesterObject::draw()
{
	_animation.draw();
}

void AnimationTesterObject::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* AnimationTesterObject::clone()
{
	return new AnimationTesterObject();
}

void AnimationTesterObject::setLocalPosition(const sf::Vector2f& _pos)
{
	GameObject::setLocalPosition(_pos);
	_animation.setPosition(getGlobalPosition());
}
