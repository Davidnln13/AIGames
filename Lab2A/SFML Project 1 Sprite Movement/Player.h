#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(float posX, float posY, int rotation);
	void Move();
	void Update();
	void Render(sf::RenderWindow& window);
	sf::Sprite& getSprite();
	void IncreaseSpeed();
	void DecreaseSpeed();
	void IncreaseRotation();
	void DecreaseRotation();
	double static const DEG_TO_RAD;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float m_speed;
	int m_maxSpeed = 3;
	float m_rotation;
	float m_linearAccel;
	float m_angularAccel;
};