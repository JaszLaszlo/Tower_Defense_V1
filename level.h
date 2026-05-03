/**
 * @file Level.h
 * @brief Játékszintek kezelése.
 *
 * A LevelManager felelős a pályák betöltéséért,
 * kiválasztásáért és az aktuális level adatok kezeléséért.
 */
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <iostream>
#include "MyArray.h"

 /**
  * @struct LevelData
  * @brief Egyetlen pálya (level) adatai.
  *
  * Tartalmazza a pályához tartozó:
  * - map fájl elérési útját
  * - wave fájl elérési útját
  * - kezdő életerőt
  * - kezdő pénzt
  */
struct LevelData
{
	std::string levelName; ///A pálya neve
	std::string mapFile; ///A pálya térképét leíró fájl elérési útja
	std::string waveFile; ///A pálya hullámjait leíró fájl elérési útja
	int startingHp; ///Kezdő életerő
	int startingMoney; ///Kezdő pénzösszeg
	/**
	 * @brief Konstruktor
	 */
	LevelData(const std::string& name, const std::string& map, const std::string& wave, int hp, int money) :
		levelName(name), mapFile(map), waveFile(wave), startingHp(hp), startingMoney(money) {
	}
};
/**
 * @class LevelManager
 * @brief Játék szintjeinek kezelése.
 *
 * Feladata:
 * - level lista betöltése konfigurációból
 * - aktuális level kiválasztása
 * - level adatok elérése gameplay-hez
 */
class LevelManager
{
	MyArray<LevelData> levels; ///A betöltött pályák listája
	int currentLevelIndex; ///Az aktuálisan kiválasztott pálya indexe a levels tömbben
public: 
	/**
	 * @brief Konstruktor
	 * Alapértelmezetten nincs kiválasztott level.
	 */
	LevelManager(): currentLevelIndex(-1) {}
	/**
	 * @brief Level lista betöltése konfigurációs fájlból
	 * A fájl tartalmazza a pályák adatait
	 * @param configFile Konfigurációs fájl neve
	 * @return void
	 */
	void loadLevels(const std::string& configFile);
	/**
	 * @brief Aktuális level lekérése
	 * @return Pointer az aktuális LevelData-ra, vagy nullptr ha nincs kiválasztva
	 */
	LevelData* getCurrentLevel();
	//@return A betöltött pályák száma
	int getLevelCount() const { return levels.size(); }
	/**
	 * @brief Level kiválasztása index alapján
	 * @param index Level index
	 * @return true ha sikerült kiválasztani
	 */
	bool selectLevel(int index);
	/**
	 * @brief Level nevének lekérése
	 * @param index Level index
	 * @return Level neve stringként
	 */
	std::string getlevelName(int index) const;

};

#endif

