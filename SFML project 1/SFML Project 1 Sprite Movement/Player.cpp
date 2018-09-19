#include "Player.h"

Player::Player(float posX, float posY, int rotation)
{
	if (!m_texture.loadFromFile("pacman.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(posX, posY);
	m_sprite.setRotation(rotation);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
void Player::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_sprite.move(0, -0.5);
		m_sprite.setRotation(270);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_sprite.move(0, +0.5);
		m_sprite.setRotation(90);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.move(-0.5,0);
		m_sprite.setRotation(180);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.move(+0.5, 0);
		m_sprite.setRotation(0);
	}
}
void Player::Update()
{
	Move();
}

void Player::Render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Sprite& Player::getSprite()
{
	return m_sprite;
}
