#include "state.h"
#include "memtrace.h"
#include "IApp.h"
#include "level.h"
#include "game.h"  


MainMenuState::MainMenuState(IApp& a) : State(a) 
{

    buttons.push_back({ menuButton(1000, 400, 600, 300, "Start", gameState::LEVELSELECT) });

    buttons.push_back({ menuButton(1000, 1100, 600, 300, "Map Editor", gameState::MAPEDITOR) });
}
void MainMenuState::handleClick(float x, float y) 
{
    for (const auto& btn : buttons) {
        if (btn.isClicked(x, y)) {
            app.changeState(btn.targetState);
            return; 
        }
    }
}
void MainMenuState::draw() const {
    Graphics& g = app.getGraphics();

    for (const auto& btn : buttons) {
        g.drawButton(btn);
    }
}
void LevelSelectState::calculateButtonPos(int index, float& x, float& y) const 
{
    const int maxCols = 8;
    const float bW = 300.0f;
    const float bH = 100.0f;
    const float gap = 15.0f;
    const float startX = 100.0f;
    const float startY = 150.0f;

    int col = index % maxCols;
    int row = index / maxCols;

    x = startX + col * (bW + gap);
    y = startY + row * (bH + gap);
}
void LevelSelectState::createButton(int index, const std::string& name) 
{
    float x, y;
    calculateButtonPos(index, x, y);

    levelButton btn(x, y, 300.0f, 100.0f, name, index);
    levelButtons.push_back(btn);
}
LevelSelectState::LevelSelectState(IApp& a) : State(a) {
    LevelManager& lm = app.getLevelManager();
    int totalLevels = lm.getLevelCount();

    for (int i = 0; i < totalLevels; ++i) {
        createButton(i, lm.getlevelName(i));
    }
}
void LevelSelectState::handleClick(float mx, float my) {
    for (const auto& btn : levelButtons) {
        if (btn.isClicked(mx, my)) {
            app.getLevelManager().selectLevel(btn.levelIndex);
            app.changeState(gameState::INGAME);
            return; 
        }
    }
}
void LevelSelectState::handleKeyInput(int keyCode) {
    if (keyCode == 58) { // Enter
        app.changeState(gameState::MAINMENU);
    }
}
void LevelSelectState::draw() const {
    Graphics& g = app.getGraphics();

    for (const auto& btn : levelButtons) {
        g.drawButton(btn);
    }
}
InGameState::InGameState(IApp& a, LevelData* data) :
    State(a), game(nullptr), selectedTowerType(TowerType::NONE)
{
    if (data == nullptr) {
        valid = false;
        return;
    }
    std::ifstream mapFile(data->mapFile);
    std::ifstream waveFile(data->waveFile);

    if (!mapFile.is_open() || !waveFile.is_open()) {
        std::cerr << "Hiba: Nem sikerult megnyitni a fajlokat!" << std::endl;
        valid = false;
        return;
    }
    game = new Game(mapFile, waveFile);
    game->setHp(data->startingHp);
    game->setMoney(data->startingMoney);
    initSidebar();
    valid = true;
}
void InGameState::initSidebar()
{
    float buttonWidth = 200.0f;
    float buttonHeight = 160.0f;
    float startX = 2400.0f;
    float startY = 100.0f;
    float gap = 40.0f;
    sidebarButtons.push_back({ towerButton(startX, startY, buttonWidth, buttonHeight, "Normal", TowerType::NORMAL,50) });
    sidebarButtons.push_back({ towerButton(startX, startY + (buttonHeight + gap), buttonWidth, buttonHeight, "Fast", TowerType::FAST,70) });
    sidebarButtons.push_back({ towerButton(startX, startY + 2 * (buttonHeight + gap), buttonWidth, buttonHeight, "Sniper", TowerType::SNIPER,90) });
}
void InGameState::handleClick(float mx, float my)
{
    if (game == nullptr || game->isFinished() || !game->isRunning()) {
        return;
    }
    float sidebarX = 2220.0f;
    if (mx > sidebarX)
    {
        for (const towerButton& button : sidebarButtons)
        {
            if (button.isClicked(mx, my)) {
                selectedTowerType = button.type;
                break;
            }
        }
    }
    else
    {
        Tower* clicked = game->getTowerAt(mx, my);
        game->setSelectedTower(clicked);
        if (game != nullptr && selectedTowerType != TowerType::NONE && clicked == nullptr)
            game->handleTowerBuildRequest(mx, my, selectedTowerType);
    }
}
void InGameState::handleKeyInput(int keyCode)
{
    if (game == nullptr) return;
    if (game->isFinished() || !game->isRunning()) {
        if (keyCode == 58) { // Enter
            app.changeState(gameState::LEVELSELECT);
        }
        return; 
    }
    if(keyCode==58) //Enter
    {
        game->startNextWave();
    }
    else if (keyCode == 20) //U
    {
        game->handleTowerUpgrade();
	}
    else if(keyCode == 18) //S
    {
        if (game->getSelectedTower()!=nullptr)
        {
            game->sellTower(game->getSelectedTower());
        }
      
    }
}
void InGameState::draw() const
{
    Graphics& g = app.getGraphics();

    game->draw(g);
    Tower* sel = game->getSelectedTower();
    if (sel != nullptr) {
        g.drawRangeCircle(sel->getPosition(), sel->getRange());
    }
    g.drawSidebarBackground();
    for (const auto& btn : sidebarButtons) {
        g.drawTowerButton(btn, selectedTowerType == btn.type, game->getMoney());
    }
    if (sel != nullptr) {
        g.drawTowerStats(sel->getDamage(), sel->getFireRate(),
            sel->getRange(), sel->getLevel(), sel->getUpgradeCost());
    }
    g.drawStatBar(
        game->getPlayerHp(), game->getMoney(),
        game->getWaveManager().getCurrentWave(),
        game->getWaveManager().getCountdown(),
        game->getWaveManager().getIsCountingDown());

    if (!game->isRunning()) {
        g.drawGameOver();
    }
    else if (game->isFinished()) {
        g.drawYouWin();   
    }
}
void InGameState::update(float dt) {
    if (!valid) {
        app.changeState(gameState::LEVELSELECT);
        return;
    }
    if (game != nullptr) {
        game->update(dt);
    }
    
}
InGameState::~InGameState()
{
    delete game;
}

