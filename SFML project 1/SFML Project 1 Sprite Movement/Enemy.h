#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(float posX, float posY, int rotation);
	void Move();
	void Update();
	void Render(sf::RenderWindow& window);
	sf::Sprite& getSprite();
	void setOnce(bool check);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	bool m_setOnce = false;
	int m_randomX;
	int m_randomY;
	float m_permaRandomX;
	float m_permaRandomY;
};