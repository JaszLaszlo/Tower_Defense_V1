#include "map.h"
#include "enemy.h"
#include "game.h"
#include "graphics.h"
#include "memtrace.h"

Game::Game(std::istream& mapIs, std::istream& waveIs) : 
	map(), enemyManager(),
	towerManager(), waveManager(),
	playerHp(100), money(200), 
	running(true), selectedTower(nullptr)
														
{
	map.load(mapIs);
	waveManager.load(waveIs);
}


void Game::handleTowerBuildRequest(float mx, float my, TowerType type)
{
	int ts = map.getTileSize();
	Vec2<int> gridPos = Vec2<float>::worldToGrid({ mx, my }, ts);
	if (gridPos.x >= 0 && gridPos.y >= 0 && gridPos.x < map.getWidth() && gridPos.y < map.getHeight())
	{
		if (!map.canBuild(gridPos.y, gridPos.x)) return;
		int cost = towerManager.GetCostForType(type);
		if (money < cost) return;
		Vec2<float> towerPos = Vec2<int>::gridToWorld(gridPos, ts);
		towerManager.AddTower(type, towerPos);
		money -= cost;
		map.getTile(gridPos.y, gridPos.x).setType(TileType::NOTBUILDABLE);
		
	}
}
void Game::cleanUpEnemies()
{
	MyArray<Enemy>& enemies = enemyManager.getEnemies();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->isAlive()) {
			money += enemies[i]->getReward();
			towerManager.notifyEnemyRemoved(enemies[i]);
			enemies.Remove(i);
			i--;
		}
		else if (enemies[i]->hasReachedEnd(map))
		{
			playerHp -= 10; 
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
Tower* Game::getTowerAt(float mx, float my)
{
	Vec2<float> pos(mx, my);
	int ts = map.getTileSize();
	return towerManager.GetTowerAt(pos, ts);

}
void Game::sellTower(Tower* t)
{
	if (t==nullptr) return;
	if (selectedTower == t) selectedTower = nullptr;
	Vec2<float> pos;
	int sell = towerManager.sellTower(t, pos);
	if (sell <= 0) return;
	money += sell;
	int ts = map.getTileSize();
	Vec2<int> gridPos = Vec2<float>::worldToGrid(pos, ts);
	if (gridPos.x >= 0 && gridPos.y >= 0 && gridPos.x < map.getWidth() && gridPos.y < map.getHeight())
	{
		map.getTile(gridPos.y, gridPos.x).setType(TileType::BUILDABLE);
	}
}
void Game::handleTowerUpgrade()
{
	if (selectedTower == nullptr || !selectedTower->canUpgrade()) return;
	int cost = selectedTower->getUpgradeCost();
	if (money >= cost)
	{
		money -= cost;
		selectedTower->upgrade();
	}
}
bool Game::isFinished() const
{
	return waveManager.isFinished() && enemyManager.isEmpty();
}

