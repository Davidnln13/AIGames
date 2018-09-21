#include "Enemy.h"

Enemy::Enemy(float posX, float posY, int rotation)
{
	if (!m_texture.loadFromFile("enemy.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(posX, posY);
	m_sprite.setRotation(rotation);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * 0.5, m_sprite.getTexture()->getSize().y * 0.5));
}
void Enemy::Move()
{
	if (m_setOnce == false)
	{
		m_setOnce = true;
		srand((int)time(0));

		m_randomX = (rand() % 100) + 1;
		m_randomY = (rand() % 100) + 1;
		if (m_randomX <= 50)
		{
			m_permaRandomX = -0.3;
		}
		else
			m_permaRandomX = 0.3;
		if (m_randomY <= 50)
		{
			m_permaRandomY = -0.3;
		}
		else
			m_permaRandomY = 0.3;
	}
	m_sprite.move(sf::Vector2f(m_permaRandomX, m_permaRandomY));
}

void Enemy::Update()
{
	Move();
}

void Enemy::Render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Sprite& Enemy::getSprite()
{
	return m_sprite;
}

void Enemy::setOnce(bool check)
{
	m_setOnce = check;
}