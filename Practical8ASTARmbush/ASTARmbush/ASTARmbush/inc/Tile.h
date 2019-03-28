#pragma once 
#include "SDL.h"
#include "Vector2f.h"
#include <vector>
class Tile
{
public:
	Tile();
	Tile(int posX, int posY, bool obstacle);
	void update();
	void render(SDL_Renderer* renderer);
	//getters
	Vector2f getPos() { return m_position; }
	bool getObstacle() { return m_obstacle; }
private:
	Vector2f m_position;
	bool m_obstacle;
	SDL_Rect m_rect;
	//a*
	bool m_visited;
	float m_hCost;
	float m_gCost;
	float m_fCost;
	float m_goal;
	Tile* m_previous;
	std::vector<Tile*> m_neighbours;
};