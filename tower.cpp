#include "tower.h"
#include <iostream>
#include "memtrace.h"


Tower::Tower(Vec2<float> p, float r, float d, float fr, float ft, float si) : position(p), range(r),
															 damage(d), fireRate(fr), fireTimer(ft), size(si) {}
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
void Tower::Update(float dt, MyArray<Enemy>& enemies)
{
	if (fireTimer > 0) fireTimer -= dt;
	if (fireTimer <= 0)
	{
		Enemy* target = findtarget(enemies);
		if (target != nullptr)
		{
			attack(target);
			fireTimer = fireRate;
		}
	}
}
void NormalTower::draw(Graphics& g) const
{
	g.drawNormalTower(position, size);
}
void FastTower::draw(Graphics& g) const
{
	g.drawFastTower(position, size);
}
void SniperTower::draw(Graphics& g) const
{
	g.drawSniperTower(position, size);
}


void TowerManager::AddTower(Tower* t)
{
	towers.Add(t);
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