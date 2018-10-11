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
	void run();
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
private:
	Player m_player;
	Enemy m_seekEnemy;
	Enemy m_fleeEnemy;
	Enemy m_wanderEnemy;
	Enemy m_arriveEnemy;

	sf::Sprite m_backgroundImageSprite;
	sf::Texture m_backgroundImageTexture;

	sf::Font m_font;
	sf::Text m_seekText;
	sf::Text m_wanderText;
	sf::Text m_fleeText;
	sf::Text m_arriveText;

};