#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "graphics.h"

class Renderer : public Graphics {
    sf::RenderWindow& window;
    sf::Font font;
    // Reusable text objects with fixed character sizes to avoid changing size each frame
    sf::Text textSmall;
    sf::Text textMedium;
    sf::Text textLarge;
    // Reusable shapes to avoid allocating shapes each frame
    sf::RectangleShape rectShape;
    sf::CircleShape circleShape;
    sf::CircleShape rangeCircle;
    sf::RectangleShape hpFrame;
    sf::RectangleShape hpContent;
public:
    Renderer(sf::RenderWindow& w);

    void drawTile(Vec2<float> pos, TileType t, float size) override;

    void drawNormalEnemy(Vec2<float> pos, float size) override;
    void drawFastEnemy(Vec2<float> pos, float size) override;
    void drawTankEnemy(Vec2<float> pos, float size) override;

    void drawNormalTower(Vec2<float> pos, float size) override;
    void drawSniperTower(Vec2<float> pos, float size) override;
    void drawFastTower(Vec2<float> pos, float size) override;

    void drawTowerButton(const TowerButton& button, bool isSelected) override;
    void drawTowerButtonBackground(const TowerButton& button, bool isSelected) override;
    void drawSidebarBackground(float x, float width) override;
    void drawRangeCircle(Vec2<float> pos, float range) override;
    void drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent) override;

    void drawStatBarBackground() override;
    void drawStatBar(int hp, int money, int currentwave, float seconds, bool isCounting) override;
    void drawHp(int hp) override;
    void drawMoney(int money) override;
    void drawWaveCounter(int currentwave) override;
    void drawCounter(float seconds) override;
    void drawGameOver() override;
	void drawTowerStats(float d, float fr, float r, int l, int uCost) override;

};

#endif

