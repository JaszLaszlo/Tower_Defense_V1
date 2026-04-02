#pragma once
#include <iostream>
#include "map.h"
#include "enemy.h"
#include "vec2.h"
#include"tower.h"

class Game
{
	Map map;
	EnemyManager enemyManager;
	TowerManager towerManager;
	int playerHp;
	bool running;
	float spawnIntervalSeconds;
	float spawnTimer;
	Vec2<float> mapToWorld(Vec2<int> gridPos) const;
	void handleSpawning(float dt);
public:
	Game(int maxEnemies, std::istream& is);
	void update(float dt);
	void draw(Graphics& g) const;
	void handleTowerBuildRequest(float mx, float my);
};