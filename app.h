#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include "renderer.h"
#include "types.h"
#include "level.h"
#include "IApp.h"
#include "state.h"

class App : public IApp{
    sf::RenderWindow window;
    Renderer renderer;
	State* currentState;
    bool running;
    const float dt = 0.016667f;
    float accumulator;
    std::chrono::steady_clock::time_point lastTime;
    
	LevelManager levelManager;
public:
    App();
    ~App();
    void changeState(gameState type) override;
    LevelManager& getLevelManager() override {
        return levelManager;
    }
    Graphics& getGraphics() {
        return renderer; 
    }
    void run();          
    void handleEvents();  
    void update(float dt); 
    void render(); 
};

#endif
