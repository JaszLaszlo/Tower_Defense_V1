#include "app.h"

App::App(std::istream& mapConfig)
    : window(sf::VideoMode(2410, 1700), "Tower Defense TD"),
    renderer(window),
    game(new Game(100, mapConfig)),
    accumulator(0.0f),
	selectedTower(TowerType::NONE)
{
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
				selectedTower = button.type;
				break;
			}
		}
	}
	else if (game != nullptr && selectedTower!=TowerType::NONE)
		game->handleTowerBuildRequest(mx, my, selectedTower);
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
	}
}
void App::initSidebar()
{
	float buttonWidth = 150.0f;
	float buttonHeight = 50.0f;
	float startX = window.getSize().x - buttonWidth - 20.0f; 
	float startY = 20.0f; 
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
			renderer.drawTowerButton(btn, selectedTower == btn.type);
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
