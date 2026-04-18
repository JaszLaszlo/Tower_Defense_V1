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
	int money;
	bool running;
	Tower* selectedTower;
	void cleanUpEnemies();
public:
	Game(std::istream& mapIs, std::istream& waveIs);
	void update(float dt);
	void draw(Graphics& g) const;
	void handleTowerBuildRequest(float mx, float my, TowerType type);
	void handleTowerUpgrade();
	void startNextWave() { waveManager.startNextWave(); }
	int getPlayerHp() const { return playerHp; }
	int getMoney() const { return money; }
	bool isRunning() const { return running; }
	bool isFinished() const;
	WaveManager& getWaveManager() { return waveManager; }
	Tower* getTowerAt(float mx, float my);
	void sellTower(Tower* t);
	void setSelectedTower(Tower* t) { selectedTower = t; }
	void setHp(int hp) { playerHp = hp; }
	void setMoney(int m) { money = m; }
	Tower* getSelectedTower() const { return selectedTower; }
};