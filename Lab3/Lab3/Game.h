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
	void collisionAvoidance();
	float distance(sf::Vector2f a, sf::Vector2f b);
	bool lineIntersects(sf::Vector2f a, sf::Vector2f a2, Enemy* obstacle);
	//vector calculations
	float vectorLength(sf::Vector2f v);
	sf::Vector2f vectorNormalise(sf::Vector2f v);
	Enemy findMostThreatening();

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
	//collision avoidance
	sf::Vector2f ahead;
	sf::Vector2f ahead2;
	sf::Vector2f avoidanceForce;
	const float MAX_SEE_AHEAD = 100;
	const float MAX_AVOID_FORCE = 20;
	int obstacleArrayLength = 5;
	Enemy* m_obstacles[5];
};