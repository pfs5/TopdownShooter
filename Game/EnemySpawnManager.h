#pragma once
#include "GameObject.h"
#include "IEnemyDestroyObserver.h"

class EnemySpawnManager : public GameObject, public IEnemyDestroyObserver
{
public:
	EnemySpawnManager(GameObject *enemy, int maxEnemies = 20);
	~EnemySpawnManager();

#pragma region Getters and setters
	void setSpawnPositions(const std::initializer_list<sf::Vector2f> &value);
	std::vector<sf::Vector2f> getSpawnPositions() const;
	void setSpawnRate(float value);
	float getSpawnRate() const;
	void setIsSpawning(bool value);
	bool isSpawning() const;
#pragma endregion

// IEnemyDestroyObserver
public:
	void onDestroy() override;

// GameObject
public:
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;

private:
	GameObject* _enemyPrefab;

	std::vector<sf::Vector2f> _spawnPositions;
	float _spawnPeriod;
	bool _isSpawning;
	int _maxEnemies;

	float _counter;
	unsigned int _currentNumberOfEnemies;

	sf::Sprite _spawnPositionMarkerSprite;

private:
	void spawnEnemy();
};

