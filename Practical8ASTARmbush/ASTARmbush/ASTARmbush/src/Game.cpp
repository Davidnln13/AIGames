#include "../inc/Game.h"
#include <thread>

Game::Game()
	: m_window(NULL)
	, m_screenSurface(NULL)
	, m_renderer(NULL) 
	, m_close(false)
	, m_grid(50,50)
	, m_player(25,25, m_grid)
{
	for (int i = 0; i < 50; i++)
	{
		auto b = m_grid.getTiles()[std::to_string(i) + "," + std::to_string(5)].getObstacle();
		if(b == false)
			m_enemies.push_back(new Enemy(i, 5, m_grid, m_player));
	}
}
void Game::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		m_window = SDL_CreateWindow("A*mbush", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_screenSurface = SDL_GetWindowSurface(m_window);
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		}
		run();
	}
}

void Game::run()
{
	SDL_Event e;
	while (!m_close)
	{
		processEvents(e);
		update();
		render();
	}
	close();
}

void Game::update()
{
	m_grid.update();
	int d = 1;
	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_threads.push_back(std::thread(multithreading, m_enemies.at(i), i, m_enemies.size()));
	}
	m_player.update();
}

int Game::multithreading(Enemy* e, int index, int size)
{
	while (true)
	{
		for (int j = 0; j < size - 1; j++)
		{
			in[index] = j;
			last[j] = index;

			for (int k = 0; k < size - 1; k++)
			{
				while (last[j] == index && k != index)
				{
					continue;
				}
			}
		}
	//	critical section 
		mutex.lock();
		//lock mutex(ran out of time)
		//update the enemies
		e->update();

		//critical section over
		in[index] = 0;
		mutex.unlock();
	}
	return 0;
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	m_grid.render(m_renderer);
	for (Enemy* e : m_enemies)
	{
		e->render(m_renderer);
	}
	m_player.render(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(m_renderer);
}

void Game::processEvents(SDL_Event& e)
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			m_close = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				m_close = true;
			}
			if (e.key.keysym.sym == SDLK_UP)
			{
				m_player.moveUp();
			}
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				m_player.moveDown();
			}
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				m_player.moveLeft();
			}
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				m_player.moveRight();
			}
		}
	}
}

void Game::close()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);

	m_window = NULL;
	m_screenSurface = NULL;
	m_renderer = NULL;

	SDL_Quit();
}