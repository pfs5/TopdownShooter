#pragma once
#include "IMap.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "GameObject.h"

class PrototypeMap2 : public IMap, public GameObject
{
public:
	PrototypeMap2(float scale = 1.f);
	~PrototypeMap2() override;

	void update(float dt) override;
	void draw() override;

	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;
	void setPosition(const sf::Vector2f& _pos) override;

private:
	/* ---- Members ---- */
	// Constants
	const std::string MAP_TEXT_NAME = "prototype-1-map-2-background";
	const std::string COLLIDERS_DATAFILE_NAME = "prototype-1-map-2-colliders.json";

	// Variables
	float _scale;

	// Sprites
	sf::Sprite _mapSprite;

private:
	/* ---- Functions ---- */
	void loadColliders();
};
