#define _USE_MATH_DEFINES
#include "Enemy.h"
#include <cmath> 


Enemy::Enemy(float posX, float posY, int rotation, std::string behaviour)
{

	m_behaviour = behaviour;
	if (m_behaviour == "SEEK")
	{
		if (!m_texture.loadFromFile("SeekEnemy.png"))
		{
			std::string s("Error loading texture");
			throw std::exception(s.c_str());
		}
		m_sprite.setTexture(m_texture);
	}
	if (m_behaviour == "FLEE")
	{
		if (!m_texture.loadFromFile("FleeEnemy.png"))
		{
			std::string s("Error loading texture");
			throw std::exception(s.c_str());
		}
		m_sprite.setTexture(m_texture);
	}
	if (m_behaviour == "WANDER")
	{
		if (!m_texture.loadFromFile("wanderEnemy.png"))
		{
			std::string s("Error loading texture");
			throw std::exception(s.c_str());
		}
		m_sprite.setTexture(m_texture);
	}
	if (m_behaviour == "ARRIVE")
	{
		if (!m_texture.loadFromFile("arriveEnemy.png"))
		{
			std::string s("Error loading texture");
			throw std::exception(s.c_str());
		}
		m_sprite.setTexture(m_texture);
	}
	m_sprite.setPosition(posX, posY);
	m_sprite.setRotation(rotation);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
void Enemy::seekMove(sf::Sprite target)
{
	m_velocity = target.getPosition() - m_sprite.getPosition();
	m_velocity = vectorNormalise(m_velocity);
	m_velocity = sf::Vector2f(m_velocity.x * m_maxSpeed, m_velocity.y * m_maxSpeed);
	m_orientation = getNewOrientation(m_orientation, m_velocity);
}

void Enemy::fleeMove(sf::Sprite target)
{
	m_velocity = m_sprite.getPosition() - target.getPosition();
	m_velocity = vectorNormalise(m_velocity);
	m_velocity = sf::Vector2f(m_velocity.x * m_maxSpeed, m_velocity.y * m_maxSpeed);
	m_orientation = getNewOrientation(m_orientation, m_velocity);
}

void Enemy::wanderMove(sf::Sprite target)
{
	m_velocity = target.getPosition() - m_sprite.getPosition();
	m_velocity = vectorNormalise(m_velocity);
	m_orientation = getNewOrientation(m_orientation, m_velocity);

	//randomNum = rand() % 10;
	//if (randomNum <= 4)
	//	randomNum = 1;
	//else
	//	randomNum = -1;
	//m_orientation = m_orientation + m_maxOrientation * randomNum;
	m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation))*m_maxSpeed;
	std::cout << "velocity is " << m_velocity.x << ", " << m_velocity.y << " Orientation is " << m_orientation << std::endl;
}

void Enemy::arriveMove(sf::Sprite target)
{
	m_velocity = target.getPosition() - m_sprite.getPosition();
	if (vectorLength(m_velocity) < m_slowRadius)
	{
		m_velocity = sf::Vector2f(0, 0);
	}
	else 
	{
		m_velocity = m_velocity / m_timeToTarget;
		if (vectorLength(m_velocity) > m_maxSpeed)
		{
			m_velocity = vectorNormalise(m_velocity);
			m_velocity = sf::Vector2f(m_velocity.x *m_maxSpeed, m_velocity.y * m_maxSpeed);
		}
		m_orientation = getNewOrientation(m_orientation, m_velocity);
	}
}

void Enemy::update(sf::Sprite target)
{
	if (m_behaviour == "SEEK")
	{
		seekMove(target);
	}
	else if (m_behaviour == "FLEE")
	{
		fleeMove(target);
	}
	else if (m_behaviour == "WANDER")
	{
		wanderMove(target);
	}
	else if (m_behaviour == "ARRIVE")
	{
		arriveMove(target);
	}
	m_sprite.move(sf::Vector2f(m_velocity.x, m_velocity.y));
	m_sprite.setRotation(atan2(-m_velocity.x, m_velocity.y) * (180 / M_PI) +180);
}

void Enemy::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Sprite& Enemy::getSprite()
{
	return m_sprite;
}

float Enemy::getNewOrientation(float currentOrientation, sf::Vector2f currentVelocity)
{
	// Note atan2 returns an angle in radians which you 
	// may want to convert to degrees.
	if (vectorLength(currentVelocity) > 0)
	{
		return (atan2(-m_sprite.getPosition().x, m_sprite.getPosition().y))* 180 / M_PI;
	}
	else
	{
		return currentOrientation;
	}
}

float Enemy::vectorLength(sf::Vector2f v)
{
	float magnitudeV = ((v.x * v.x) + (v.y * v.y));
	magnitudeV = sqrt(magnitudeV);
	return magnitudeV;
}

sf::Vector2f Enemy::vectorNormalise(sf::Vector2f v)
{
	float mag = vectorLength(v);
	if (mag != 0)
	{
		return sf::Vector2f(v.x / mag, v.y / mag);
	}
	else
	{
		return sf::Vector2f(v.x, v.y);
	}
	
}
