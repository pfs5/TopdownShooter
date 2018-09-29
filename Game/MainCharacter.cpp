#include "MainCharacter.h"
#include "Input.h"
#include "Display.h"
#include "ResourceManager.h"
#include "VectorOperations.h"

#include "Debug.h"
#include "GameStateManager.h"
#include "Projectile.h"
#include "BasicWeapon.h"
#include "Util.h"

#include <memory>
#include <math.h>

MainCharacter::MainCharacter() :
	_currentWeapon{0},
	_externalVelocity{sf::Vector2f{0.f, 0.f}},
	_initialRecoilVelocity{sf::Vector2f{0.f, 0.f}},
	_recoilTimer{0.f}
{
	setObjectLayer("Player");

	// Init visuals
	auto playerTex = ResourceManager::getTextureStatic(TEX_NAME_PLAYER);
	_sprite.setTexture(*playerTex);
	_sprite.setOrigin(VectorOperations::utof(playerTex->getSize()) / 2.f);
	_sprite.setScale(SIZE_SCALE, SIZE_SCALE);

	auto crosshairTex = ResourceManager::getTextureStatic(TEX_NAME_CROSSHAIR);
	_crosshairSprite.setTexture(*crosshairTex);
	_crosshairSprite.setOrigin(VectorOperations::utof(crosshairTex->getSize()) / 2.f);
	_crosshairSprite.setScale(SIZE_SCALE, SIZE_SCALE);

	// Init physics
	auto baseCol = createCollider(sf::Vector2f{ 0.f , 0.f }, VectorOperations::utof(playerTex->getSize()) * SIZE_SCALE);
	auto rb = createRigidBody();
	rb->setGravity(false);

	baseCol->setStatic(false);
	baseCol->setTrigger(false, rb);

	// Init weapons
	_weapons.push_back(std::make_unique<BasicWeapon>(this));

	for (const auto &wep : _weapons)
	{
		attachChild(wep.get());
	}
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::update(float _dt)
{
	moveAction(_dt);
	aimAction();
	shootAction();

	applyDrag(_dt);
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

void MainCharacter::setLocalPosition(const sf::Vector2f & _pos)
{
	GameObject::setLocalPosition(_pos);

	_sprite.setPosition(_globalPosition);
	_crosshairSprite.setPosition(_globalPosition + _aimDirection * CROSSHAIR_DISTANCE);


	for(const auto &col : _colliders)
	{
		col->setPosition(_globalPosition);
	}
}

void MainCharacter::onShoot()
{
}

void MainCharacter::applyKnockback(sf::Vector2f velocity)
{
	_initialRecoilVelocity = velocity;
	_recoilTimer = 0.f;
}

void MainCharacter::moveAction(float dt)
{
	float dx = 0.f;
	float dy = 0.f;

	if (Input::getKey(Input::W)) { dy -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::A)) { dx -= MOVEMENT_SPEED; }
	if (Input::getKey(Input::S)) { dy += MOVEMENT_SPEED; }
	if (Input::getKey(Input::D)) { dx += MOVEMENT_SPEED; }

	// Update velocity
	_movementVelocity.x = dx + _externalVelocity.x;
	_movementVelocity.y = dy + _externalVelocity.y;

	// Update external velocity
	/*if (_movementVelocity.x * _externalVelocity.x < 0.f)
	{
		if (_externalVelocity.x < 0.f)
		{
			_externalVelocity.x = std::min(0.f, _externalVelocity.x + _movementVelocity.x * dt);
		} else
		{
			_externalVelocity.x = std::max(0.f, _externalVelocity.x + _movementVelocity.x * dt);
		}
	}

	if (_movementVelocity.y * _externalVelocity.y < 0.f)
	{
		if (_externalVelocity.y < 0.f)
		{
			_externalVelocity.y = std::min(0.f, _externalVelocity.y + _movementVelocity.y * dt);
		}
		else
		{
			_externalVelocity.y = std::max(0.f, _externalVelocity.y + _movementVelocity.y * dt);
		}
	}*/

	move(_movementVelocity * dt);
}

void MainCharacter::aimAction()
{
	auto mousePos = static_cast<sf::Vector2f>(Input::getMousePosition());
	auto screenPos = Display::worldToScreenPosition(getLocalPosition());

	_aimDirection = mousePos - screenPos;
	_aimDirection /= VectorOperations::norm(_aimDirection);
}

void MainCharacter::shootAction()
{
	if (Input::getKeyDown(CONTROL_SHOOT))
	{
		_weapons[_currentWeapon]->setDirection(_aimDirection);
		_weapons[_currentWeapon]->shootWeapon();
	}
}

void MainCharacter::applyDrag(float dt)
{
	// Linear damping
	_externalVelocity = (-_initialRecoilVelocity / RECOIL_DAMP_TIME) * _recoilTimer + _initialRecoilVelocity;

	_recoilTimer = std::min(RECOIL_DAMP_TIME, _recoilTimer + dt);
}
