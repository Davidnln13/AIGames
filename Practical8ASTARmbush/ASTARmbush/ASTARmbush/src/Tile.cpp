#include "../inc/Tile.h"
Tile::Tile()
{

}
Tile::Tile(int posX, int posY, bool obstacle)
	: m_position(posX, posY)
	, m_obstacle(obstacle)
	, m_rect({ posX, posY, 10,10 })
	, m_visited(false)
	, m_hCost(0)
	, m_gCost(0)
	, m_fCost(0)
	, m_goal(0)
{

}
void Tile::update()
{

}
void Tile::render(SDL_Renderer* renderer)
{
	if (m_obstacle)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(renderer, m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h);

	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &m_rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &m_rect);
	}
}