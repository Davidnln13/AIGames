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
void Player::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		IncreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		DecreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		DecreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		IncreaseRotation();
	}
}
void Player::Update()
{
	Move();
	m_sprite.setPosition(m_sprite.getPosition().x + cos(m_rotation * DEG_TO_RAD) * m_speed,
		m_sprite.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed);
	m_sprite.setRotation(m_rotation);

}
void Player::IncreaseSpeed()
{
	if (m_speed < 1)
	{
		m_speed += m_linearAccel;
	}
}
void Player::DecreaseSpeed()
{
	if (m_speed > -1)
	{
		m_speed -= m_linearAccel;
	}
}

void Player::IncreaseRotation()
{
	m_rotation += m_angularAccel;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::DecreaseRotation()
{
	m_rotation -= m_angularAccel;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}


void Player::Render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Sprite& Player::getSprite()
{
	return m_sprite;
}

