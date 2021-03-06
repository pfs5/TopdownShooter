#include "MainCharacter.h"
#include "Input.h"
#include "Display.h"
#include "ResourceManager.h"
#include "VectorOperations.h"

#include "Debug.h"
#include "GameStateManager.h"
#include "BasicWeapon.h"
#include "BasicShotgun.h"
#include "Util.h"

#include <memory>
#include "Rendering.h"

MainCharacter::MainCharacter() :
	_currentWeapon{0},
	_externalVelocity{sf::Vector2f{0.f, 0.f}},
	_initialRecoilVelocity{sf::Vector2f{0.f, 0.f}},
	_recoilTimer{0.f},
	_reloadSlider{ sf::Vector2f{80.f, 10.f}, sf::Color{171, 165, 145}, sf::Color{ 227, 222, 203 } }
{
	setObjectLayer("Player");
	setObjectTag("Player");

	// -------- Init visuals -------- 
	auto playerTex = ResourceManager::getTextureStatic(TEX_NAME_PLAYER);
	_sprite.setTexture(*playerTex);
	_sprite.setOrigin(VectorOperations::utof(playerTex->getSize()) / 2.f);
	_sprite.setScale(SIZE_SCALE, SIZE_SCALE);

	auto crosshairTex = ResourceManager::getTextureStatic(TEX_NAME_CROSSHAIR);
	_crosshairSprite.setTexture(*crosshairTex);
	_crosshairSprite.setOrigin(VectorOperations::utof(crosshairTex->getSize()) / 2.f);
	_crosshairSprite.setScale(SIZE_SCALE, SIZE_SCALE);

	attachChild(&_reloadSlider);
	_reloadSlider.setLocalPosition(sf::Vector2f{ 40.f, -70.f });

	// --------  Init physics -------- 
	auto baseCol = createCollider(sf::Vector2f{ 0.f , 0.f }, VectorOperations::utof(playerTex->getSize()) * SIZE_SCALE);
	auto rb = createRigidBody();
	rb->setGravity(false);
	rb->setMass(100);

	baseCol->setStatic(false);
	baseCol->setTrigger(false, rb);

	// --------  Init weapons -------- 
	BasicWeaponDescription wpnDescSingleShot = BasicWeaponDescription{}.setRateOfFire(0.5f).setRecoil(1000.f).setProjectileMass(0.1f).setDoesPenetrate(true);
	BasicWeaponDescription wpnDescSlowMachineGun = BasicWeaponDescription{}.setRateOfFire(2.f).setRecoil(500.f).setProjectileMass(0.05f);
	BasicWeaponDescription wpnDescFastMachineGun = BasicWeaponDescription{}.setRateOfFire(10.f).setRecoil(100.f).setProjectileMass(0.03f);
	BasicShotgunDescription wpnDescPumpShotgun = BasicShotgunDescription{}.setRateOfFire(0.8f).setRecoil(500.f).setProjectileMass(0.1f).setDoesPenetrate(false).setBurstBulletCount(15);

	_weapons.push_back(std::make_unique<BasicWeapon>(this, wpnDescSingleShot));
	_weapons.push_back(std::make_unique<BasicWeapon>(this, wpnDescSlowMachineGun));
	_weapons.push_back(std::make_unique<BasicWeapon>(this, wpnDescFastMachineGun));
	_weapons.push_back(std::make_unique<BasicShotgun>(this, wpnDescPumpShotgun));

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
	shootAction(_dt);

	handleWeaponSwitching();
	applyDrag(_dt);
}

void MainCharacter::draw()
{
	Rendering::draw(_sprite);
	Rendering::draw(_crosshairSprite);

	_reloadSlider.draw();
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

	getRigidBody()->setVelocity(_movementVelocity);
}

void MainCharacter::aimAction()
{
	auto mousePos = static_cast<sf::Vector2f>(Input::getMousePosition());
	auto screenPos = Display::worldToScreenPosition(getLocalPosition());

	_aimDirection = mousePos - screenPos;
	_aimDirection /= VectorOperations::norm(_aimDirection);
}

void MainCharacter::shootAction(float dt)
{
	_weapons[_currentWeapon]->update(dt);
	_weapons[_currentWeapon]->setDirection(_aimDirection);

	_weapons[_currentWeapon]->setIsShooting(Input::getKey(CONTROL_SHOOT));

	_reloadSlider.setValue(_weapons[_currentWeapon]->getReloadPercentage());
	_reloadSlider.setVisible(_weapons[_currentWeapon]->getReloadPercentage() < 0.999f);
}

void MainCharacter::handleWeaponSwitching()
{
	if (Input::getKeyDown(Input::Num1) && _weapons.size() > 0)
	{
		_currentWeapon = 0;
	}

	if (Input::getKeyDown(Input::Num2) && _weapons.size() > 1)
	{
		_currentWeapon = 1;
	}

	if (Input::getKeyDown(Input::Num3) && _weapons.size() > 2)
	{
		_currentWeapon = 2;
	}

	if (Input::getKeyDown(Input::Num4) && _weapons.size() > 3)
	{
		_currentWeapon = 3;
	}

	if (Input::getKeyDown(Input::Num5) && _weapons.size() > 4)
	{
		_currentWeapon = 4;
	}
}

void MainCharacter::applyDrag(float dt)
{
	// Linear damping
	_externalVelocity = (-_initialRecoilVelocity / RECOIL_DAMP_TIME) * _recoilTimer + _initialRecoilVelocity;

	_recoilTimer = std::min(RECOIL_DAMP_TIME, _recoilTimer + dt);
}