MapEditorState::MapEditorState(IApp& a): 
	State(a), eMap(13, 9, 170), selectedType(TileType::PATH), isSaved(false)
{
    initButtons();
}
void MapEditorState::initButtons() {
    buttons.push_back({ 2300, 100, 330, 50, "PATH", TileType::PATH});
    buttons.push_back({ 2300, 200, 330, 50, "BUILDABLE", TileType::BUILDABLE});
    buttons.push_back({ 2300, 300, 330, 50, "NOTBUILDABLE", TileType::NOTBUILDABLE});
}
void MapEditorState::handleClick(float x, float y)
{
    if(!isSaved)
    {
        for (const auto& btn : buttons) {
            if (btn.isClicked(x, y)) {
                selectedType = btn.type;
                return;
            }
        }
        int ts = eMap.getTileSize();
        int gridX = static_cast<int>(x / ts);
        int gridY = static_cast<int>(y / ts);
        if (gridX >= 0 && gridX < eMap.getWidth() &&
            gridY >= 0 && gridY < eMap.getHeight()) {
            eMap.setTile(gridY, gridX, selectedType);
        }
    }
    
}
void MapEditorState::handleKeyInput(int keyCode)
{
    if(!isSaved)
    {
        if (keyCode == 18) //S
            eMap.save(isSaved);
        else if (keyCode == 3)  //D
            eMap.undoLastPath();
	}
    if(isSaved && keyCode == 58) //Enter
		app.changeState(gameState::MAINMENU);
}
void MapEditorState::draw() const
{
    Graphics& g = app.getGraphics();
    eMap.draw(g);
    for (const auto& btn : buttons)
    {
        bool isSelected = (btn.type == selectedType);
        g.drawButton(btn, isSelected);
    }
    if (isSaved)
        g.drawMapSaved();
}

