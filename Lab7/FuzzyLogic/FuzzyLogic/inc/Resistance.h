#pragma once
#include <SFML/Graphics.hpp>
// class to represent the rebel resistance aka allies
class Resistance
{
public:
	Resistance(sf::Vector2f pos, sf::Vector2f size, int rotation);
	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	int m_rotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};