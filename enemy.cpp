#include<iostream>
#include "enemy.h"
#include "map.h"
#include "memtrace.h"
Enemy::Enemy(Vec2<float> p, float h, float mH, float sp, float si, const Map& map) : position(p), hp(h), maxHp(mH),
speed(sp), size(si), currentPathIndex(0)
{
	float maxMovementRange = static_cast<float>(map.getTileSize() - size);
	offset = (static_cast<float>(std::rand() % static_cast<int>(maxMovementRange))
		- maxMovementRange / 2.0f);
	handleOffsetAtSpawn(map);
}
Vec2<float> Enemy::calculateNormalizedDir(const Vec2<int>& from, const Vec2<int>& to) const {
	float dx = static_cast<float>(to.x - from.x);
	float dy = static_cast<float>(to.y - from.y);
	float len = std::sqrt(dx * dx + dy * dy);
	if (len <0.0001f) return { 0, 0 };
	return { dx / len, dy / len };
}
Vec2<float> Enemy::getPerpendicular(const Vec2<float>& dir) const {
	return { -dir.y, dir.x };
}
Vec2<float> Enemy::calculateCornerPoint(const Map& map, int pathIndex, float tileSize) const {
	Vec2<int> prev = map.getPathPoint(pathIndex);
	Vec2<int> curr = map.getPathPoint(pathIndex + 1);
	Vec2<int> next = map.getPathPoint(pathIndex + 2);
	Vec2<float> perp1 = getPerpendicular(calculateNormalizedDir(prev, curr));
	Vec2<float> perp2 = getPerpendicular(calculateNormalizedDir(curr, next));
	float cornerX = curr.x * tileSize + tileSize / 2.0f;
	float cornerY = curr.y * tileSize + tileSize / 2.0f;
	return {
		cornerX + perp1.x * offset + perp2.x * offset,
		cornerY + perp1.y * offset + perp2.y * offset
	};
}
Vec2<float> Enemy::calculateStraightTarget(const Map& map, int pathIndex, float tileSize) const {
	Vec2<int> current = map.getPathPoint(pathIndex);
	Vec2<int> next = map.getPathPoint(pathIndex + 1);
	Vec2<float> perp = getPerpendicular(calculateNormalizedDir(current, next));
	return {
		next.x * tileSize + tileSize / 2.0f + perp.x * offset,
		next.y * tileSize + tileSize / 2.0f + perp.y * offset
	};
}
void Enemy::handleOffsetAtSpawn(const Map& map)
{
	Vec2<float> direction = calculateNormalizedDir(map.getPathPoint(0), map.getPathPoint(1));
	Vec2<float> perpendicular = getPerpendicular(direction);
	position.x += perpendicular.x * offset;
	position.y += perpendicular.y * offset;
	
}
Vec2<float> Enemy::getOffsetTarget(const Map& map, int pathIndex) const
{
	float tileSize = static_cast<float>(map.getTileSize());
	if (pathIndex + 2 >= map.getPathSize())
		return calculateStraightTarget(map, pathIndex, tileSize);
	Vec2<int> current = map.getPathPoint(pathIndex);
	Vec2<int> next = map.getPathPoint(pathIndex + 1);
	Vec2<int> afterNext = map.getPathPoint(pathIndex + 2);
	bool dirChanges = (next.x - current.x) != (afterNext.x - next.x) ||
		(next.y - current.y) != (afterNext.y - next.y);
	if (dirChanges)
		return calculateCornerPoint(map, pathIndex, tileSize);
	return calculateStraightTarget(map, pathIndex, tileSize);
}
void Enemy::applyMovement(const Vec2<float>& target, float moveStep, float distance) {
	if (distance > moveStep) {
		position.x += ((target.x - position.x) / distance) * moveStep;
		position.y += ((target.y - position.y) / distance) * moveStep;
	}
	else {
		position = target;
		currentPathIndex++;
	}
}
void Enemy::Move(const Map& map, float dt)
{
	if (currentPathIndex >= map.getPathSize() - 1) return;
	Vec2<float> target = getOffsetTarget(map, currentPathIndex);
	float distance = std::hypot(target.x - position.x, target.y - position.y);
	applyMovement(target, speed * dt, distance);
}
bool Enemy::isAlive() const
{
	return hp > 0;
}
bool Enemy::hasReachedEnd(const Map& map) const {
	return currentPathIndex >= map.getPathSize() - 1;
}
Enemy::~Enemy() {}

EnemyManager::EnemyManager(int max) : Enemies(max) {}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	Enemies.Add(enemy);
}
void EnemyManager::Update(const Map& map,float dt)
{
	for (int i = 0; i < Enemies.size();i++)
	{
		if (Enemies[i] != nullptr)
		{
			Enemies[i]->Move(map, dt);
		}
	}
}

void NormalEnemy::draw(Graphics& g) const 
{
	g.drawNormalEnemy(position, size);
	g.drawEnemyHpbar(position, size, hp / maxHp);
}
void FastEnemy::draw(Graphics& g) const 
{
	g.drawFastEnemy(position, size);
	g.drawEnemyHpbar(position, size, hp / maxHp);
}
void TankEnemy::draw(Graphics& g) const 
{
	g.drawTankEnemy(position, size);
	g.drawEnemyHpbar(position, size, hp / maxHp);
}
void EnemyManager::Draw(Graphics& g) const
{
	for (int i = 0; i < Enemies.size(); i++)
	{
		if (Enemies[i] != nullptr)
		{
			Enemies[i]->draw(g);
		}
	}
}