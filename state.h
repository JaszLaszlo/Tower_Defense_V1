/**
 * @file State.h
 * @brief A játék state machine rendszerének definíciója.
 *
 * Ez a fájl tartalmazza a játék különböző állapotait:
 * - Main Menu
 * - Level Select
 * - InGame
 * - Map Editor
 *
 * Minden state felelős a saját input, update és render logikájáért.
 */
#ifndef STATE_H
#define STATE_H
#include "types.h"
#include "map.h"
#include <vector>
#include <string>


class IApp;
struct LevelData;
class Game;
class Map;

/**
 * @class State
 * @brief Absztrakt alap osztály minden játékállapothoz.
 *
 * A State minta alapján minden képernyő külön logikát kezel:
 * - input kezelés
 * - update
 * - render
 */
class State {
protected:
	IApp& app; //Referencia a fő alkalmazásra
public:
	/**
	* @brief Konstruktor
	* @param a App referencia
	*/
	State(IApp& a) : app(a) {}
	/**
	 * @brief Virtuális destruktor
	 */
	virtual ~State() {}
	/**
	 * @brief Egér kattintás kezelése
	 * @param x X koordináta
	 * @param y Y koordináta
	 */
	virtual void handleClick(float x, float y) = 0;
	/**
	 * @brief Billentyű input kezelése
	 * @param keyCode Billentyű kód
	 */
	virtual void handleKeyInput(int keyCode) = 0;
	/**
	 * @brief Állapot frissítése
	 * @param dt Delta time
	 */
	virtual void update(float dt) = 0;
	/**
	 * @brief Állapot kirajzolása
	 */
	virtual void draw() const = 0;
};
/**
 * @class MainMenuState
 * @brief Főmenü állapot.
 *
 * Kezeli:
 * - map editor és játék közötti választás
 */
class MainMenuState : public State {
	std::vector<menuButton> buttons;
public:
	MainMenuState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keycode) override {}
	void update(float dt) override {}
	void draw() const override;
};
/**
 * @class LevelSelectState
 * @brief Pályaválasztó képernyő.
 */
class LevelSelectState : public State {

	std::vector<levelButton> levelButtons;
	/**
	 * @brief Gomb pozíció számítása
	 * @param index Level index
	 * @param x X pozíció (out)
	 * @param y Y pozíció (out)
	 */
	void calculateButtonPos(int index, float& x, float& y) const;
	/**
	 * @brief Level gomb létrehozása
	 * @param index Level index
	 * @param name Megjelenített név
	 */
	void createButton(int index, const std::string& name);
public:
	LevelSelectState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override;
	void update(float dt) override {}
	void draw() const override;
};
/**
 * @class InGameState
 * @brief Aktív játékmenet állapot.
 * Itt fut a teljes tower defense játék logika.
 */
class InGameState : public State {
private:
	Game* game; //aktív játék
	TowerType selectedTowerType;
	std::vector<towerButton> sidebarButtons;
	bool valid = true; //Jelzi, hogy sikerült-e a játék inicializálása (fájlok betöltése)
	void initSidebar();
public:
	InGameState(IApp& a, LevelData* data);
	~InGameState();
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override;
	void update(float dt) override;
	void draw() const override;
};
/**
 * @class MapEditorState
 * @brief Pályaszerkesztő mód.
 * Lehetővé teszi:
 * - map szerkesztést, mentését
 */
class MapEditorState : public State
{
	EditorMap eMap;
	TileType selectedType;
	std::vector<editorTileButton> buttons;
	bool isSaved;
	void initButtons();
public:
	MapEditorState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override;
	void update(float dt) override {}
	void draw() const override;
};
#endif
