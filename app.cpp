#include "app.h"
#include "memtrace.h"


App::App(std::istream& mapConfig, std::istream& waveConfig) :
	window(sf::VideoMode(2700, 1700), "Tower Defense"),
	renderer(window),
    game(new Game(mapConfig, waveConfig)),
    accumulator(0.0f),
	selectedTowerType(TowerType::NONE)
{
	window.setPosition(sf::Vector2i(75, 0));
    lastTime = std::chrono::steady_clock::now();
	initSidebar();
}
App::~App() {
    delete game;
}
void App::handleClicks(float mx, float my)
{
	float sidebarX = 2220;
	if(mx>sidebarX)
	{
		for (const TowerButton& button : sidebarButtons) 
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
		if (game != nullptr && selectedTowerType!=TowerType::NONE && clicked==nullptr)
			game->handleTowerBuildRequest(mx, my, selectedTowerType);
	}
		
}
void App::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			handleClicks((float)event.mouseButton.x, (float)event.mouseButton.y);
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
				if (game != nullptr) game->startNextWave();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
			if (game != nullptr) {
				Tower* t = game->getTowerAt((float)event.mouseButton.x, (float)event.mouseButton.y);
				if (t != nullptr) {
					game->sellTower(t); 
				}
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::U) {
				game->handleTowerUpgrade();
			}
		}
	}
}
void App::initSidebar()
{
	float buttonWidth = 150.0f;
	float buttonHeight = 50.0f;
	float startX = window.getSize().x - buttonWidth - 90.0f; 
	float startY = 100.0f; 
	float gap = 10.0f; 
	sidebarButtons.push_back({ TowerType::NORMAL, startX, startY, buttonWidth, buttonHeight });
	sidebarButtons.push_back({ TowerType::FAST,   startX, startY + (buttonHeight + gap), buttonWidth, buttonHeight });
	sidebarButtons.push_back({ TowerType::SNIPER, startX, startY + 2 * (buttonHeight + gap), buttonWidth, buttonHeight });
}
void App::update(float dt)
{
	if (game != nullptr)
		game->update(dt);
}
void App::render()
{
	window.clear(sf::Color::Black);
	if (game != nullptr)
	{
		game->draw(renderer);
		for (const auto& btn : sidebarButtons) {
			renderer.drawTowerButton(btn, selectedTowerType == btn.type);
		}
		Tower* sel = game->getSelectedTower();
		if (sel != nullptr) {
			renderer.drawTowerStats(sel->getDamage(), sel->getFireRate(),
									sel->getRange(), sel->getLevel(), sel->getUpgradeCost());
			renderer.drawRangeCircle(sel->getPosition(), sel->getRange());
		}
		renderer.drawStatBar(
			game->getPlayerHp(), game->getMoney(), 
			game->getWaveManager().getCurrentWave(), 
			game->getWaveManager().getCountdown(), 
			game->getWaveManager().getIsCountingDown());
		if (!game->isRunning()) {
			renderer.drawGameOver();
		}
	}
	window.display();
}
void App::run()
{
	while (window.isOpen() && game!=nullptr)
	{
		auto now = std::chrono::steady_clock::now();
		float frameTime = std::chrono::duration<float>(now - lastTime).count();
		lastTime = now;
		if (frameTime > 0.25f) frameTime = 0.25f;
		accumulator += frameTime;
		handleEvents();
		while (accumulator >= dt)
		{
			update(dt);
			accumulator -= dt;
		}
		render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
