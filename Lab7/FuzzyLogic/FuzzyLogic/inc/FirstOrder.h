#pragma once
#include <SFML/Graphics.hpp>
// class to represent the first order aka empire
class FirstOrder
{
public:
	FirstOrder(sf::Vector2f pos, sf::Vector2f size, int rotation);
	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	int m_rotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};