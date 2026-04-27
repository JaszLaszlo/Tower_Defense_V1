/**
 * @file IApp.h
 * @brief Az alkalmazás fõ interfésze.
 *
 * Az IApp egy absztrakt interfész, amelyet a fõ alkalmazás implementál.
 *
 * Célja:
 * - állapotváltás biztosítása (state machine kezelés)
 */
#ifndef IAPP_H
#define IAPP_H
#include "types.h"

class State;
class LevelManager;
class Graphics;

/**
 * @class IApp
 * @brief Alkalmazás interfész a játék state rendszere számára.
 *
 * Az IApp lehetõvé teszi, hogy a State osztályok:
 * - ne legyenek közvetlenül kötve az App implementációhoz
 * - csak absztrakt interfészen keresztül kommunikáljanak
 */
class IApp {
public:
	/**
	 * @brief Virtuális destruktor
	 */
	virtual ~IApp() {}
	/**
	 * @brief Játékállapot váltása
	 * Átvált a megadott game state-re 
	 * @param sType Új állapot típusa
	 */
	virtual void changeState(gameState sType) = 0;
	/**
	 * @brief LevelManager elérése
	 * A játék pályarendszerének kezelése.
	 * @return LevelManager referencia
	 */
	virtual LevelManager& getLevelManager() = 0;
	/**
	 * @brief Graphics rendszer elérése
	 * Rajzolási mûveletekhez szükséges grafikai objektum.
	 * @return Graphics referencia
	 */
	virtual Graphics& getGraphics() = 0;
};

#endif
