#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(float posX, float posY, int rotation);
	~Player();
	void move();
	void update();
	void render(sf::RenderWindow& window);
	//getters
	sf::Sprite& getSprite();
	sf::Vector2f getVelocity();

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	double static const DEG_TO_RAD;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float m_speed;
	float m_maxSpeed = 0.5;
	float m_rotation;
	float m_linearAccel;
	float m_angularAccel;
};