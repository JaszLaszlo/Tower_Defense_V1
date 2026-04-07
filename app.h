#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include "renderer.h"
#include "game.h"
#include "types.h"


class App {
    sf::RenderWindow window;
    Renderer renderer;
    Game* game;

    const float dt = 0.016667f;
    float accumulator;
    std::chrono::steady_clock::time_point lastTime;

    std::vector<TowerButton> sidebarButtons;
	TowerType selectedTowerType;
	void initSidebar();
    void handleClicks(float mx, float my);

public:
    App(std::istream& mapConfig, std::istream& waveconfig);
    ~App();

    void run();          
    void handleEvents();  
    void update(float dt); 
    void render(); 
};

#endif
