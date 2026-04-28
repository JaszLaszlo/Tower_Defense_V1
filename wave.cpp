#include "wave.h"
#include "memtrace.h"

EnemyType WaveManager::convertStringToEnemyType(const std::string& str) const
{
	if(str == "NORMAL") return EnemyType::NORMAL;
	if (str == "FAST") return EnemyType::FAST;
	if (str == "TANK") return EnemyType::TANK;
	throw std::runtime_error("Tipushiba " + str);
}

void WaveManager::processLine(const std::string& line, int lineNum)
{
	if (line.empty()) return;
	std::stringstream ss(line);
	int wN;
	std::string eT;
	int c;
	float sI, sD;
	if (!(ss >> wN >> eT >> c >> sI >> sD)) {
		throw std::runtime_error("Formatumhiba " + std::to_string(lineNum));
	}
	EnemyType enemyType = convertStringToEnemyType(eT);
	spawnGroups.Add(new SpawnGroup(wN, enemyType, c, sI, sD));
	activeStatuses.Add(new ActiveWaveStatus());
}
void WaveManager::load(std::istream& is)
{
	std::string line;
	if (std::getline(is, line)) {
		 int totalWaves = std::stoi(line); 
		 maxWave = totalWaves;
	}
	int lineNum = 0; 
	while (std::getline(is, line)) {
		lineNum++; 
		try 
		{
			processLine(line, lineNum); 
		}
		catch (const std::exception& e) 
		{
			throw std::runtime_error("Hiba a(z) " + std::to_string(lineNum) + ". sorban: " + e.what());
		}
	}
	
}
void WaveManager::updateGroup(int idx, float dt, EnemyManager& em, const Map& map)
{
	ActiveWaveStatus* status = activeStatuses[idx];
	SpawnGroup* group = spawnGroups[idx];
	if (status->finished || waveElapsedTime<group->getDelay()) return;
	status->timer += dt;
	while (status->timer >= group->getInterval() && status->spawnedSoFar < group->getCount())
	{
		em.spawnEnemy(group->getEnemyType(), map, currentWave);
		status->spawnedSoFar++;
		status->timer -= group->getInterval();
	}
	if (status->spawnedSoFar >= group->getCount()) {
		status->finished = true;
	}
}
void WaveManager::update(float dt, EnemyManager& em, const  Map& map)
{
	if (isWaveRunning)
	{
		waveElapsedTime += dt;
		bool allFinished = true;
		for (int i = 0; i < spawnGroups.size(); i++)
		{
			if (spawnGroups[i]->getWaveNumber() == currentWave)
			{
				updateGroup(i, dt, em, map);
				if (!activeStatuses[i]->finished) allFinished = false;
			}
		}
		if (allFinished && em.getEnemies().size() == 0)
		{
			isWaveRunning = false;
			if (currentWave < maxWave) {
				isCountingDown = true;
				waveCountdown = TIME_BETWEEN_WAVES;
			}
		}
	}
	else if (isCountingDown)
	{
		waveCountdown -= dt;
		if (waveCountdown <= 0) {
			startNextWave(); 
		}
	}
}
void WaveManager::startNextWave()
{
	if (isWaveRunning) return; 
	isCountingDown = false;
	currentWave++;
	waveElapsedTime = 0.0f;
	isWaveRunning = true;
}
bool WaveManager::isFinished() const {
	return (currentWave >= maxWave && !isWaveRunning);
}