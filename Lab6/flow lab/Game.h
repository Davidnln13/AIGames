#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>

class Game
{
public:
	Game();
	void run();
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	// main window
	sf::RenderWindow m_window;
private:

};