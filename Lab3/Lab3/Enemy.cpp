#define _USE_MATH_DEFINES
#include "Enemy.h"
#include <cmath> 


Enemy::Enemy(sf::Vector2f position, std::string behaviour, float maxSpeed) :
	m_behaviour(behaviour),
	m_velocity(0, 0),
	m_desiredVelocity(0, 0),
	m_steering(0,0),
	m_position(position),
	m_maxSpeed(maxSpeed),
	m_orientation(0),
	m_circleCenter(0,0),
	m_wanderForce(0,0),
	m_displacement(0,-1),
	m_wanderAngle(0),
	m_futurePos(0,0),
	m_noOfIterationsAhead(0)
{
	if (!m_font.loadFromFile("arial.ttf"))
	{

	}
	if (m_behaviour == "SEEK")
	{
		if (!m_texture.loadFromFile("SeekEnemy.png")) {}
		m_text.setFillColor(sf::Color::Red);
	}
	else if (m_behaviour == "FLEE")
	{
		if (!m_texture.loadFromFile("FleeEnemy.png")) {}
		m_text.setFillColor(sf::Color::Green);
	}
	else if (m_behaviour == "PURSUE")
	{
		if (!m_texture.loadFromFile("PursueEnemy.png")) {}
		m_text.setFillColor(sf::Color::Magenta);
	}
	else if (m_behaviour == "WANDER")
	{
		if (!m_texture.loadFromFile("WanderEnemy.png")) {}
		m_text.setFillColor(sf::Color::Blue);
	}
	else if (m_behaviour == "ARRIVE S" || m_behaviour == "ARRIVE F")
	{
		if (!m_texture.loadFromFile("ArriveEnemy.png")) {}
		m_text.setFillColor(sf::Color::Yellow);
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setString(m_behaviour);

	//setting up the sprite initially 
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
Enemy::~Enemy()
{

}
void Enemy::seekMove(Player* p)
{
	//old seek
	/*m_velocity = target.getPosition() - m_sprite.getPosition();
	m_velocity = vectorNormalise(m_velocity);
	m_velocity = sf::Vector2f(m_velocity.x * m_maxSpeed, m_velocity.y * m_maxSpeed);
	m_orientation = getNewOrientationByPosition(m_orientation, m_velocity);*/

	m_desiredVelocity = p->getSprite().getPosition() - m_sprite.getPosition();
	m_desiredVelocity = vectorNormalise(m_desiredVelocity);
	m_desiredVelocity = sf::Vector2f(m_desiredVelocity.x * m_maxSpeed, m_desiredVelocity.y * m_maxSpeed);

	m_steering = m_desiredVelocity - m_velocity;
	m_steering = truncate(m_steering, 10.0f);

	m_velocity = truncate(m_velocity + m_steering, m_maxSpeed); 

	m_orientation = getNewOrientationByVelocity(m_orientation, m_velocity);
	//std::cout << "velocity is " << m_velocity.x << ", " << m_velocity.y << " Orientation is " << m_orientation << std::endl;
}

void Enemy::fleeMove(Player* p)
{
	m_velocity = m_sprite.getPosition() - p->getSprite().getPosition();
	m_velocity = vectorNormalise(m_velocity);
	m_velocity = sf::Vector2f(m_velocity.x * m_maxSpeed, m_velocity.y * m_maxSpeed);
	m_orientation = getNewOrientationByPosition(m_orientation, m_velocity);
}

void Enemy::pursueMove(Player* p)
{
  m_desiredVelocity  = p->getSprite().getPosition() - m_sprite.getPosition();
  m_noOfIterationsAhead = vectorLength(m_desiredVelocity)/m_maxSpeed;
  m_futurePos = p->getSprite().getPosition() + p->getVelocity() * (float)m_noOfIterationsAhead;
  //std::cout << m_noOfIterationsAhead << std::endl;

  m_desiredVelocity = m_futurePos - m_sprite.getPosition();
  m_desiredVelocity = vectorNormalise(m_desiredVelocity);
  m_desiredVelocity = sf::Vector2f(m_desiredVelocity.x * m_maxSpeed, m_desiredVelocity.y * m_maxSpeed);
  m_steering = m_desiredVelocity - m_velocity;
  m_steering = truncate(m_steering, 10.0f);
  m_velocity = truncate(m_velocity + m_steering, m_maxSpeed);
  m_orientation = getNewOrientationByVelocity(m_orientation, m_velocity);
}

void Enemy::wanderMove(Player* p)
{
	//old wander
	//m_velocity = target->getPosition() - m_sprite.getPosition();
	//m_velocity = vectorNormalise(m_velocity);
	//m_orientation = getNewOrientationByPosition(m_orientation, m_velocity);

	//randomNum = rand() % 10;
	//if (randomNum <= 4)
	//	randomNum = 1;
	//else
	//	randomNum = -1;
	//m_orientation = m_orientation + m_maxOrientation * randomNum;

	////seek
	////m_velocity = sf::Vector2f(m_velocity.x * m_maxSpeed, m_velocity.y * m_maxSpeed);
	////seek
	// 
	//m_velocity = sf::Vector2f(sin(m_orientation*(M_PI/180.0f)), -cos(m_orientation*(M_PI/180.0f)))*m_maxSpeed;
	////std::cout << "velocity is " << m_velocity.x << ", " << m_velocity.y << " Orientation is " << m_orientation << std::endl;

	// Calculate the wander force#
	m_steering = wanderCalc();
	m_steering = truncate(m_steering, 10.0f);
	m_velocity = truncate(m_velocity + m_steering, m_maxSpeed);
	m_orientation = getNewOrientationByVelocity(m_orientation, m_velocity);

}

sf::Vector2f Enemy::wanderCalc()
{
	// Calculate the circle center
	m_circleCenter = m_velocity;

	m_circleCenter = vectorNormalise(m_circleCenter);
	m_circleCenter *= CIRCLE_DISTANCE;
	// Calculate the displacement force
	m_displacement *= CIRCLE_RADIUS;
	// Randomly change the vector direction
	// by making it change its current angle
	m_displacement = sf::Vector2f(0, -1);
	setAngle(m_displacement, m_wanderAngle);
	//
	// Change wanderAngle just a bit, so it
	// won't have the same value in the
	// next game frame.
	randomNum = rand() % 10;
	m_wanderAngle += (((randomNum/10) +0.05)  * ANGLE_CHANGE) - (ANGLE_CHANGE * .5);
	//std::cout << m_wanderAngle << std::endl;
	// Finally calculate and return the wander force
	
	m_wanderForce = m_circleCenter + m_displacement;
	return m_wanderForce;
}
void Enemy::setAngle(sf::Vector2f& v, float f)
{
	float len = vectorLength(v);
	v.x = cos(f * (M_PI/180.0f)) * len;
	v.y = sin(f* (M_PI / 180.0f)) * len;

}
void Enemy::arriveMove(Player* p)
{
	//old arrival
	/*m_velocity = target.getPosition() - m_sprite.getPosition();
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
		m_orientation = getNewOrientationByPosition(m_orientation, m_velocity);
	}*/

	// Calculate the desired velocity
	m_desiredVelocity = p->getSprite().getPosition() - m_sprite.getPosition();
	float distance = vectorLength(m_desiredVelocity);
	// Check the distance to detect whether the character
	// is inside the slowing area
	if (distance < m_slowRadius) 
	{
		// Inside the slowing area
		m_desiredVelocity = vectorNormalise(m_desiredVelocity) * m_maxSpeed * (distance / m_slowRadius);
	}
	else 
	{
		// Outside the slowing area.
		m_desiredVelocity = vectorNormalise(m_desiredVelocity) * m_maxSpeed;
	}

	// Set the steering based on this
	m_steering = m_desiredVelocity - m_velocity;
	m_velocity = truncate(m_velocity + m_steering, m_maxSpeed);
	m_orientation = getNewOrientationByVelocity(m_orientation, m_velocity);
	//if (m_behaviour == "ARRIVE F")
	//{
	//	std::cout << "Velocity " << m_velocity.x << "," << m_velocity.y << std::endl;
	//}
}

sf::Vector2f Enemy::truncate(sf::Vector2f v, float max)
{
	float i = 0;
	i = max / vectorLength(v);
	i = i < 1.0 ? i : 1.0;
	v *= i;
	return v;
}


void Enemy::update(Player* p)
{
	if (m_behaviour == "SEEK")
	{
		seekMove(p);
	}
	else if (m_behaviour == "PURSUE")
	{
		pursueMove(p);
	}
	else if (m_behaviour == "FLEE")
	{
		fleeMove(p);
	}
	else if (m_behaviour == "WANDER")
	{
		wanderMove(p);
	}
	else if (m_behaviour == "ARRIVE S" || m_behaviour == "ARRIVE F")
	{
		arriveMove(p);
		
	}
	m_text.setPosition(m_sprite.getPosition().x - 80, m_sprite.getPosition().y - 60);
	m_sprite.move(sf::Vector2f(m_velocity.x, m_velocity.y));
	m_sprite.setRotation(m_orientation);
}

void Enemy::render(sf::RenderWindow &window)
{
	window.draw(m_text);
	window.draw(m_sprite);
}

sf::Sprite& Enemy::getSprite()
{
	return m_sprite;
}

float Enemy::getNewOrientationByPosition(float currentOrientation, sf::Vector2f currentVelocity)
{
	// Note atan2 returns an angle in radians which you 
	// may want to convert to degrees.
	if (vectorLength(currentVelocity) > 0)
	{
		const auto radAngle = atan2(-m_sprite.getPosition().y, m_sprite.getPosition().x);
		return (radAngle)* (180 / M_PI);
	}
	else
	{
		return currentOrientation;
	}
}

float Enemy::getNewOrientationByVelocity (float currentOrientation, sf::Vector2f currentVelocity)
{
	// Note atan2 returns an angle in radians which you 
	// may want to convert to degrees.
	if (vectorLength(currentVelocity) > 0)
	{
		return (atan2(-currentVelocity.x, currentVelocity.y))* (180.0f / M_PI) + 180;
	}
	else
	{
		return currentOrientation;
	}
}

float Enemy::vectorLength(sf::Vector2f v)
{
	float magnitudeV = sqrt((v.x * v.x) + (v.y * v.y));
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
