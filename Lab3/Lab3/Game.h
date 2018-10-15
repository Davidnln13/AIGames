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
	Player* m_player;
	Enemy m_dynamicSeekEnemy;
	Enemy m_dynamicWanderEnemy;
	Enemy m_dynamicArriveEnemy;
	Enemy m_dynamicArriveEnemy2;
	Enemy m_pursueEnemy;
	//Enemy m_fleeEnemy;

	sf::Sprite m_backgroundImageSprite;
	sf::Texture m_backgroundImageTexture;
};