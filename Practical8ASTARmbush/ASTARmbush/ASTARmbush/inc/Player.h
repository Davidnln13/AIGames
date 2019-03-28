#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include "Grid.h"
#include <iostream>


class Player
{
public:
	Player(int posX, int posY, Grid& grid);
	void update();
	void render(SDL_Renderer* renderer);
	Vector2f getPosition() { return m_position; }
	void updateRect();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
private:
	Vector2f m_position;
	SDL_Rect m_rect;
	Grid* m_grid;
};