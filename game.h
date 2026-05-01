/**
 * @file Game.h
 * @brief A játék fő vezérlő osztálya.
 *
 * A Game osztály összefogja a teljes játékmenetet:
 * - pálya (Map)
 * - ellenségek (EnemyManager)
 * - tornyok (TowerManager)
 * - hullámok (WaveManager)
 *
 * Kezeli a játékállapotot, játékos erőforrásokat és a fő game loop logikát.
 */
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "map.h"
#include "enemy.h"
#include "vec2.h"
#include"tower.h"
#include "graphics.h"
#include "types.h"
#include "wave.h"
 /**
  * @class Game
  * @brief A játék teljes állapotát és logikáját kezelő osztály.
  *
  * Felelős:
  * - frissítés (update loop)
  * - kirajzolás (rendering)
  * - input események kezelése
  * - játékos erőforrások (HP, pénz)
  */
class Game
{
	Map map; //A játék pályája
	EnemyManager enemyManager; //Az ellenségek kezelője
	TowerManager towerManager; //A tornyok kezelője
	WaveManager waveManager; //A hullámok kezelője
	int playerHp; //A játékos életereje
	int money; //A játékos pénze
	bool running; //Jelzi, hogy a játék fut-e
	Tower* selectedTower; //Az aktuálisan kiválasztott torony (fejlesztéshez, eladáshoz)
	/**
	 * @brief Eltávolítja a már nem szükséges enemy-ket
	 * Pl. ha meghaltak vagy elérték a célpontot.
	 * @return void
	 */
	void cleanUpEnemies();
public:
	/**
	 * @brief Konstruktor
	 * Betölti a pályát és a wave adatokat streamből.
	 * @param mapIs Map input stream
	 * @param waveIs Wave input stream
	 */
	Game(std::istream& mapIs, std::istream& waveIs);
	/**
	 * @brief Játék logika frissítése
	 * Minden frame-ben meghívódik:
	 * - enemy update
	 * - tower update
	 * - wave update
	 * @param dt Delta time
	 */
	void update(float dt);
	/**
	 * @brief Játék kirajzolása
	 * Rendereli a teljes játékállapotot:
	 * map, enemy-k, tornyok
	 * @param g Grafikai objektum
	 */
	void draw(Graphics& g) const;
	/**
	 * @brief Torony építési kérés kezelése
	 * Ellenőrzi:
	 * - pénz elég-e
	 * - tile építhető-e
	 * @param mx Egér X pozíció
	 * @param my Egér Y pozíció
	 * @param type Torony típusa
	 */
	void handleTowerBuildRequest(float mx, float my, TowerType type);
	/**
	 * @brief Kijelölt torony fejlesztés
	 */
	void handleTowerUpgrade();
	/**
	 * @brief Következő hullám indítása
	 */
	void startNextWave() { waveManager.startNextWave(); }
	//@return Játékos HP-ja
	int getPlayerHp() const { return playerHp; }
	//@return Játékos pénze
	int getMoney() const { return money; }
	//@return jelzi, hogy a játék fut-e
	bool isRunning() const { return running; }
	//@return jelzi, hogy vége a játéknak
	bool isFinished() const;
	/**
	 * @brief WaveManager elérése
	 * @return Referencia a wave rendszerhez
	 */
	WaveManager& getWaveManager() { return waveManager; }
	/**
	 * @brief Torony keresése pozíció alapján
	 * @param mx X koordináta
	 * @param my Y koordináta
	 * @return A megtalált torony vagy nullptr
	 */
	Tower* getTowerAt(float mx, float my);
	/**
	 * @brief Torony eladása
	 * @param t Torony pointer
	 */
	void sellTower(Tower* t);
	/**
	 * @brief Kijelölt torony beállítása
	 */
	void setSelectedTower(Tower* t) { selectedTower = t; }
	// @param hp új HP
	void setHp(int hp) { playerHp = hp; }
	// @param m új pénz
	void setMoney(int m) { money = m; }
	// @return Kijelölt torony
	Tower* getSelectedTower() const { return selectedTower; }
};

#endif