#pragma once
#include "map.h"
#include "MyArray.h"
#include "vec2.h"
#include "graphics.h"
#include "types.h"
#include <iostream> 


class Enemy
{
protected:
	Vec2<float> position;
	float offset;
	float hp, maxHp, speed, size;
	int currentPathIndex;
	Vec2<float> calculateNormalizedDir(const Vec2<int>& from, const Vec2<int>& to) const;
	Vec2<float> getPerpendicular(const Vec2<float>& dir) const;
	Vec2<float> calculateCornerPoint(const Map& map, int pathIndex, float tileSize) const;
	Vec2<float> calculateStraightTarget(const Map& map, int pathIndex, float tileSize) const;
	void applyMovement(const Vec2<float>& target, float moveStep, float distance);
	
public:
	Enemy(Vec2<float> p, float h, float mH, float sp, float si, const Map& map);
	virtual ~Enemy();
	Vec2<float> getPosition() const { return position; }
	float getSize() const { return size; }
	void handleOffsetAtSpawn(const Map& map);
	Vec2<float> getOffsetTarget(const Map& map, int pathIndex) const;
	void Move(const Map& map, float dt);
	bool hasReachedEnd(const Map& map) const;
	bool isAlive() const;
	void takeDamage(float amount) { hp -= amount; }
	virtual void draw(Graphics& g) const = 0;
	virtual Enemy* clone() const = 0;

};

class FastEnemy : public Enemy
{
public:
	FastEnemy(Vec2<float> p, const Map& map) : Enemy(p, 10.0, 10.0,85.0,55.0, map) {}
	void draw(Graphics& g) const;
	FastEnemy* clone() const override { return new FastEnemy(*this); }
};
class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Vec2<float> p, const Map& map) : Enemy(p, 20.0, 20.0, 55.0,30.0, map) {}
	void draw(Graphics& g) const;
	NormalEnemy* clone() const override { return new NormalEnemy(*this); }
};
class TankEnemy : public Enemy
{
public:
	TankEnemy(Vec2<float> p, const Map& map) : Enemy(p, 35.0, 35.0, 40.0,30.0, map) {}
	void draw(Graphics& g) const;
	TankEnemy* clone() const override { return new TankEnemy(*this); }
};

class EnemyManager
{
	MyArray<Enemy> Enemies;
public:
	EnemyManager(int max);
	void Update(const Map& map,float dt);
	void AddEnemy(Enemy* enemy);
	MyArray<Enemy>& getEnemies() { return Enemies; }
	void Draw(Graphics& g) const;
};