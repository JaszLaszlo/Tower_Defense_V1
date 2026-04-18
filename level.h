#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <iostream>
#include "MyArray.h"


struct LevelData
{
	std::string levelName;
	std::string mapFile;
	std::string waveFile;
	int startingHp;
	int startingMoney;
	LevelData(const std::string& name, const std::string& map, const std::string& wave, int hp, int money) :
		levelName(name), mapFile(map), waveFile(wave), startingHp(hp), startingMoney(money) {
	}
};
class LevelManager
{
	MyArray<LevelData> levels;
	int currentLevelIndex;
public:
	LevelManager(): currentLevelIndex(-1) {}
	void loadLevels(const std::string& configFile);
	LevelData* getCurrentLevel();
	int getLevelCount() const { return levels.size(); }
	bool selectLevel(int index);
	std::string getlevelName(int index) const;
};

#endif

