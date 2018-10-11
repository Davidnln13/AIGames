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
	m_player(270,450,0),
	m_seekEnemy(570,150,0, "SEEK"),
	m_fleeEnemy(570, 450,0,"FLEE"),
	m_wanderEnemy(570,300,0, "WANDER"),
	m_arriveEnemy(570,600,0,"ARRIVE")
{
	if (!m_font.loadFromFile("arial.ttf"))
	{

	}
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

	m_seekText.setFont(m_font);
	m_seekText.setCharacterSize(50);
	m_seekText.setFillColor(sf::Color::Red);
	m_seekText.setString("SEEK");
	m_seekText.setPosition(0, 0);

	m_wanderText.setFont(m_font);
	m_wanderText.setCharacterSize(50);
	m_wanderText.setFillColor(sf::Color::Blue);
	m_wanderText.setString("WANDER");
	m_wanderText.setPosition(0, 51);

	m_fleeText.setFont(m_font);
	m_fleeText.setCharacterSize(50);
	m_fleeText.setFillColor(sf::Color::Green);
	m_fleeText.setString("FLEE");
	m_fleeText.setPosition(0, 102);

	m_arriveText.setFont(m_font);
	m_arriveText.setCharacterSize(50);
	m_arriveText.setFillColor(sf::Color::Yellow);
	m_arriveText.setString("ARRIVE");
	m_arriveText.setPosition(0, 153);
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
	m_seekEnemy.update(m_player.getSprite());
	m_fleeEnemy.update(m_player.getSprite());
	m_wanderEnemy.update(m_player.getSprite());
	m_arriveEnemy.update(m_player.getSprite());
	m_player.update(); 

	checkBoundaries(m_seekEnemy.getSprite());
	checkBoundaries(m_fleeEnemy.getSprite());
	checkBoundaries(m_wanderEnemy.getSprite());
	checkBoundaries(m_arriveEnemy.getSprite());
	checkBoundaries(m_player.getSprite());	
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
	m_window.draw(m_seekText);
	m_window.draw(m_arriveText);
	m_window.draw(m_fleeText);
	m_window.draw(m_wanderText);

	m_player.render(m_window);
	m_seekEnemy.render(m_window);
	m_wanderEnemy.render(m_window);
	m_fleeEnemy.render(m_window);
	m_arriveEnemy.render(m_window);
	// Now display on-screen everthing that has been rendered to the SFML window.
	m_window.display();
}
