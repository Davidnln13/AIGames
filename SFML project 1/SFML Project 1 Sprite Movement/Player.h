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
	void IncreaseSpeed(std::string direction);
	void DecreaseSpeed();
	void CheckSpeedBoundaries();
private:
	sf::Sprite m_sprite;
	bool checkIfMoving = false;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_currentVelocity;
	float m_rotation;
	float m_linearAccel;
	float m_angularAccel;
};