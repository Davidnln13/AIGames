#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>

double const Player::DEG_TO_RAD = M_PI / 180.0f;

Player::Player(float posX, float posY, int rotation)
	:
	m_speed(0),
	m_rotation(rotation),
	m_linearAccel(0.001),
	m_angularAccel(0.1)
{
	if (!m_texture.loadFromFile("player.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setRotation(m_rotation);
	m_sprite.setPosition(posX, posY);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	
}
void Player::update()
{
	move();
	m_sprite.setPosition(m_sprite.getPosition().x + cos(m_rotation * DEG_TO_RAD) * m_speed,
		m_sprite.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed);
	m_sprite.setRotation(m_rotation);

}
void Player::increaseSpeed()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += m_linearAccel;
	}
}
void Player::decreaseSpeed()
{
	if (m_speed > -m_maxSpeed)
	{
		m_speed -= m_linearAccel;
	}
}

void Player::increaseRotation()
{
	m_rotation += m_angularAccel;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= m_angularAccel;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}


void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Sprite& Player::getSprite()
{
	return m_sprite;
}

