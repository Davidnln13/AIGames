#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include "Grid.h"
#include "Player.h"
#include <iostream>


class Enemy
{
public:
	Enemy(int posX, int posY, Grid& grid, Player& player);
	void update();
	void render(SDL_Renderer* renderer);
	Vector2f getPosition() { return m_position; }
	void pathfind();

private:
	Vector2f m_position;
	SDL_Rect m_rect;
	Grid* m_grid;
	Player* m_player;
	std::vector<Vector2f> m_path;
};