#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Resistance.h"
#include "FirstOrder.h"
#include "FuzzyLogic.h"

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
private:
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_threatLevel;
	sf::Text m_axisDistance;
	sf::Text m_axisSize;
	sf::Text m_reset;
	sf::Text m_allySize;
	std::vector<Resistance*> m_allies;
	std::vector<FirstOrder*> m_axis;
};