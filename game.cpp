#include "map.h"
#include "enemy.h"
#include "game.h"
#include "graphics.h"
#include "memtrace.h"

Game::Game(int maxEnemies, std::istream& is) : map(Map()), enemyManager(maxEnemies), towerManager(100),
														   playerHp(100), running(true),
														   spawnIntervalSeconds(1.0f), spawnTimer(0.0f)
{
	map.load(is);
}
Vec2<float> Game::mapToWorld(Vec2<int> gridPos) const
{
	Vec2<float> pos;
	float tileSize = static_cast<float>(map.getTileSize());
	pos.x = gridPos.x * tileSize + tileSize / 2.0f;
	pos.y = gridPos.y * tileSize + tileSize / 2.0f;
	return pos;
}
void Game::handleSpawning(float dt)
{
	spawnTimer += dt;
	if (spawnTimer >= spawnIntervalSeconds)
	{
		Vec2<float> startPos = mapToWorld(map.getSpawnPoint());
		Enemy* newEnemy = new FastEnemy(startPos, map);
		enemyManager.AddEnemy(newEnemy);
		spawnTimer -= spawnIntervalSeconds;
	}
}
void Game::handleTowerBuildRequest(float mx, float my)
{
	int ts = map.getTileSize();
	int gridX = static_cast<int>(mx) / ts;
	int gridY = static_cast<int>(my) / ts;
	if (gridX >= 0 && gridY >= 0 && gridX < map.getWidth() && gridY < map.getHeight())
	{
		if (map.canBuild(gridY, gridX))
		{
			Vec2<float> towerPos(gridX * ts + ts / 2.0f, gridY * ts + ts / 2.0f);
			towerManager.AddTower(new NormalTower(towerPos));
			map.getTile(gridY, gridX).setType(TileType::NOTBUILDABLE);
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
	enemyManager.Update(map,dt);
	towerManager.Update(dt, enemyManager.getEnemies());
	handleSpawning(dt);
}

