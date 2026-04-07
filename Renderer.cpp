#include "Renderer.h"
#include <iostream>
#include <iomanip>  
#include <sstream>


Renderer::Renderer(sf::RenderWindow& w): window(w)
{
    if (!font.loadFromFile("Consola.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    textSmall.setFont(font);
    textSmall.setCharacterSize(20);
    textSmall.setFillColor(sf::Color::White);

    textMedium.setFont(font);
    textMedium.setCharacterSize(50);
    textMedium.setFillColor(sf::Color::White);

    textLarge.setFont(font);
    textLarge.setCharacterSize(150);
    textLarge.setFillColor(sf::Color::White);

    rectShape.setSize(sf::Vector2f(0.0f, 0.0f));
    rectShape.setFillColor(sf::Color::White);
    rectShape.setOutlineThickness(0.0f);

    circleShape.setRadius(0.0f);
    circleShape.setFillColor(sf::Color::White);

    rangeCircle.setRadius(0.0f);
    rangeCircle.setFillColor(sf::Color(255, 255, 255, 30));
    rangeCircle.setOutlineThickness(2.0f);
    rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 150));

    hpFrame.setSize(sf::Vector2f(0.0f, 0.0f));
    hpFrame.setFillColor(sf::Color::Transparent);
    hpFrame.setOutlineColor(sf::Color::White);
    hpFrame.setOutlineThickness(2.0f);

    hpContent.setSize(sf::Vector2f(0.0f, 0.0f));
    hpContent.setFillColor(sf::Color::Green);
}
void Renderer::drawTile(Vec2<float> pos, TileType t, float size)
{
    rectShape.setSize(sf::Vector2f(size, size));
    rectShape.setPosition(pos.x, pos.y);
    rectShape.setOrigin(0.0f, 0.0f);
    static const sf::Color colors[] =
    {
        sf::Color(100,100,100),
        sf::Color(34,139,34),
        sf::Color(50,50,50)
    };
    rectShape.setFillColor(colors[static_cast<int>(t)]);
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawNormalEnemy(Vec2<float> pos, float size)
{
    circleShape.setRadius(size / 2.0f);
    circleShape.setOrigin(size / 2.0f, size / 2.0f);
    circleShape.setPosition(pos.x, pos.y);
    circleShape.setFillColor(sf::Color::Green);
    window.draw(circleShape);
}
void Renderer::drawFastEnemy(Vec2<float> pos, float size)
{
    circleShape.setRadius(size / 2.0f);
    circleShape.setOrigin(size / 2.0f, size / 2.0f);
    circleShape.setPosition(pos.x, pos.y);
    circleShape.setFillColor(sf::Color::Yellow);
    window.draw(circleShape);
}
void Renderer::drawTankEnemy(Vec2<float> pos, float size)
{
    rectShape.setSize(sf::Vector2f(size, size));
    rectShape.setOrigin(size / 2.0f, size / 2.0f);
    rectShape.setPosition(pos.x, pos.y);
    rectShape.setFillColor(sf::Color::Red);
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawNormalTower(Vec2<float> pos, float size)
{
    rectShape.setSize(sf::Vector2f(size, size));
    rectShape.setOrigin(size / 2.0f, size / 2.0f);
    rectShape.setPosition(pos.x, pos.y);
    rectShape.setFillColor(sf::Color::Blue);
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawSniperTower(Vec2<float> pos, float size)
{
    rectShape.setSize(sf::Vector2f(size, size));
    rectShape.setOrigin(size / 2.0f, size / 2.0f);
    rectShape.setPosition(pos.x, pos.y);
    rectShape.setFillColor(sf::Color::Magenta);
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawFastTower(Vec2<float> pos, float size)
{
    rectShape.setSize(sf::Vector2f(size, size));
    rectShape.setOrigin(size / 2.0f, size / 2.0f);
    rectShape.setPosition(pos.x, pos.y);
    rectShape.setFillColor(sf::Color::Cyan);
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawTowerButtonBackground(const TowerButton& button, bool isSelected)
{
    rectShape.setSize(sf::Vector2f(button.w, button.h));
    rectShape.setPosition(button.x, button.y);
    rectShape.setOrigin(0.0f, 0.0f);
    rectShape.setFillColor(isSelected ? sf::Color(100, 100, 100) : sf::Color(50, 50, 50));
    rectShape.setOutlineThickness(isSelected ? 3.0f : 1.0f);
    rectShape.setOutlineColor(isSelected ? sf::Color::Yellow : sf::Color::White);
    window.draw(rectShape);
}
void Renderer::drawTowerButton(const TowerButton& button, bool isSelected)
{
    drawTowerButtonBackground(button, isSelected);
    Vec2<float> center(button.x + button.w / 2.0f, button.y + button.h / 2.0f);
    float iconSize = button.h * 0.6f;

    switch (button.type) {
    case TowerType::NORMAL: drawNormalTower(center, iconSize); break;
    case TowerType::FAST:   drawFastTower(center, iconSize);   break;
    case TowerType::SNIPER: drawSniperTower(center, iconSize); break;
    }
}

void Renderer::drawSidebarBackground(float x, float width)
{
    rectShape.setSize(sf::Vector2f(width, window.getSize().y));
    rectShape.setPosition(x, 0);
    rectShape.setOrigin(0.0f, 0.0f);
    rectShape.setFillColor(sf::Color(40, 40, 40));
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);
}
void Renderer::drawRangeCircle(Vec2<float> pos, float range)
{
    rangeCircle.setRadius(range);
    rangeCircle.setOrigin(range, range);
    rangeCircle.setPosition(pos.x, pos.y);
    window.draw(rangeCircle);
}
void Renderer::drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent)
{
    const float barHeight = 10.0f;
    const float borderthickness = 2.0f;
    const float distanceAboveEnemy = size / 2.0f + barHeight + borderthickness;
    sf::Vector2f topLeft(pos.x - size / 2.0f, pos.y - distanceAboveEnemy);

    hpFrame.setSize(sf::Vector2f(size, barHeight));
    hpFrame.setPosition(topLeft);
    hpFrame.setOrigin(0.0f, 0.0f);
    hpFrame.setFillColor(sf::Color::Transparent);
    hpFrame.setOutlineColor(sf::Color::White);
    hpFrame.setOutlineThickness(borderthickness);
    window.draw(hpFrame);

    if (hpPercent > 0.0f)
    {
        hpContent.setSize(sf::Vector2f(size * hpPercent, barHeight));
        hpContent.setPosition(topLeft);
        hpContent.setOrigin(0.0f, 0.0f);
        hpContent.setFillColor(sf::Color::Green);
        window.draw(hpContent);
    }
}
void Renderer::drawStatBarBackground()
{
    rectShape.setSize(sf::Vector2f(window.getSize().x, 170.0f));
    rectShape.setPosition(0, 1530);
    rectShape.setOrigin(0.0f, 0.0f);
    rectShape.setFillColor(sf::Color(40, 40, 40));
    rectShape.setOutlineColor(sf::Color(80, 80, 80));
    rectShape.setOutlineThickness(2);
    window.draw(rectShape);
}
void Renderer::drawStatBar(int hp, int money, int currentwave, float seconds, bool isCounting)
{
    drawStatBarBackground();
    drawHp(hp);
    drawMoney(money);
    drawWaveCounter(currentwave);
    if(isCounting)
        drawCounter(seconds);
}

void Renderer::drawHp(int hp)
{
    textMedium.setString("HP: " + std::to_string(hp));
    textMedium.setFillColor(sf::Color::Red);
    textMedium.setPosition(40, 1550);
    window.draw(textMedium);
}
void Renderer::drawMoney(int money)
{
    textMedium.setString("Money: " + std::to_string(money));
    textMedium.setFillColor(sf::Color::Yellow);
    textMedium.setPosition(600, 1550);
    window.draw(textMedium);
}
void Renderer::drawWaveCounter(int currentwave)
{
    textMedium.setString("Wave: " + std::to_string(currentwave));
    textMedium.setFillColor(sf::Color::White);
    textMedium.setPosition(2000, 1550);
    window.draw(textMedium);
}
void Renderer::drawCounter(float seconds)
{
    textMedium.setString("NEXT WAVE: " + std::to_string((int)seconds) + "s");
    textMedium.setFillColor(sf::Color::Cyan);
    textMedium.setPosition(1250, 1550);
    window.draw(textMedium);
}
void Renderer::drawGameOver()
{
    rectShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    rectShape.setPosition(0, 0);
    rectShape.setOrigin(0.0f, 0.0f);
    rectShape.setFillColor(sf::Color(0, 0, 0, 150));
    rectShape.setOutlineThickness(0.0f);
    window.draw(rectShape);

    textLarge.setString("GAME OVER");
    textLarge.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = textLarge.getLocalBounds();
    textLarge.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    textLarge.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    window.draw(textLarge);
}
void Renderer::drawTowerStats(float d, float fr, float r, int l, int uCost)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << std::left;
    ss <<"--- TOWER INFO ---\n\n";
    ss << std::setw(15) <<"Damage:"<<d<<"\n";
    ss << std::setw(15) <<"Range:"<<r<<"\n";
    ss << std::setw(15) <<"Fire Rate:"<<fr<<"s\n";
	ss << std::setw(15) << "Level:" << l << "\n";
	ss << std::setw(15) << "Upgrade Cost:" << uCost << "\n";
    ss << "------------------\n";
    ss << "Right Click to Sell\n";
	ss << "Press U to Upgrade";
    textMedium.setString(ss.str());
    textMedium.setCharacterSize(35); 
    textMedium.setFillColor(sf::Color::Yellow);
    textMedium.setPosition(2250.0f, 500.0f);
    window.draw(textMedium);
	textMedium.setCharacterSize(50);
}
