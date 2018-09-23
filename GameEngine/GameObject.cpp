#include "GameObject.h"
#include "PhysicsEngine.h"

GameObject::GameObject() :
	_rigidBody{nullptr} {
}

GameObject::~GameObject() {
	if (_rigidBody != nullptr) {
		delete _rigidBody;
	}

	for (Collider * c : _colliders) {
		delete c;
	}
}

void GameObject::setRigidBody(RigidBody * _rb) {
	_rigidBody = _rb;
}

RigidBody * GameObject::getRigidBody() {
	return _rigidBody;
}

void GameObject::addCollider(Collider * _c) {
	_colliders.push_back(_c);
}

void GameObject::move(sf::Vector2f _delta) {
	setPosition(getPosition() + _delta);
}

/**
 * Creates a new rigid body, registers it with the physics engine and attaches to all existing colliders.
 */
RigidBody * GameObject::createRigidBody() {
	_rigidBody = PhysicsEngine::getInstance().createRigidBody(this);
	for (const auto &col : _colliders) { col->setRigidBody(_rigidBody); }

	return _rigidBody;
}

Collider * GameObject::createCollider(const sf::Vector2f &position, const sf::Vector2f &size) {
	Collider * col = PhysicsEngine::getInstance().createCollider(this);
	col->setOffset(position);
	col->setSize(size);
	_colliders.push_back(col);
	if (_rigidBody != nullptr) { col->setRigidBody(_rigidBody); }
	return col;
}

void GameObject::setObjectLayer(std::string layer) {
	int layerNumber = PhysicsLayers::layerNumber(layer);
	_physicsLayer = layerNumber >= 0 ? layerNumber : _physicsLayer;
}

std::string GameObject::getObjectLayer() {
	return PhysicsLayers::layerName(_physicsLayer);
}

int GameObject::getLayerNumber() {
	return _physicsLayer;
}

inline void GameObject::setPosition(const sf::Vector2f & _pos)
{
	ITransformable::setPosition(_pos);

	for (auto &child : _children)
	{
		child->setPosition(_pos);
	}
}
