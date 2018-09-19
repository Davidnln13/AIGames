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

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};