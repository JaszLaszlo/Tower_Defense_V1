#ifndef WAVE_H
#define WAVE_H
#include <string>
#include <sstream>
#include "types.h"
#include "MyArray.h"
#include "enemy.h"
#include "map.h"

class SpawnGroup
{
	int waveNumber;
	EnemyType enemyType;
	int count;
	float spawnInterval;
	float startDelay;
public:
	SpawnGroup(int wN, EnemyType eT, int c, float sI, float sD) : 
		waveNumber(wN), enemyType(eT), count(c), 
		spawnInterval(sI), startDelay(sD) {}
	SpawnGroup* clone() const {
		return new SpawnGroup(*this);
	}
	int getWaveNumber() const { return waveNumber; }
	EnemyType getEnemyType() const { return enemyType; }
	int getCount() const { return count; }
	float getInterval() const { return spawnInterval; }
	float getDelay() const { return startDelay; }
};
class WaveManager
{
	struct ActiveWaveStatus
	{
		int spawnedSoFar;
		float timer;
		bool finished;
		ActiveWaveStatus() : spawnedSoFar(0), timer(0.0f), finished(false) {}
		ActiveWaveStatus* clone() const { return new ActiveWaveStatus(*this); }
	};
	MyArray<SpawnGroup> spawnGroups;
	MyArray<ActiveWaveStatus> activeStatuses;
	int currentWave;
	float waveElapsedTime;
	bool isWaveRunning;
	float waveCountdown;
	bool isCountingDown;
	const float TIME_BETWEEN_WAVES = 15.0f;
	EnemyType convertStringToEnemyType(const std::string& str) const;
	void processLine(const std::string& line, int lineNum);
	void updateGroup(int idx, float dt, EnemyManager& em, const Map& map);
public:
	WaveManager() : 
		currentWave(0), waveElapsedTime(0.0f),
		isWaveRunning(false),isCountingDown(false),
		waveCountdown(0.0f) {}
	void load(std::istream& is);
	void update(float dt, EnemyManager& em, const  Map& map);
	int getCurrentWave() const { return currentWave; }
	bool isRunning() const { return isWaveRunning; }
	float getCountdown() const { return waveCountdown; }
	bool getIsCountingDown() const { return isCountingDown; }
	void startNextWave();
};



#endif

