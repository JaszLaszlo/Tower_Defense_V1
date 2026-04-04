#include "map.h"
#include "enemy.h"
#include "game.h"
#include "graphics.h"
#include "memtrace.h"

Game::Game(int maxEnemies, std::istream& mapIs, std::istream& waveIs) : 
	map(Map()), enemyManager(maxEnemies), 
	towerManager(100), waveManager(),
	playerHp(100), running(true)
														
{
	map.load(mapIs);
	waveManager.load(waveIs);
}
Vec2<float> Game::mapToWorld(Vec2<int> gridPos) const
{
	Vec2<float> pos;
	float tileSize = static_cast<float>(map.getTileSize());
	pos.x = gridPos.x * tileSize + tileSize / 2.0f;
	pos.y = gridPos.y * tileSize + tileSize / 2.0f;
	return pos;
}

void Game::handleTowerBuildRequest(float mx, float my, TowerType type)
{
	int ts = map.getTileSize();
	int gridX = static_cast<int>(mx) / ts;
	int gridY = static_cast<int>(my) / ts;
	if (gridX >= 0 && gridY >= 0 && gridX < map.getWidth() && gridY < map.getHeight())
	{
		if (map.canBuild(gridY, gridX))
		{
			Vec2<float> towerPos(gridX * ts + ts / 2.0f, gridY * ts + ts / 2.0f);
			towerManager.AddTower(type, towerPos);
			map.getTile(gridY, gridX).setType(TileType::NOTBUILDABLE);
		}
		
	}
}
void Game::cleanUpEnemies()
{
	MyArray<Enemy>& enemies = enemyManager.getEnemies();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->isAlive() || enemies[i]->hasReachedEnd(map)) {
			towerManager.notifyEnemyRemoved(enemies[i]);
			enemies.Remove(i);
			i--;
		}
	}
}
void Game::draw(Graphics& g) const
{ 
	map.draw(g);
	enemyManager.Draw(g);
	towerManager.Draw(g);
	
}

void Game::update(float dt)
{
	if (!running) return;
	waveManager.update(dt, enemyManager, map);
	enemyManager.Update(map,dt);
	towerManager.Update(dt, enemyManager.getEnemies());
	cleanUpEnemies();
	if (playerHp <= 0) running = false;
}

