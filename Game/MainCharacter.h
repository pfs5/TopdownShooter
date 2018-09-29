#pragma once
#include "GameObject.h"
#include "Input.h"
#include "IPlayerWeapon.h"
#include "IWeaponReactor.h"

class MainCharacter : public GameObject, public IWeaponReactor
{
public:
	MainCharacter();
	~MainCharacter();

	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setLocalPosition(const sf::Vector2f &_pos) override;

	// IWeaponReactor
	void onShoot() override;
	void applyKnockback(sf::Vector2f velocity) override;
private:

	/* ------------------------- Members ------------------------------------------------- */
	// ### Constants ### 
	const std::string TEX_NAME_PLAYER = "prototype-1-player";
	const std::string TEX_NAME_CROSSHAIR = "prototype-1-player-crosshair";

	const float SHOOT_SPEED = 500.f;
	const float RECOIL_DAMP_TIME = .5f;

	// ###  Controls ### 
	const Input::KeyCode CONTROL_SHOOT = Input::SPACE;
	const Input::KeyCode CHOOSE_WEAPON_1 = Input::Num1;
	const Input::KeyCode CHOOSE_WEAPON_2 = Input::Num2;
	const Input::KeyCode CHOOSE_WEAPON_3 = Input::Num3;
	const Input::KeyCode CHOOSE_WEAPON_4 = Input::Num4;

	const float MOVEMENT_SPEED = 500.f;
	const float SIZE_SCALE = 0.7f;
	const float CROSSHAIR_DISTANCE = 100.f;

	// ###  Visuals ### 
	sf::Sprite _sprite;
	sf::Sprite _crosshairSprite;

	sf::Vector2f _movementVelocity;
	sf::Vector2f _externalVelocity;
	sf::Vector2f _aimDirection;

	sf::Vector2f _initialRecoilVelocity;
	float _recoilTimer;

	// ###  Weapons ### 
	std::vector<std::unique_ptr<IPlayerWeapon>> _weapons;
	int _currentWeapon;

private:
	/* ------------------------- Functions ------------------------------------------------ */
	void moveAction(float dt);
	void aimAction();
	void shootAction(float dt);

	void handleWeaponSwitching();
	void applyDrag(float dt);
};

