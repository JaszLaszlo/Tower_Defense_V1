#include "level.h"
#include <iostream>
#include "memtrace.h"

void LevelManager::loadLevels(const std::string& configFile)
{
	std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "Hiba: Nem sikerult megnyitni a config fajlt: " << configFile << std::endl;
        return;
    }
	std::string name, map, wave;
	int hp, money;
    while (file >> name >> map >> wave >> hp >> money) {
        levels.Add(new LevelData(name, map, wave, hp, money));
    }
    file.close();
}
LevelData* LevelManager::getCurrentLevel() {
    if (levels.size() == 0) return nullptr; 
	return levels[currentLevelIndex];
}
bool LevelManager::selectLevel(int index)
{
    if (index >= 0 && index < levels.size()) {
        currentLevelIndex = index;
        return true;
    }
    return false;
}
std::string LevelManager::getlevelName(int index) const
{
    if (index >= 0 && index < levels.size()) {
        return levels[index]->levelName;
    }
    return "";
}