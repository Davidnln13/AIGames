#include "../inc/Enemy.h"

Enemy::Enemy(int posX, int posY, Grid& grid, Player& player)
	: m_position(Vector2f(posX, posY))
	, m_rect({ posX * 10,posY * 10,10,10 })
	, m_grid(&grid)
	, m_player(&player)
{

}
void Enemy::update()
{
	//pathfind();
}
void Enemy::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &m_rect);
	SDL_RenderDrawRect(renderer, &m_rect);
}
void Enemy::pathfind()
{

}

