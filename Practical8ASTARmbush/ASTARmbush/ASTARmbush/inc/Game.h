#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <mutex>
#include "Grid.h"
#include "Player.h"
#include "Enemy.h"

//used for the multithreading but get to implement them properly
static std::vector<int> in;
static std::vector<int> last;
static std::mutex mutex;

class Game
{
public:
	Game();
	void init();
	void run();
	void update();
	void render();
	void processEvents(SDL_Event& e);
	void close();
	static int multithreading(Enemy* e, int index, int size);

private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 500;
	const int SCREEN_HEIGHT = 500;
	
	//The window we'll be rendering to
	SDL_Window* m_window;

	//The surface contained by the window
	SDL_Surface* m_screenSurface;

	//The window renderer
	SDL_Renderer* m_renderer;

	bool m_close;

	Grid m_grid;
	Player m_player;
	std::vector<Enemy*> m_enemies;
	std::vector<std::thread> m_threads;
};