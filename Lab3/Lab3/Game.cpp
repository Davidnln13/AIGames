#include "Game.h"
#include <cstdlib>
/// <summary>
/// @author David Nolan
/// @date September 2018
/// @version 1.0
/// 
/// </summary>


// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;


/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()
	: 
	m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default),
	m_player(new Player(270,450,0)),
	m_dynamicSeekEnemy(sf::Vector2f(570,150),"SEEK",0.1),
	m_pursueEnemy(sf::Vector2f(570, 450),"PURSUE",0.1),
	m_dynamicWanderEnemy(sf::Vector2f(570, 300),"WANDER",0.1),
	m_dynamicArriveEnemy(sf::Vector2f(570, 600),"ARRIVE S",0.1),
	m_dynamicArriveEnemy2(sf::Vector2f(570, 750),"ARRIVE F",0.2)
{
	if (!m_backgroundImageTexture.loadFromFile("background.jpg"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	else
	{
		m_backgroundImageSprite.setTexture(m_backgroundImageTexture);
	}
	m_backgroundImageSprite.setScale(2, 2);
}


	/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;		
		}
		update(MS_PER_UPDATE);
		render();
	}
}

/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	m_dynamicSeekEnemy.update(m_player);
	m_pursueEnemy.update(m_player);
	m_dynamicWanderEnemy.update(m_player);
	m_dynamicArriveEnemy.update(m_player);
	m_dynamicArriveEnemy2.update(m_player);
	m_player->update(); 

	checkBoundaries(m_dynamicSeekEnemy.getSprite());
	checkBoundaries(m_pursueEnemy.getSprite());
	checkBoundaries(m_dynamicWanderEnemy.getSprite());
	checkBoundaries(m_dynamicArriveEnemy.getSprite());
	checkBoundaries(m_dynamicArriveEnemy2.getSprite());
	checkBoundaries(m_player->getSprite());	
}

void Game::checkBoundaries(sf::Sprite &s)
{	
	if (s.getPosition().x < 0)
	{
		s.setPosition(m_window.getSize().x - 1, s.getPosition().y);
	}
	if (s.getPosition().x > m_window.getSize().x)
	{
		s.setPosition(1, s.getPosition().y);
	}
	if (s.getPosition().y < 0)
	{
		s.setPosition(s.getPosition().x, m_window.getSize().y - 1);
	}
	if (s.getPosition().y > m_window.getSize().y)
	{
		s.setPosition(s.getPosition().x, 1);
	}

}
/// <summary>
/// @brief draw the window for the game.
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	// Draw sprites etc. here using m_window.draw()...
	m_window.draw(m_backgroundImageSprite);

	m_player->render(m_window);
	m_dynamicSeekEnemy.render(m_window);
	m_dynamicWanderEnemy.render(m_window);
	m_pursueEnemy.render(m_window);
	m_dynamicArriveEnemy.render(m_window);
	m_dynamicArriveEnemy2.render(m_window);
	// Now display on-screen everthing that has been rendered to the SFML window.
	m_window.display();
}
