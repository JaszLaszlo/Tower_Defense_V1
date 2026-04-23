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

class State {
protected:
	IApp& app;
public:
	State(IApp& a) : app(a) {}
	virtual ~State() {}
	virtual void handleClick(float x, float y) = 0;
	virtual void handleKeyInput(int keyCode) = 0;
	virtual void update(float dt) = 0;
	virtual void draw() const = 0;
};
class MainMenuState : public State {
	std::vector<menuButton> buttons;
public:
	MainMenuState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keycode) override {}
	void update(float dt) override {}
	void draw() const override;
};
class LevelSelectState : public State {

	std::vector<levelButton> levelButtons;
	void calculateButtonPos(int index, float& x, float& y) const;
	void createButton(int index, const std::string& name);
public:
	LevelSelectState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override {}
	void update(float dt) override {}
	void draw() const override;
};
class InGameState : public State {
private:
	Game* game;
	TowerType selectedTowerType;
	std::vector<towerButton> sidebarButtons;
	void initSidebar();
public:
	InGameState(IApp& a, LevelData* data);
	~InGameState();
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override;
	void update(float dt) override;
	void draw() const override;
};
class MapEditorState : public State
{
	EditorMap eMap;
	TileType selectedType;
	std::vector<editorTileButton> buttons;
	void initButtons();
public:
	MapEditorState(IApp& a);
	void handleClick(float x, float y) override;
	void handleKeyInput(int keyCode) override;
	void update(float dt) override {}
	void draw() const override;
};
#endif
