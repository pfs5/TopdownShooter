#include "EnemySpawnManager.h"
#include "ResourceManager.h"
#include "Rendering.h"
#include "GameStateManager.h"
#include "VectorOperations.h"
#include "Enemy.h"


EnemySpawnManager::EnemySpawnManager(GameObject *enemy, int maxEnemies) :
	_enemyPrefab{enemy},
	_spawnPeriod{1.f},
	_isSpawning{true},
	_maxEnemies{maxEnemies},
	_counter{ 0.f },
	_currentNumberOfEnemies{0u}
{
	_enemyPrefab->setActive(false);

	sf::Texture* tex = ResourceManager::getTextureStatic("spawn-icon");
	_spawnPositionMarkerSprite.setTexture(*tex);
	_spawnPositionMarkerSprite.setColor(sf::Color{ 230, 230, 230 });
	_spawnPositionMarkerSprite.setScale(.4f, .4f);
}


EnemySpawnManager::~EnemySpawnManager()
{
}

void EnemySpawnManager::setSpawnPositions(const std::initializer_list<sf::Vector2f> &value)
{
	_spawnPositions = std::vector<sf::Vector2f>{ value };
}

std::vector<sf::Vector2f> EnemySpawnManager::getSpawnPositions() const
{
	return _spawnPositions;
}

void EnemySpawnManager::setSpawnRate(float value)
{
	_spawnPeriod = 1.f / value;
}

float EnemySpawnManager::getSpawnRate() const
{
	return 1.f / _spawnPeriod;
}

void EnemySpawnManager::setIsSpawning(bool value)
{
	_isSpawning = value;
}

bool EnemySpawnManager::isSpawning() const
{
	return _isSpawning;
}

void EnemySpawnManager::onDestroy()
{
	--_currentNumberOfEnemies;
}

void EnemySpawnManager::update(float _dt)
{
	if (!_isSpawning || _currentNumberOfEnemies >= _maxEnemies) return;

	_counter += _dt;
	if (_counter > _spawnPeriod)
	{
		spawnEnemy();
		++_currentNumberOfEnemies;
		_counter = 0.f;
	}
}

void EnemySpawnManager::draw()
{
	for (const auto &spawnPos : _spawnPositions)
	{
		_spawnPositionMarkerSprite.setPosition(spawnPos);
		Rendering::draw(_spawnPositionMarkerSprite);
	}
}

void EnemySpawnManager::onCollision(Collider* _this, Collider* _other)
{

}

GameObject* EnemySpawnManager::clone()
{
	return new EnemySpawnManager(_enemyPrefab);
}

void EnemySpawnManager::spawnEnemy()
{
	auto enemy = dynamic_cast<Enemy*>(GameStateManager::instantiate(_enemyPrefab));
	enemy->setLocalPosition(_spawnPositions[Util::randomInt(0, _spawnPositions.size() - 1)]);
	enemy->attachObserver(this);
}
