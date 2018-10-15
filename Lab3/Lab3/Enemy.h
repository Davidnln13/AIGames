#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Player.h"

class Enemy
{
public:
	Enemy(sf::Vector2f position, std::string behaviour, float maxSpeed);
	~Enemy();
	//behaviour functions 
	void seekMove(Player* p);
	void pursueMove(Player* p);
	void fleeMove(Player* p);
	void wanderMove(Player* p);
	void arriveMove(Player* p);
	sf::Vector2f truncate(sf::Vector2f v, float max);
	sf::Vector2f wanderCalc();
	void setAngle(sf::Vector2f& v, float f);
	void update(Player* p);
	void render(sf::RenderWindow& window);
	//getters
	sf::Sprite& getSprite();
	sf::Vector2f getVelocity();
	//orientation based on ..
	float getNewOrientationByVelocity(float currentOrientation, sf::Vector2f currentVelocity);
	float getNewOrientationByPosition(float currentOrientation, sf::Vector2f currentVelocity);
	//vector calculations
	float vectorLength(sf::Vector2f v);
	sf::Vector2f vectorNormalise(sf::Vector2f v);
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::string m_behaviour;
	sf::Vector2f m_velocity;
	sf::Vector2f m_desiredVelocity;
	sf::Vector2f m_steering;
	sf::Vector2f m_position;
	sf::Font m_font;
	sf::Text m_text;
	float m_maxSpeed;
	float randomNum;
	float m_orientation;
	float m_maxOrientation = 1;
	//arrive variables
	float m_slowRadius = 150;
	//wander variables 
	sf::Vector2f m_circleCenter;
	sf::Vector2f m_wanderForce;
	sf::Vector2f m_displacement;
	float m_wanderAngle;
	const float CIRCLE_DISTANCE = 100.0f;
	const float CIRCLE_RADIUS = 25.0f;
	const float ANGLE_CHANGE = 1.0f;
	//pursue
	sf::Vector2f m_futurePos;
	int m_noOfIterationsAhead;


};