#include "PrototypeMap1.h"
#include "ResourceManager.h"
#include "Display.h"

PrototypeMap1::PrototypeMap1(float scale) :
	_cloudsBackPos {0.f},
	_cloudsFrontPos {0.f}
{
	// Initialize texture
	auto texBackground = ResourceManager::getInstance().getTexture(TEX_NAME_BACKGROUND);
	_backgroundSprite.setTexture(*texBackground);
	_backgroundSprite.setScale(scale, scale);

	auto texCloudsBack = ResourceManager::getInstance().getTexture(TEX_NAME_CLOUDS_BACK);
	texCloudsBack->setRepeated(true);
	_cloudsBackSprite.setTexture(*texCloudsBack);
	_cloudsBackSprite.setScale(scale, scale);

	auto texCloudsFront = ResourceManager::getInstance().getTexture(TEX_NAME_CLOUDS_FRONT);
	texCloudsFront->setRepeated(true);
	_cloudsFrontSprite.setTexture(*texCloudsFront);
	_cloudsFrontSprite.setScale(scale, scale);

	auto texPlatforms = ResourceManager::getInstance().getTexture(TEX_NAME_PLATFORMS);
	_platformsSprite.setTexture(*texPlatforms);
	_platformsSprite.setScale(scale, scale);
}

void PrototypeMap1::update(float dt)
{
	auto texRectBack = sf::IntRect{ _cloudsBackSprite.getTextureRect() };
	_cloudsBackPos += CLOUD_SPEED_BACK * dt;
	texRectBack.left = static_cast<int>(_cloudsBackPos);
	_cloudsBackSprite.setTextureRect(texRectBack);

	auto texRectFront = sf::IntRect{ _cloudsFrontSprite.getTextureRect() };
	_cloudsFrontPos += CLOUD_SPEED_FRONT * dt;
	texRectFront.left = static_cast<int>(_cloudsFrontPos);
	_cloudsFrontSprite.setTextureRect(texRectFront);
}

void PrototypeMap1::draw()
{
	Display::draw(_backgroundSprite);
	Display::draw(_cloudsBackSprite);
	Display::draw(_cloudsFrontSprite);
	Display::draw(_platformsSprite);
}
