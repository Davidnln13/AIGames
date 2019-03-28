#pragma once
#include "SDL.h"
#include "../inc/Tile.h"
#include <map> 
#include <vector>



class Grid
{
public:
	Grid();
	Grid(int x, int y);
	void update();
	void render(SDL_Renderer* renderer);
	std::map<std::string, Tile> getTiles() { return m_tiles; };
private:
	std::map<std::string, Tile> m_tiles;
};