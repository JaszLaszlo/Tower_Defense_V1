#ifndef TYPES_H
#define TYPES_H
#include <string>

enum class TileType
{
	PATH,
	BUILDABLE,
	NOTBUILDABLE
};
enum class TowerType
{
	NORMAL,
	FAST,
	SNIPER,
	NONE
};
enum class EnemyType
{
	NORMAL,
	FAST,
	TANK
};
enum class gameState
{
	MAINMENU,
	LEVELSELECT,
	INGAME,
	MAPEDITOR,
	EXIT
};
struct Button {
	float x, y, w, h;
	std::string label;
	Button(float x, float y, float w, float h, const std::string& label) :
		x(x), y(y), w(w), h(h), label(label) {
	}
	bool isClicked(float mx, float my) const {
		return mx >= x && mx <= x + w && my >= y && my <= y + h;
	}
};
struct menuButton :public Button
{
	gameState targetState;
	menuButton(float x, float y, float w, float h, const std::string& label, gameState targetState) :
		Button(x, y, w, h, label), targetState(targetState) {}
};
struct levelButton : public Button
{
	int levelIndex;
	levelButton(float x, float y, float w, float h, const std::string& label, int levelIndex) :
		Button(x, y, w, h, label), levelIndex(levelIndex) {
	}
};
struct towerButton : public Button
{
	TowerType type;
	towerButton(float x, float y, float w, float h, const std::string& label, TowerType type) :
		Button(x, y, w, h, label), type(type) {
	}
};

#endif
