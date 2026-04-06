#include "Renderer.h"
#include <iostream>



Renderer::Renderer(sf::RenderWindow& w): window(w)
{
	font.loadFromFile("Roboto-Regular.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
}
void Renderer::drawTile(Vec2<float> pos, TileType t, float size)
{
	sf::RectangleShape shape(sf::Vector2f(size, size));
	shape.setPosition(pos.x, pos.y);
	static const sf::Color colors[] =
	{
		sf::Color(100,100,100),
		sf::Color(34,139,34),
		sf::Color(50,50,50)
	};
	shape.setFillColor(colors[static_cast<int>(t)]);
	window.draw(shape);
}
void Renderer::drawNormalEnemy(Vec2<float> pos, float size)
{
	sf::CircleShape shape(size / 2);
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Green);
	window.draw(shape);
}
void Renderer::drawFastEnemy(Vec2<float> pos, float size)
{
	sf::CircleShape shape(size / 2);
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Yellow);
	window.draw(shape);
}
void Renderer::drawTankEnemy(Vec2<float> pos, float size)
{
	sf::RectangleShape shape(sf::Vector2f(size, size));
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Red);
	window.draw(shape);
}
void Renderer::drawNormalTower(Vec2<float> pos, float size)
{
	sf::RectangleShape shape(sf::Vector2f(size, size));
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Blue);
	window.draw(shape);
}
void Renderer::drawSniperTower(Vec2<float> pos, float size)
{
	sf::RectangleShape shape(sf::Vector2f(size, size));
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Magenta);
	window.draw(shape);
}
void Renderer::drawFastTower(Vec2<float> pos, float size)
{
	sf::RectangleShape shape(sf::Vector2f(size, size));
	shape.setOrigin(size / 2, size / 2);
	shape.setPosition(pos.x, pos.y);
	shape.setFillColor(sf::Color::Cyan);
	window.draw(shape);
}
void Renderer::drawTowerButtonBackground(const TowerButton& button, bool isSelected)
{
	sf::RectangleShape rect(sf::Vector2f(button.w, button.h));
	rect.setPosition(button.x, button.y);
	rect.setFillColor(isSelected ? sf::Color(100, 100, 100) : sf::Color(50, 50, 50));
	rect.setOutlineThickness(isSelected ? 3.0f : 1.0f);
	rect.setOutlineColor(isSelected ? sf::Color::Yellow : sf::Color::White);
	window.draw(rect);
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
	sf::RectangleShape sidebar(sf::Vector2f(width, window.getSize().y));
	sidebar.setPosition(x, 0);
	sidebar.setFillColor(sf::Color(40, 40, 40));
	window.draw(sidebar);
}
void Renderer::drawRangeCircle(Vec2<float> pos, float range)
{
	sf::CircleShape rangeCircle(range);
	rangeCircle.setOrigin(range, range);
	rangeCircle.setPosition(pos.x, pos.y);
	rangeCircle.setFillColor(sf::Color(255, 255, 255, 30));
	rangeCircle.setOutlineThickness(2.0f);
	rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 150));
	window.draw(rangeCircle);
}
void Renderer::drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent)
{
	const float barHeight = 10.0f;
	const float borderthickness = 2.0f;
	const float distanceAboveEnemy = size / 2.0f + barHeight + borderthickness;
	sf::Vector2f topLeft(pos.x - size / 2.0f, pos.y - distanceAboveEnemy);
	sf::RectangleShape frame(sf::Vector2f(size, barHeight));
	frame.setPosition(topLeft);
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::White);
	frame.setOutlineThickness(borderthickness);
	window.draw(frame);
	if (hpPercent > 0)
	{
		sf::RectangleShape content(sf::Vector2f(size * hpPercent, barHeight));
		content.setPosition(topLeft);
		content.setFillColor(sf::Color::Green);
		window.draw(content);
	}
}
void Renderer::drawStatBarBackground()
{
	sf::RectangleShape header(sf::Vector2f(window.getSize().x, 170.0f));
	header.setPosition(0, 1530);
	header.setFillColor(sf::Color(40, 40, 40));
	header.setOutlineColor(sf::Color(80, 80, 80));
	header.setOutlineThickness(2);
	window.draw(header);
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
	text.setString("HP: " + std::to_string(hp));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	text.setPosition(40, 1550);
	window.draw(text);
}
void Renderer::drawMoney(int money)
{
	text.setString("Money: " + std::to_string(money));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(600, 1550);
	window.draw(text);
}
void Renderer::drawWaveCounter(int currentwave)
{
	text.setString("Wave: " + std::to_string(currentwave));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setPosition(2000, 1550);
	window.draw(text);
}
void Renderer::drawCounter(float seconds)
{
	text.setString("NEXT WAVE: " + std::to_string((int)seconds) + "s");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(1250, 1550);
	window.draw(text);
}
void Renderer::drawGameOver()
{
	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(background);
	text.setString("GAME OVER");
	text.setCharacterSize(150);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	window.draw(text);
}
