/**
 * @file Wave.h
 * @brief Hullámkezelő rendszer tower defense játékhoz.
 *
 * A WaveManager felelős az enemy hullámok betöltéséért,
 * időzítéséért és spawnolásáért.
 */
#ifndef WAVE_H
#define WAVE_H
#include <string>
#include <sstream>
#include "types.h"
#include "MyArray.h"
#include "enemy.h"
#include "map.h"

 /**
  * @class SpawnGroup
  * @brief Egy adott hullámon belüli enemy spawn csoport.
  *
  * Egy SpawnGroup meghatározza:
  * - melyik wave-ben jelenik meg
  * - milyen enemy típus
  * - hány darab
  * - milyen időközönként spawnol
  * - késleltetés a spawn előtt
  */
class SpawnGroup
{
	int waveNumber; //Melyik wave-ben jelenik meg
	EnemyType enemyType; //Milyen típusú enemy
	int count; //Hány darab enemy spawnol
	float spawnInterval; //Milyen időközönként spawnolnak (másodpercben)
	float startDelay; //Késleltetés a spawn előtt (másodpercben)
public:
	/**
	 * @brief Konstruktor
	 */
	SpawnGroup(int wN, EnemyType eT, int c, float sI, float sD) : 
		waveNumber(wN), enemyType(eT), count(c), 
		spawnInterval(sI), startDelay(sD) {}
	/**
	 * @brief Klónozás
	 * @return Új SpawnGroup példány
	 */
	SpawnGroup* clone() const {
		return new SpawnGroup(*this);
	}
	//@return hullám száma
	int getWaveNumber() const { return waveNumber; }
	//@return enemy típus
	EnemyType getEnemyType() const { return enemyType; }
	//@return spawnolni kívánt enemy-k száma
	int getCount() const { return count; }
	//@return spawnolási időköz
	float getInterval() const { return spawnInterval; }
	//@return kezdési késleltetés
	float getDelay() const { return startDelay; }
};
/**
 * @class WaveManager
 * @brief Hullámok kezelése és enemy spawn rendszer.
 *
 * Felelős:
 * - wave-ek betöltéséért fájlból
 * - spawn időzítésért
 * - aktív hullám állapot kezeléséért
 */
class WaveManager
{
	/**
	 * @struct ActiveWaveStatus
	 * @brief Egy aktív spawn csoport futási állapota.
	 */
	struct ActiveWaveStatus
	{
		int spawnedSoFar; //Eddig hány enemy spawnolt a csoportból
		float timer; //Időzítő a spawnoláshoz
		bool finished; //Jelzi, hogy a csoport spawnolása befejeződött-e
		//@brief Konstruktor
		ActiveWaveStatus() : spawnedSoFar(0), timer(0.0f), finished(false) {}
		// @return Klónozott állapot
		ActiveWaveStatus* clone() const { return new ActiveWaveStatus(*this); }
	};
	MyArray<SpawnGroup> spawnGroups; //Az összes spawn csoport
	MyArray<ActiveWaveStatus> activeStatuses; //Aktív állapotok
	int currentWave; //Aktuális wave száma
	int maxWave; //Maximális wave szám
	float waveElapsedTime; //Mennyi idő telt el az aktuális wave kezdete óta
	bool isWaveRunning; //Jelzi, hogy jelenleg fut-e egy wave
	float waveCountdown; //Visszaszámláló a következő wave kezdetéig
	bool isCountingDown; //Jelzi, hogy jelenleg visszaszámlálás van-e a következő wave-ig
	const float TIME_BETWEEN_WAVES = 15.0f; //Másodperc a wave-ek között
	/**
	 * @brief String  EnemyType konverzió
	 * @param str Bemeneti szöveg
	 * @return EnemyType érték
	 */
	EnemyType convertStringToEnemyType(const std::string& str) const;
	/**
	 * @brief Egy sor feldolgozása wave fájlból
	 * @param line Beolvasott sor
	 * @param lineNum Sor száma hibakereséshez
	 */
	void processLine(const std::string& line, int lineNum);
	/**
	 * @brief Egy spawn csoport frissítése
	 * Kezeli az időzítést és enemy spawnolást.
	 * @param idx Csoport index
	 * @param dt Delta time
	 * @param em EnemyManager
	 * @param map A pálya
	 */
	void updateGroup(int idx, float dt, EnemyManager& em, const Map& map);
public:
	/**
	 * @brief Konstruktor
	 */
	WaveManager() : 
		currentWave(0), waveElapsedTime(0.0f),
		isWaveRunning(false), isCountingDown(false),
		waveCountdown(0.0f), maxWave(0) {}
	/**
	 * @brief Hullámok betöltése streamből
	 * @param is Input stream (fájl)
	 */
	void load(std::istream& is);
	/**
	 * @brief Wave rendszer frissítése
	 * Kezeli:
	 * - spawnolást
	 * - cooldownokat
	 * 
	 * @param dt Delta time
	 * @param em EnemyManager
	 * @param map A pálya
	 */
	void update(float dt, EnemyManager& em, const  Map& map);
	// @return aktuális wave száma
	int getCurrentWave() const { return currentWave; }
	// @return jelzi, hogy jelenleg fut-e a wave
	bool isRunning() const { return isWaveRunning; }
	// @return visszaszámláló értéke a következő wave kezdetéig
	float getCountdown() const { return waveCountdown; }
	// @return jelzi, hogy visszaszámlálás van-e a következő wave-ig
	bool getIsCountingDown() const { return isCountingDown; }
	/**
	 * @brief Következő hullám indítása
	 */
	void startNextWave();
	/**
	 * @brief Ellenőrzi, hogy minden wave kész van-e
	 * @return true ha vége a játéknak
	 */
	bool isFinished() const;
};



#endif

