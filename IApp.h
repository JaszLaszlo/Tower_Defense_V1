#ifndef IAPP_H
#define IAPP_H
#include "types.h"

class State;
class LevelManager;
class Graphics;

class IApp {
public:
	virtual ~IApp() {}
	virtual void changeState(gameState sType) = 0;
	virtual LevelManager& getLevelManager() = 0;
	virtual Graphics& getGraphics() = 0;
};

#endif
