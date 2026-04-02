#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "graphics.h"

class Renderer : public Graphics {
    sf::RenderWindow& window;
    //sf::Font font;          
public:
    Renderer(sf::RenderWindow& w);

    void drawTile(Vec2<float> pos, TileType t, float size) override;

    void drawNormalEnemy(Vec2<float> pos, float size) override;
    void drawFastEnemy(Vec2<float> pos, float size) override;
    void drawTankEnemy(Vec2<float> pos, float size) override;

    void drawNormalTower(Vec2<float> pos, float size) override;
    void drawSniperTower(Vec2<float> pos, float size) override;
    void drawFastTower(Vec2<float> pos, float size) override;

    //void drawText(Vec2<float> pos, const std::string& text, int fontSize) override;
};

#endif

