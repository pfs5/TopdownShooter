#pragma once
#include "IMap.h"
#include <string>
#include <SFML/Graphics/Sprite.hpp>

class PrototypeMap1 : public IMap
{
public:
	PrototypeMap1(float scale = 1.f);

	void update(float dt) override;
	void draw() override;

private:
	const std::string TEX_NAME_BACKGROUND = "prototype-1-map-1-background";
	const std::string TEX_NAME_CLOUDS_BACK = "prototype-1-map-1-clouds-back";
	const std::string TEX_NAME_CLOUDS_FRONT = "prototype-1-map-1-clouds-front";
	const std::string TEX_NAME_PLATFORMS = "prototype-1-map-1-platforms";

	const float CLOUD_SPEED_BACK = -20.f;
	const float CLOUD_SPEED_FRONT = -50.f;

	sf::Sprite _backgroundSprite;
	sf::Sprite _cloudsBackSprite;
	sf::Sprite _cloudsFrontSprite;
	sf::Sprite _platformsSprite;

	float _cloudsBackPos;
	float _cloudsFrontPos;
};
