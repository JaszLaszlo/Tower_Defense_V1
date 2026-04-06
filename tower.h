#ifndef TOWER_H
#define TOWER_H
#include "enemy.h"
#include "MyArray.h"
#include "vec2.h"
#include "graphics.h"

class Tower
{
protected:
	Vec2<float> position;
	float range;
	float damage;
	float fireRate;
	float fireTimer;
	float size;
	Enemy* currentTarget;
	float getDistance(const Vec2<float>& v1, const Vec2<float>& v2) const;
	Enemy* findtarget(MyArray<Enemy>& enemies) const;

public:
	Tower(Vec2<float> p, float r, float d, float fr, float ft, float si);
	virtual ~Tower() {};
	Enemy* getCurrentTarget() const { return currentTarget; }
	float getRange() const { return range; }
	float getSize() const { return size; }
	Vec2<float> getPosition() const { return position; }
	void resetTarget() { currentTarget = nullptr; }
	virtual void attack(Enemy* enemy) const { enemy->takeDamage(damage); }
	void Update(float dt, MyArray<Enemy>& enemies);
	virtual void draw(Graphics& g) const = 0;
	virtual int getCost() const = 0;
	virtual Tower* clone() const = 0;
	
};
class NormalTower : public Tower
{
public:
	NormalTower(Vec2<float> p): Tower(p, 400.0, 10.0, 1.0,0.0,150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 50; }
	NormalTower* clone() const override { return new NormalTower(*this); }
};
class FastTower : public Tower
{
public:
	FastTower(Vec2<float> p): Tower(p, 300.0, 5.0, 0.5, 0.0, 150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 70; }
	FastTower* clone() const override { return new FastTower(*this); }
};
class SniperTower : public Tower
{
public:
	SniperTower(Vec2<float> p): Tower(p, 900.0, 20.0, 3.0, 0.0, 150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 90; }
	SniperTower* clone() const override { return new SniperTower(*this); }
};
class TowerManager
{
	MyArray<Tower> towers;
	Tower* towerFactory(TowerType type, Vec2<float> pos) const;
public:
	TowerManager(int max): towers(max) {}
	void notifyEnemyRemoved(Enemy* enemy);
	void AddTower(TowerType type, Vec2<float> pos);
	void Update(float dt, MyArray<Enemy>& enemies);
	void Draw(Graphics& g) const;
	int GetCostForType(TowerType type) const;
};

#endif