/**
 * @file App.h
 * @brief A játék fõ alkalmazás osztálya.
 *
 * Az App felelõs:
 * - ablak kezelésért (SFML)
 * - game loop futtatásáért
 * - state managementért
 * - renderelés megvalósításáért
 */
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
 /**
  * @class App
  * @brief A játék fõ alkalmazás loop implementációja.
  *
  * Ez az osztály:
  * - inicializálja a rendszert
  * - kezeli a window-t (SFML)
  * - futtatja a game loopot
  * - kezeli az aktuális State-et
 
  */
class App : public IApp{
    sf::RenderWindow window; //SFML ablak
    Renderer renderer; //Grafikai réteg
	State* currentState; //Aktuális state
    bool running; //Játék fut-e
    const float dt = 0.016667f; //~60FPS
    float accumulator; //Idõ akkumulátor
    std::chrono::steady_clock::time_point lastTime; //Idõzítéshez
	LevelManager levelManager; //Pályák kezelése
public:
    /**
     * @brief Konstruktor
     * Inicializálja az ablakot, renderer-t és alap state-et.
     */
    App();
    /**
     * @brief Destruktor
     * Felszabadítja az aktív state-et
     */
    ~App();
    /**
    * @brief Játékállapot váltása
    * Lecseréli az aktuális State-et
    * @param type Új állapot típusa
    */
    void changeState(gameState type) override;
    LevelManager& getLevelManager() override {
        return levelManager;
    }
    /**
     * @brief Grafikai rendszer elérése
     * @return Renderer mint Graphics referencia
     */
    Graphics& getGraphics() {
        return renderer; 
    }
    /**
     * @brief Fõ game loop
     * Kezeli:
     * - event
     * - update 
     * - render
     */
    void run();   
    /**
     * @brief Input események kezelése
     * SFML event (billentyû, egér)
     */
    void handleEvents();  
    /**
     * @brief Játék logika frissítése
     * @param dt Delta time
     */
    void update(float dt); 
    /**
     * @brief Render 
     * Kirajzolja az aktuális state-et.
     */
    void render(); 
};

#endif
