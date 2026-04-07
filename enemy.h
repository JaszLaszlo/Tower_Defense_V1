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
	Enemy(Vec2<float> p, float h, float sp, float si, const Map& map, float multiplier);
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
	virtual int getReward() const = 0;
	virtual Enemy* clone() const = 0;

};

class FastEnemy : public Enemy
{
public:
	FastEnemy(Vec2<float> p, const Map& map, float mult) 
		: Enemy(p, 15.0f,130.0f,55.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 6; }
	FastEnemy* clone() const override { return new FastEnemy(*this); }
};
class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Vec2<float> p, const Map& map, float mult) : 
		Enemy(p, 30.0f, 60.0f, 30.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 3; }
	NormalEnemy* clone() const override { return new NormalEnemy(*this); }
};
class TankEnemy : public Enemy
{
public:
	TankEnemy(Vec2<float> p, const Map& map, float mult)
		: Enemy(p, 120.0f, 35.0f, 30.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 9; }
	TankEnemy* clone() const override { return new TankEnemy(*this); }
};

class EnemyManager
{
	MyArray<Enemy> Enemies;
	Enemy* enemyFactory(EnemyType type, Vec2<float> pos, const Map& map, float mult) const;
public:
	EnemyManager() : Enemies() {}
	void Update(const Map& map,float dt);
	void spawnEnemy(EnemyType type, const Map& map, int wave);
	void AddEnemy(Enemy* enemy);
	MyArray<Enemy>& getEnemies() { return Enemies; }
	void Draw(Graphics& g) const;
};