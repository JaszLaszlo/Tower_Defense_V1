#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include "vec2.h"

enum class TileType
{
	PATH,
	BUILDABLE,
	NOTBUILDABLE
};
class Graphics
{
public:
	virtual ~Graphics() {}
	virtual void drawTile(Vec2<float> pos, TileType t, float size) = 0;
	virtual void drawNormalEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawFastEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawTankEnemy(Vec2<float> pos, float size) = 0;
	virtual void drawNormalTower(Vec2<float> pos, float size) = 0;
	virtual void drawSniperTower(Vec2<float> pos, float size) = 0;
	virtual void drawFastTower(Vec2<float> pos, float size) = 0;
	//virtual void drawText(Vec2<float> pos, const std::string& text, int fontSize) = 0;
};

#endif
