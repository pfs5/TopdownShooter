#include "Display.h"
#include "VectorOperations.h"
#include <memory>
#include <iostream>

namespace Display {
	std::unique_ptr<sf::RenderWindow> window;
	bool isWindowInFocus = true;

	void init() {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;

		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Default, settings);
		window.get()->setFramerateLimit(60);
	}

	void clear(const sf::Color& _color) {
		window->clear(_color);
	}

	void display() {
		window->display();
	}

	void draw(const sf::Drawable& _drawable) {
		window->draw(_drawable);
	}

	void checkWindowEvents() {
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::KeyPressed) {
				// TODO
			}
			if (e.type == sf::Event::KeyReleased) {
				// TODO
			}
			if (e.type == sf::Event::Closed) {
				window->close();
			}
			if (e.type == sf::Event::GainedFocus) {
				isWindowInFocus = true;
			}
			if (e.type == sf::Event::LostFocus) {
				isWindowInFocus = false;
			}
		}
	}

	bool isOpen() {
		return window->isOpen();
	}

	bool isInFocus() {
		return isWindowInFocus;
	}

	sf::RenderWindow &getWindow() {
		return *window;
	}
	sf::Vector2f worldToScreenPosition(const sf::Vector2f & worldPos)
	{
		sf::Vector2f viewCenter = getWindow().getView().getCenter();
		sf::Vector2f viewPosition = viewCenter - VectorOperations::utof(getWindow().getSize()) / 2.f;

		return worldPos - viewPosition;
	}
}