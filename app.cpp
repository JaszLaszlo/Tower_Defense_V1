#include "app.h"

App::App(std::istream& mapConfig)
    : window(sf::VideoMode(2210, 1700), "Tower Defense TD"),
    renderer(window),
    game(new Game(100, mapConfig)),
    accumulator(0.0f)
{
    lastTime = std::chrono::steady_clock::now();
}
App::~App() {
    delete game;
}
void App::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
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
		game->draw(renderer);
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