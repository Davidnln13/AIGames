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
	m_player(670,450,0),
	m_enemy(870,450,0)
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
	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
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
	m_text.setString("Score: " + std::to_string(m_score));
	
	m_enemy.Update();
	m_player.Update(); 

	checkBoundaries(m_enemy.getSprite());
	checkBoundaries(m_player.getSprite());
	checkCollisions(m_player.getSprite(), m_enemy.getSprite());	
}
void Game::checkCollisions(sf::Sprite &p, sf::Sprite &e)
{
	if (p.getGlobalBounds().intersects(e.getGlobalBounds()))
	{
		m_enemy.setOnce(false);
		srand((int)time(0));
		float posX = (rand()% 1440) + 1;
		float posY = (rand() % 900) + 1;
		m_enemy.getSprite().setPosition(posX, posY);
		m_score += 1;
	}
}
void Game::checkBoundaries(sf::Sprite &s)
{	
	if (s.getPosition().x < 0)
	{
		s.setPosition(m_window.getSize().x - 1, s.getPosition().y);
		m_enemy.setOnce(false);
	}
	if (s.getPosition().x > m_window.getSize().x)
	{
		s.setPosition(1, s.getPosition().y);
		m_enemy.setOnce(false);
	}
	if (s.getPosition().y < 0)
	{
		s.setPosition(s.getPosition().x, m_window.getSize().y - 1);
		m_enemy.setOnce(false);
	}
	if (s.getPosition().y > m_window.getSize().y)
	{
		s.setPosition(s.getPosition().x, 1);
		m_enemy.setOnce(false);
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
	m_player.Render(m_window);
	m_enemy.Render(m_window);
	m_window.draw(m_text);
	// Now display on-screen everthing that has been rendered to the SFML window.
	m_window.display();
}
