#include "../inc/Grid.h"

Grid::Grid()
{

}
Grid::Grid(int x, int y)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			bool obstacle = false;
			if ((j == 5 && i < 35) || (j == 24 && i > 10 && i < 40) || (j == 35 && i > 3 && i < 30))
			{
				obstacle = true;
			}
			auto t = Tile(j * 10, i * 10, obstacle);
			m_tiles[std::to_string(j) + "," + std::to_string(i)] = t;
		}
	}
}

void Grid::update()
{

}
void Grid::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (auto& tile : m_tiles)
		tile.second.render(renderer);
}