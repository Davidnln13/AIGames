#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>

class Game
{
public:
	Game();
	void checkBoundaries(sf::Sprite &s);
	void checkCollisions(sf::Sprite &p, sf::Sprite &e);
	void run();
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
private:
	int m_score = 0;

	Player m_player;
	Enemy m_enemy;

	sf::Font m_font;
	sf::Text m_text;

};