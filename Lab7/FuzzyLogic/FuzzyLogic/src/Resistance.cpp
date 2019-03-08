#include "../inc/Resistance.h"

Resistance::Resistance(sf::Vector2f pos, sf::Vector2f size, int rotation)
	: m_position(pos)
	, m_size(size)
	, m_rotation(rotation)
{
	m_texture.loadFromFile("res/resistance.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin((m_sprite.getGlobalBounds().width / 2), m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(m_rotation);
	m_sprite.setScale(m_size.x, m_size.y);
}

void Resistance::update()
{
}

void Resistance::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
