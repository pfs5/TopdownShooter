#include "PrototypeMap2.h"
#include "ResourceManager.h"
#include "json.h"
#include "Display.h"
#include "Debug.h"

#include <fstream>

PrototypeMap2::PrototypeMap2(float scale) :
	_scale {scale}
{
	// Init sprite
	auto mapTex = ResourceManager::getTextureStatic(MAP_TEXT_NAME);
	_mapSprite.setTexture(*mapTex);
	_mapSprite.setScale(scale, scale);

	loadColliders();
}

PrototypeMap2::~PrototypeMap2()
{
}

void PrototypeMap2::update(float dt)
{
}

void PrototypeMap2::draw()
{
	Display::draw(_mapSprite);
}

void PrototypeMap2::onCollision(Collider * _this, Collider * _other)
{
}

GameObject* PrototypeMap2::clone()
{
	return new PrototypeMap2(_scale);
}

void PrototypeMap2::setPosition(const sf::Vector2f& _pos)
{
}

void PrototypeMap2::loadColliders()
{
	std::string dataPath = ResourceManager::getRawDataPath(COLLIDERS_DATAFILE_NAME);
	std::ifstream dataFile{ dataPath };

	if (dataFile.is_open())
	{
		nlohmann::json data;
		dataFile >> data;

		for (const auto &col : data["colliders"])
		{
			float x = col["x"];
			float y = col["y"];
			float width = col["width"];
			float height = col["height"];

			auto newCol = createCollider(sf::Vector2f{x, y} , sf::Vector2f{width, height});
		}
	} else
	{
		Debug::logError("[PrototypeMap2] Error loading colliders. Error opening file " + dataPath + ".");
		return;
	}
}
