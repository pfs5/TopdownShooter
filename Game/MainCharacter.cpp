#include "MainCharacter.h"
#include "Input.h"
#include "Display.h"
#include "ResourceManager.h"
#include "VectorOperations.h"

#include "Debug.h"

MainCharacter::MainCharacter()
{
	setObjectLayer("Player");

	auto playerTex = ResourceManager::getTextureStatic(TEX_NAME_PLAYER);
	_sprite.setTexture(*playerTex);
	_sprite.setOrigin(VectorOperations::utof(playerTex->getSize()) / 2.f);
	_sprite.setScale(SIZE_SCALE, SIZE_SCALE);

	auto crosshairTex = ResourceManager::getTextureStatic(TEX_NAME_CROSSHAIR);
	_crosshairSprite.setTexture(*crosshairTex);
	_crosshairSprite.setOrigin(VectorOperations::utof(crosshairTex->getSize()) / 2.f);
	_crosshairSprite.setScale(SIZE_SCALE, SIZE_SCALE);

	auto baseCol = createCollider(sf::Vector2f{ 0.f , 0.f }, VectorOperations::utof(playerTex->getSize()) * SIZE_SCALE);
	auto rb = createRigidBody();
	rb->setGravity(false);

	baseCol->setStatic(false);
	baseCol->setTrigger(false, rb);
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::update(float _dt)
{
	moveAction(_dt);
	aimAction();
}

void MainCharacter::draw()
{
	Display::draw(_sprite);
	Display::draw(_crosshairSprite);
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
	_position = _pos;

	_sprite.setPosition(_pos);
	_crosshairSprite.setPosition(_pos + _aimDirection * CROSSHAIR_DISTANCE);


	for(const auto &col : _colliders)
	{
		col->setPosition(_pos);
	}
}

void MainCharacter::moveAction(float dt)
{
	float dx = 0.f;
	float dy = 0.f;

	if (Input::getKey(Input::W)) { dy -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::A)) { dx -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::S)) { dy += MOVEMENT_SPEED; }
	if (Input::getKey(Input::D)) { dx += MOVEMENT_SPEED; }

	move(sf::Vector2f{ dx, dy } * dt);
}

void MainCharacter::aimAction()
{
	auto mousePos = static_cast<sf::Vector2f>(Input::getMousePosition());
	auto screenPos = Display::worldToScreenPosition(getPosition());

	_aimDirection = mousePos - screenPos;
	_aimDirection /= VectorOperations::norm(_aimDirection);
}
