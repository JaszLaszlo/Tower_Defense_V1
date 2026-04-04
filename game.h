#pragma once
#include <iostream>
#include "map.h"
#include "enemy.h"
#include "vec2.h"
#include"tower.h"
#include "graphics.h"
#include "types.h"
#include "wave.h"

class Game
{
	Map map;
	EnemyManager enemyManager;
	TowerManager towerManager;
	WaveManager waveManager;
	int playerHp;
	bool running;
	Vec2<float> mapToWorld(Vec2<int> gridPos) const;
	void cleanUpEnemies();
public:
	Game(int maxEnemies, std::istream& mapIs, std::istream& waveIs);
	void update(float dt);
	void draw(Graphics& g) const;
	void handleTowerBuildRequest(float mx, float my, TowerType type);
	void startNextWave() { waveManager.startNextWave(); }
};