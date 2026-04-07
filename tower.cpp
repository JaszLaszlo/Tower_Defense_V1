#include "tower.h"
#include <iostream>
#include "memtrace.h"


Tower::Tower(Vec2<float> p, float r, float d, float fr, float ft, float si) : 
	position(p), range(r),
	damage(d), fireRate(fr), fireTimer(ft),
	size(si), currentTarget(nullptr),
	level(1), maxLevel(4){}

float Tower::getDistance(const Vec2<float>& v1, const Vec2<float>& v2) const
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
}
void FastTower::draw(Graphics& g) const
{
	g.drawFastTower(position, size);
}
void SniperTower::draw(Graphics& g) const
{
	g.drawSniperTower(position, size);
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
int TowerManager::GetCostForType(TowerType type) const
{
	Tower* t = towerFactory(type, Vec2<float>(0.0f, 0.0f));
	if (!t) return 0;
	int cost = t->getCost();
	delete t;
	return cost;
}
int Tower::getUpgradeCost() const {
	return static_cast<int>(getCost() + (0.5f * level * getCost()));
}
Tower* TowerManager::GetTowerAt(const Vec2<float>& pos, int ts)
{
	Vec2<int> clickGrid = Vec2<float>::worldToGrid(pos, ts);
	for (int i = 0; i < towers.size(); i++)
	{
		if (towers[i] != nullptr)
		{
			Vec2<int> towerGrid = Vec2<float>::worldToGrid(towers[i]->getPosition(), ts);
			if (clickGrid==towerGrid)
				return towers[i];
		}
	}
	return nullptr;
}
int TowerManager::sellTower(Tower* t, Vec2<float>& pos)
{
	for (int i = 0; i < towers.size(); i++)
	{
		if (towers[i] == t)
		{
			pos = t->getPosition();
			int sell = t->getSellValue();
			towers.Remove(i);
			return sell;
		}
	}
	return 0;
}
int Tower::getSellValue() const {
	int totalInvested = getCost(); 
	
	for (int i = 1; i < level; i++) {
		totalInvested += static_cast<int>(getCost() + (0.5f * i * getCost()));
	}
	return totalInvested / 2; 
}
void NormalTower::upgrade() {
	if (!canUpgrade()) return;

	switch (level) {
	case 1: 
		damage += 5.0f;     // 10 -> 15
		range += 50.0f;     // 400 -> 450
		break;
	case 2: 
		damage += 10.0f;    // 15 -> 25
		range += 50.0f;     // 450 -> 500
		fireRate *= 0.8f;   // 1.0 -> 0.8s
		break;
	case 3: 
		damage += 15.0f;    // 25 -> 40
		range += 100.0f;    // 500 -> 600
		fireRate *= 0.75f;  // 0.8 -> 0.6s
		break;
	}
	level++;
}
void FastTower::upgrade() {
	if (!canUpgrade()) return;

	switch (level) {
	case 1: 
		fireRate *= 0.7f;   // 0.5 -> 0.35s
		range += 20.0f;     // 300 -> 320
		break;
	case 2: 
		fireRate *= 0.6f;   // 0.35 -> 0.21s
		damage += 2.0f;     // 5 -> 7
		break;
	case 3: 
		fireRate = 0.15f;   
		damage += 5.0f;     // 7 -> 12
		range += 30.0f;     // 320 -> 350
		break;
	}
	level++;
}
void SniperTower::upgrade() {
	if (!canUpgrade()) return;

	switch (level) {
	case 1: 
		damage += 30.0f;    // 20 -> 50
		range += 100.0f;    // 900 -> 1000
		break;
	case 2: 
		damage *= 2.5f;     // 50 -> 125
		range += 200.0f;    // 1000 -> 1200
		fireRate *= 1.1f;   // Lassul a töltés: ~3.3s
		break;
	case 3:
		damage *= 2.0f;     // 125 -> 250 
		break;
	}
	level++;
}