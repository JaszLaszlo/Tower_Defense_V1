/**
 * @file Types.h
 * @brief Alapvetõ enumok és UI elemek definíciói.
 *
 * Ez a fájl tartalmazza a játékban használt:
 * - tile típusokat
 * - tower típusokat
 * - enemy típusokat
 * - játékállapotokat
 * - UI gomb struktúrákat
 */
#ifndef TYPES_H
#define TYPES_H
#include <string>

 /**
  * @enum TileType
  * @brief A pálya mezõinek típusa.
  */
enum class TileType
{
	PATH,
	BUILDABLE,
	NOTBUILDABLE
};
/**
 * @enum TowerType
 * @brief Torony típusok.
 */
enum class TowerType
{
	NORMAL,
	FAST,
	SNIPER,
	NONE
};
/**
 * @enum EnemyType
 * @brief Ellenség típusok.
 */
enum class EnemyType
{
	NORMAL,
	FAST,
	TANK
};
/**
 * @enum gameState
 * @brief Játék fõ állapotai.
 */
enum class gameState
{
	MAINMENU,
	LEVELSELECT,
	INGAME,
	MAPEDITOR,
	EXIT
};
/**
 * @struct Button
 * @brief Egyszerû UI gomb alapstruktúra.
 * Minden UI gomb ebbõl öröklõdik.
 */
struct Button {
	float x, y, w, h; //Pozíció és méret
	std::string label; //megjelenített szöveg
	Button(float x, float y, float w, float h, const std::string& label) :
		x(x), y(y), w(w), h(h), label(label) {
	}
	/**
	 * @brief Egér kattintás ellenõrzése
	 * @param mx Egér X koordináta
	 * @param my Egér Y koordináta
	 * @return true ha a kattintás a gombon belül történt
	 */
	bool isClicked(float mx, float my) const {
		return mx >= x && mx <= x + w && my >= y && my <= y + h;
	}
};
/**
 * @struct menuButton
 * @brief Menü gomb, amely játékállapotot vált.
 */
struct menuButton :public Button
{
	gameState targetState;
	menuButton(float x, float y, float w, float h, const std::string& label, gameState targetState) :
		Button(x, y, w, h, label), targetState(targetState) {}
};
/**
 * @struct levelButton
 * @brief Pályaválasztó gomb.
 */
struct levelButton : public Button
{
	int levelIndex;
	levelButton(float x, float y, float w, float h, const std::string& label, int levelIndex) :
		Button(x, y, w, h, label), levelIndex(levelIndex) {
	}
};
/**
 * @struct towerButton
 * @brief Torony építõ gomb.
 */
struct towerButton : public Button
{
	TowerType type;
	int cost;
	towerButton(float x, float y, float w, float h, const std::string& label, TowerType type, int cost) :
		Button(x, y, w, h, label), type(type), cost(cost) {}
};
/**
 * @struct editorTileButton
 * @brief Pályaszerkesztõ tile választó gomb.
 */
struct editorTileButton : public Button
{
	TileType type;
public:
	editorTileButton(float x, float y, float w, float h, const std::string& label, TileType type) :
		Button(x, y, w, h, label), type(type) {}

};

#endif
