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