#include "Player.h"

Player::Player(float posX, float posY, int rotation)
{
	m_position = sf::Vector2f(posX, posY);
	m_currentVelocity = sf::Vector2f(0,0);
	m_rotation = rotation;
	m_linearAccel = 0.02;
	m_angularAccel = 1;

	if (!m_texture.loadFromFile("pacman.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_rotation);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
void Player::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		IncreaseSpeed("UP");
		checkIfMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		IncreaseSpeed("DOWN");
		checkIfMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		IncreaseSpeed("LEFT");
		checkIfMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		IncreaseSpeed("RIGHT");
		checkIfMoving = true;
	}
}
void Player::Update()
{
	std::cout << "Y velo " << m_currentVelocity.y << " Y accel" << m_linearAccel << std::endl;
	Move();
	CheckSpeedBoundaries();
	if (m_currentVelocity.x == 0 && m_currentVelocity.y == 0)
	{
		checkIfMoving = false;
	}
	if (checkIfMoving == true)
	{
		DecreaseSpeed();
	}
	m_sprite.setRotation(m_rotation);
	m_sprite.move(m_currentVelocity.x, m_currentVelocity.y);
}
void Player::IncreaseSpeed(std::string direction)
{
	if (direction == "UP" && m_currentVelocity.y > -1)
	{
		m_currentVelocity.y -= m_linearAccel;
	}
	if (direction == "DOWN" && m_currentVelocity.y < 1)
	{
		m_currentVelocity.y += m_linearAccel;
	}
	if (direction == "LEFT" && m_currentVelocity.x > -1)
	{
		m_currentVelocity.x -= m_linearAccel;
	}
	if (direction == "RIGHT" && m_currentVelocity.x < 1)
	{
		m_currentVelocity.y += m_linearAccel;
	}
}
void Player::DecreaseSpeed()
{
	if (m_currentVelocity.x > 0)
	{
		m_currentVelocity.x -= 0.01;
		if (m_currentVelocity.x < 0.1)
		{
			m_currentVelocity.x = 0;
		}
	}

	if (m_currentVelocity.x < 0)
	{
		m_currentVelocity.x += 0.01;
		if (m_currentVelocity.x > -0.1)
		{
			m_currentVelocity.x = 0;
		}
	}

	if (m_currentVelocity.y > 0)
	{
		m_currentVelocity.y -= 0.01;
		if (m_currentVelocity.y < 0.1)
		{
			m_currentVelocity.y = 0;
		}
	}

	if (m_currentVelocity.y < 0)
	{
		m_currentVelocity.y += 0.01;
		if (m_currentVelocity.y > -0.1)
		{
			m_currentVelocity.y = 0;
		}
	}
}

void Player::CheckSpeedBoundaries()
{
	if (m_currentVelocity.y < -1)
	{
		m_currentVelocity.y = -1;
	}
	if (m_currentVelocity.y > 1)
	{
		m_currentVelocity.y = 1;
	}
	if (m_currentVelocity.x < -1)
	{
		m_currentVelocity.x = -1;
	}
	if (m_currentVelocity.x > 1)
	{
		m_currentVelocity.x = 1;
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

