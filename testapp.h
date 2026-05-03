#ifndef TESTAPP_H
#define TESTAPP_H

#include "IApp.h"
#include "level.h"
#include "graphics.h"
#include "types.h"

class NullGraphics : public Graphics {
    void drawTile(Vec2<float> pos, TileType t, float size) override {}
    void drawGrid(int width, int height, float tileSize) override {}
    void drawPathNumbers(const std::vector<Vec2<int>>& pathPoints, float tileSize) override {}
    void drawNormalEnemy(Vec2<float> pos, float size) override {}
    void drawFastEnemy(Vec2<float> pos, float size) override {}
    void drawTankEnemy(Vec2<float> pos, float size) override {}
    void drawNormalTower(Vec2<float> pos, float size) override {}
    void drawSniperTower(Vec2<float> pos, float size) override {}
    void drawFastTower(Vec2<float> pos, float size) override {}
    void drawTowerButton(const towerButton& button, bool isSelected, int currentMoney) override {}
    void drawTowerButtonBackground(const towerButton& button, bool isSelected) override {}
    void drawSidebarBackground() override {}
    void drawRangeCircle(Vec2<float> pos, float range) override {}
    void drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent) override {}
    void drawStatBarBackground() override {}
    void drawStatBar(int hp, int money, int currentwave, float seconds, bool isCounting) override {}
    void drawHp(int hp) override {}
    void drawMoney(int money) override {}
    void drawWaveCounter(int currentwave) override {}
    void drawCounter(float seconds) override {}
    void drawGameOver() override {}
    void drawYouWin() override {}
    void drawMapSaved() override {}
    void drawTowerStats(float d, float fr, float r, int l, int uCost) override {}
    void drawButton(const Button& button, bool isSelected=false) override {}
};
class TestApp : public IApp {
    LevelManager levelManager;
    NullGraphics graphics;
    gameState state;
public:
    TestApp() : state(gameState::MAINMENU) {}
    void changeState(gameState sType) override {
        state = sType;
    }
    LevelManager& getLevelManager() override {
        return levelManager;
    }
    Graphics& getGraphics() override {
        return graphics;
	}
    gameState getState() const {
        return state;
	}
};

#endif
