#include "app.h"
#include "memtrace.h"


App::App() :
	window(sf::VideoMode(2700, 1650), "Tower Defense"),
	renderer(window),
	currentState(nullptr),
    accumulator(0.0f)
{
	window.setPosition(sf::Vector2i(75, 0));
	window.setFramerateLimit(60);
    lastTime = std::chrono::steady_clock::now();
	levelManager.loadLevels("levels.txt");
	changeState(gameState::MAINMENU);
}

void App::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			continue;
		}
		if (currentState == nullptr) continue;
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			currentState->handleClick((float)event.mouseButton.x, (float)event.mouseButton.y);
		}
		if (event.type == sf::Event::KeyPressed) {
			currentState->handleKeyInput(event.key.code);
		}
		
	}
}
App::~App()
{
	delete currentState;
}
void App::update(float dt)
{
	if (currentState != nullptr)
		currentState->update(dt);
}
void App::render()
{
	window.clear(sf::Color::Black);
	if (currentState != nullptr) {
		currentState->draw();
	}
	window.display();
}
void App::run()
{
	while (window.isOpen())
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
	}
}
void App::changeState(gameState type) {
	if (currentState != nullptr) {
		delete currentState;
		currentState = nullptr; 
	}
	switch (type) {
	case gameState::MAINMENU:
		currentState = new MainMenuState(*this);
		break;
	case gameState::INGAME:
		currentState = new InGameState(*this, levelManager.getCurrentLevel());
		break;
	case gameState::LEVELSELECT:
		currentState = new LevelSelectState(*this);
		break;
	case gameState::MAPEDITOR:
		currentState = new MapEditorState(*this);
		break;
	}
	
}