#pragma once
#include <SFML/Graphics.hpp>

/**
	Handles all display operations including window management and drawing
**/
namespace Display {
	constexpr uint16_t HEIGHT = 900;
	constexpr uint16_t WIDTH = static_cast<uint16_t>(HEIGHT * 16.f / 9.f);
	const std::string TITLE = "Concept game";

	const float UPS = 60;   // 60

	/**
	* Initialize window
	*/
	void init();

	/**
	* Clears window using input color
	* @param colour
	*/
	void clear(const sf::Color& _color = { 0, 0, 0 });

	/**
	* Display content on window
	*/
	void display();

	/**
	* Draw object on window
	* @param drawable
	*/
	void draw(const sf::Drawable& _drawable);

	/**
	*
	*/
	void checkWindowEvents();

	/**
	* Check if window is open
	* @return
	*/
	bool isOpen();

	/*
	* Check if window is in focus
	* @return true if window is in focus, false otherwise
	*/
	bool isInFocus();

	/**
	* Returns window reference
	* @return
	*/
	sf::RenderWindow &getWindow();
};