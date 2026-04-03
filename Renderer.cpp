#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& w): window(w)
{
	//font.loadFromFile("arial.ttf");
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
void Renderer::drawTowerButton(const TowerButton& button, bool isSelected)
{
	sf::RectangleShape rect(sf::Vector2f(button.w, button.h));
	rect.setPosition(button.x, button.y);
	rect.setFillColor(isSelected ? sf::Color(100, 100, 100) : sf::Color(50, 50, 50));
	rect.setOutlineThickness(isSelected ? 3.0f : 1.0f);
	rect.setOutlineColor(isSelected ? sf::Color::Yellow : sf::Color::White);
	window.draw(rect);

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
/*void Renderer::drawText(Vec2<float> pos, const std::string& text, int fontSize)
{
	sf::Text sfText;
	sfText.setFont(font);
	sfText.setString(text);
	sfText.setCharacterSize(fontSize);
	sfText.setFillColor(sf::Color::White);
	sfText.setPosition(pos.x, pos.y);
	window.draw(sfText);
}*/
