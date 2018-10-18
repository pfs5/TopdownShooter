#include "BoxObject.h"
#include "ResourceManager.h"
#include "Rendering.h"
#include "VectorOperations.h"

BoxObject::BoxObject(const sf::Vector2f &size, float mass) :
	_size{size}
{
	sf::Texture* tex = ResourceManager::getTextureStatic("box");

	_sprite.setTexture(*tex);

	sf::Vector2f scale = sf::Vector2f
	{
		size.x / tex->getSize().x,
		size.y / tex->getSize().y
	};

	_sprite.setScale(scale);

	RigidBody *rb = createRigidBody();
	rb->setMass(mass);
	rb->setGravity(false);
	rb->setBounceFactor(.8f);
	rb->setDragCoefficient(1);

	Collider* baseCol = createCollider(size / 2.f, size);
	baseCol->setStatic(false);
	baseCol->setTrigger(false, rb);
} 

BoxObject::~BoxObject()
{
}

void BoxObject::update(float _dt)
{
}

void BoxObject::draw()
{
	Rendering::draw(_sprite);
}

void BoxObject::onCollision(Collider* _this, Collider* _other)
{
}

GameObject* BoxObject::clone()
{
	return new BoxObject{ _size, getRigidBody()->getMass() };
}

void BoxObject::setLocalPosition(const sf::Vector2f & _pos)
{
	GameObject::setLocalPosition(_pos);
	_sprite.setPosition(getGlobalPosition());
}
