/**
 * @file Graphics.h
 * @brief Absztrakt grafikai interfész.
 *
 * Ez az interfész elválasztja a játék logikát a konkrét rendereléstől.
 * A konkrét implementáció (pl. SFML Renderer) ezt valósítja meg.
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include <vector>
#include "vec2.h"
#include "types.h"

 /**
  * @class Graphics
  * @brief Absztrakt renderelési interfész.
  *
  * Minden kirajzolási művelet ezen keresztül történik.
  * A játék nem közvetlenül SFML-t használ
  */
class Graphics
{
public:
	/**
	 * @brief Virtuális destruktor
	 */
	virtual ~Graphics() {}
	/**
	 * @brief Tile kirajzolása
	 * @param pos Pozíció
	 * @param t Tile típusa
	 * @param size Méret
	 */
	virtual void drawTile(Vec2<float> pos, TileType t, float size) = 0;
	/**
	 * @brief Rács kirajzolása
	 * @param width Szélesség (tile-okban)
	 * @param height Magasság (tile-okban)
	 * @param tileSize Tile méret
	 */
	virtual void drawGrid(int width, int height, float tileSize) = 0;
	/**
	 * @brief Útvonal indexek kirajzolása
	 * @param pathPoints Útvonal pontok
	 * @param tileSize Tile méret
	 */
	virtual void drawPathNumbers(const std::vector<Vec2<int>>& pathPoints, float tileSize) = 0;
	/**
	 * @brief Normal enemy kirajzolása
	 */
	virtual void drawNormalEnemy(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Fast enemy kirajzolása
	 */
	virtual void drawFastEnemy(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Tank enemy kirajzolása
	 */
	virtual void drawTankEnemy(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Normal tower kirajzolása
	 */
	virtual void drawNormalTower(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Sniper tower kirajzolása
	 */
	virtual void drawSniperTower(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Fast tower kirajzolása
	 */
	virtual void drawFastTower(Vec2<float> pos, float size) = 0;
	/**
	 * @brief Tower gomb kirajzolása
	 *
	 * @param button Gomb
	 * @param isSelected Kijelölt-e
	 * @param currentMoney Játékos pénze
	 */
	virtual void drawTowerButton(const towerButton& button, bool isSelected, int currentMoney) = 0;
	/**
	 * @brief Tower gomb háttér
	 */
	virtual void drawTowerButtonBackground(const towerButton& button, bool isSelected) = 0;
	/**
	 * @brief Sidebar háttér
	 */
	virtual void drawSidebarBackground() = 0;
	/**
	 * @brief Tower range kör kirajzolása
	 * @param pos Pozíció
	 * @param range Hatótáv
	 */
	virtual void drawRangeCircle(Vec2<float> pos, float range) = 0;
	/**
	 * @brief Enemy HP bar
	 * @param pos Pozíció
	 * @param size Méret
	 * @param hpPercent HP százalék a maxhoz képest
	 */
	virtual void drawEnemyHpbar(Vec2<float> pos, float size, float hpPercent) = 0;
	/**
	 * @brief Stat bar háttér
	 */
	virtual void drawStatBarBackground() = 0;
	/**
	 * @brief Stat bar (HUD)
	 *
	 * @param hp HP
	 * @param money Pénz
	 * @param currentwave Aktuális wave
	 * @param seconds Countdown
	 * @param isCounting Timer aktív-e
	 */
	virtual void drawStatBar(int hp, int money, int currentwave, float seconds, bool isCounting) = 0;
	/**
	 * @brief HP UI
	 */
	virtual void drawHp(int hp) = 0;
	/**
	 * @brief Pénz UI
	 */
	virtual void drawMoney(int money) = 0;
	/**
	 * @brief Wave UI
	 */
	virtual void drawWaveCounter(int currentwave) = 0;
	/**
	 * @brief Visszaszámláló UI
	 */
	virtual void drawCounter(float seconds) = 0;
	/**
	 * @brief Game over képernyő
	 */
	virtual void drawGameOver() = 0;
	/**
	 * @brief You win képernyő
	 */
	virtual void drawYouWin() = 0;
	/**
	 * @brief Mentett pálya képernyő
	 */
	virtual void drawMapSaved() = 0;
	/**
	 * @brief Tower stat panel
	 *
	 * @param d damage
	 * @param fr fire rate
	 * @param r range
	 * @param l level
	 * @param uCost upgrade cost
	 */
	virtual void drawTowerStats(float d, float fr, float r, int l, int uCost) = 0;
	/**
	 * @brief Gomb kirajzolása, kijelölt állapotban
	 * @param button Gomb
	 * @param isSelected Kijelölt-e
	 */
	virtual void drawButton(const Button& button, bool isSelected=false) = 0;
};

#endif
