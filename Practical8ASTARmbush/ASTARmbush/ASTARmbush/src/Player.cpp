#include "../inc/Player.h"

Player::Player(int posX, int posY, Grid& grid)
	: m_position(Vector2f(posX, posY))
	, m_rect({posX*10,posY*10,10,10})
	, m_grid(&grid)
{

}
void Player::update()
{

}
void Player::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0,255,0,255);
	SDL_RenderFillRect(renderer, &m_rect);
	SDL_RenderDrawRect(renderer, &m_rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDrawPoint(renderer, m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2);
}

void Player::updateRect()
{
	m_rect = { (int)m_position.x * 10, (int)m_position.y * 10, 10, 10 };
}

void Player::moveUp()
{
	auto t = m_grid->getTiles();
	auto b = t[std::to_string((int)(m_position.x)) + "," + std::to_string((int)(m_position.y - 1))].getObstacle();
	if (m_position.y > 0 && b == false)
	{
		m_position.y -= 1;
		updateRect();
	}	
}

void Player::moveRight()
{
	auto t = m_grid->getTiles();
	auto b = t[std::to_string((int)(m_position.x+1)) + "," + std::to_string((int)(m_position.y))].getObstacle();
	if (m_position.x < 49 && b == false)
	{
		m_position.x += 1;
		updateRect();
	}
}

void Player::moveDown()
{
	auto t = m_grid->getTiles();
	auto b = t[std::to_string((int)(m_position.x)) + "," + std::to_string((int)(m_position.y+1))].getObstacle();
	if (m_position.y < 49 && b == false)
	{
		m_position.y += 1;
		updateRect();
	}	
}

void Player::moveLeft()
{
	auto t = m_grid->getTiles();
	auto b = t[std::to_string((int)(m_position.x - 1)) + "," + std::to_string((int)(m_position.y))].getObstacle();
	if (m_position.x > 0 && b == false)
	{
		m_position.x -= 1;
		updateRect();
	}
		
}
