#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include "vec2.h"
#include "types.h"

class Graphics
{
public:
	virtual ~Graphics() {}
	virtual void drawTile(Vec2<float> pos, TileType t, float size) = 0;
	virtual void drawNormalEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawFastEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawTankEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawNormalTower(Vec2<float> pos, float size) = 0;
	virtual void drawSniperTower(Vec2<float> pos, float size) = 0;
	virtual void drawFastTower(Vec2<float> pos, float size) = 0;
	virtual void drawTowerButton(const towerButton& button, bool isSelected) = 0;
	virtual void drawTowerButtonBackground(const towerButton& button, bool isSelected) = 0;
	virtual void drawSidebarBackground(float x, float width) = 0;
	virtual void drawRangeCircle(Vec2<float> pos, float range) = 0;
	virtual void drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent) = 0;
	virtual void drawStatBarBackground() = 0;
	virtual void drawStatBar(int hp, int money, int currentwave, float seconds, bool isCounting) = 0;
	virtual void drawHp(int hp) = 0;
	virtual void drawMoney(int money) = 0;
	virtual void drawWaveCounter(int currentwave) = 0;
	virtual void drawCounter(float seconds) = 0;
	virtual void drawGameOver() = 0;
	virtual void drawYouWin() = 0;
	virtual void drawTowerStats(float d, float fr, float r, int l, int uCost) = 0;
	virtual void drawButton(float x, float y, float w, float h, const std::string& text) = 0;
};

#endif
