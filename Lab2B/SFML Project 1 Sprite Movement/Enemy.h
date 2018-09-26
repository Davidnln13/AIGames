#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

class Enemy
{
public:
	Enemy(float posX, float posY, int rotation, std::string behaviour);
	void seekMove(sf::Sprite target);
	void fleeMove(sf::Sprite target);
	void wanderMove(sf::Sprite target);
	void arriveMove(sf::Sprite target);

	void update(sf::Sprite target);
	void render(sf::RenderWindow& window);
	sf::Sprite& getSprite();
	float getNewOrientation(float currentOrientation, sf::Vector2f currentVelocity);
	float vectorLength(sf::Vector2f v);
	sf::Vector2f vectorNormalise(sf::Vector2f v);
	double static const RAD_TO_DEG;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::string m_behaviour;
	sf::Vector2f m_velocity;
	float m_maxSpeed = 0.1;
	float randomNum;
	float m_slowRadius = 10;
	float m_timeToTarget = 1;
	float m_orientation;
	float m_maxOrientation = 90;
};