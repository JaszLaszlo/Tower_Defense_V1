#include "tower.h"
#include <iostream>
#include "memtrace.h"


Tower::Tower(Vec2<float> p, float r, float d, float fr, float ft, float si) : 
	position(p), range(r),
	damage(d), fireRate(fr), fireTimer(ft),
	size(si), currentTarget(nullptr) {}

float Tower::getDistance(Vec2<float> v1, Vec2<float> v2) const
{
	return std::hypot(v1.x - v2.x, v1.y - v2.y);
}
Enemy* Tower::findtarget(MyArray<Enemy>& enemies) const
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] != nullptr && enemies[i]->isAlive())
		{
			float dist = getDistance(position, enemies[i]->getPosition());
			if (dist - enemies[i]->getSize() / 2.0f <= range)
				return enemies[i];
		}
	}
	return nullptr;
}
	
Tower* TowerManager::towerFactory(TowerType type, Vec2<float> pos) const
{
	switch (type)
	{
	case TowerType::NORMAL:
		return new NormalTower(pos);
	case TowerType::FAST:
		return new FastTower(pos);
	case TowerType::SNIPER:
		return new SniperTower(pos);
	default:
		return nullptr;
	}
}
void TowerManager::notifyEnemyRemoved(Enemy* enemy)
{
	for(int i = 0; i < towers.size(); i++)
	{
		if (towers[i]->getCurrentTarget() == enemy)
		{
			towers[i]->resetTarget();
		}
	}
}
void Tower::Update(float dt, MyArray<Enemy>& enemies)
{
	if (fireTimer > 0) fireTimer -= dt;
	if (currentTarget != nullptr)
	{
		float dist = getDistance(position, currentTarget->getPosition());
		if (!currentTarget->isAlive() || (dist - currentTarget->getSize() / 2.0f) > range)
			currentTarget = nullptr;
	}
	if(currentTarget == nullptr)
		currentTarget = findtarget(enemies);
	if (fireTimer <= 0 && currentTarget!=nullptr)
	{
			attack(currentTarget);
			fireTimer = fireRate;
	}
}
void NormalTower::draw(Graphics& g) const
{
	g.drawNormalTower(position, size);
	g.drawRangeCircle(position, range);
}
void FastTower::draw(Graphics& g) const
{
	g.drawFastTower(position, size);
	g.drawRangeCircle(position, range);
}
void SniperTower::draw(Graphics& g) const
{
	g.drawSniperTower(position, size);
	g.drawRangeCircle(position, range);
}


void TowerManager::AddTower(TowerType type, Vec2<float> pos)
{
	Tower* newTower = towerFactory(type, pos);
	towers.Add(newTower);
}
void TowerManager::Update(float dt, MyArray<Enemy>& enemies)
{
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->Update(dt, enemies);
	}
}
void TowerManager::Draw(Graphics& g) const
{
	for (int i = 0; i < towers.size(); i++)
	{
		if (towers[i] != nullptr)
			towers[i]->draw(g);
	}
}