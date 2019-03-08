#include "../inc/Game.h";
#include <stdlib.h>
/// <summary>
/// @author David Nolan
/// @date 
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
	m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)
{
	if (!m_font.loadFromFile("res/arial.TTF"))
	{
		std::cout << "could not load font" << std::endl;
	}
	m_threatLevel.setFont(m_font);
	m_threatLevel.setCharacterSize(24);
	m_threatLevel.setFillColor(sf::Color::Red);
	m_threatLevel.setPosition(650, 50);
	m_threatLevel.setString("Threat Level: ");

	m_axisDistance.setFont(m_font);
	m_axisDistance.setCharacterSize(24);
	m_axisDistance.setFillColor(sf::Color::Red);
	m_axisDistance.setPosition(650, 150);
	m_axisDistance.setString("Axis Distance: ");

	m_axisSize.setFont(m_font);
	m_axisSize.setCharacterSize(24);
	m_axisSize.setFillColor(sf::Color::Red);
	m_axisSize.setPosition(650, 250);
	m_axisSize.setString("Axis Size: ");

	m_allySize.setFont(m_font);
	m_allySize.setCharacterSize(24);
	m_allySize.setFillColor(sf::Color::Blue);
	m_allySize.setPosition(650, 350);
	m_allySize.setString("Ally Size: ");

	m_reset.setFont(m_font);
	m_reset.setCharacterSize(24);
	m_reset.setFillColor(sf::Color::Green);
	m_reset.setPosition(650, 600);
	m_reset.setString("Press R to reset");

	m_allies.push_back(new Resistance(sf::Vector2f(100, 450), sf::Vector2f(1, 1), 90));
	m_axis.push_back(new FirstOrder(sf::Vector2f(1340, 450), sf::Vector2f(1, 1), 270));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//clears vector
	//	m_axis.clear();
		//fuzzy variables
		int troopSize = rand() % 25 + 1;
		int troopDistance = rand() % 100 + 1;
		//fuzzification - get threat levels
		//troop size
		double mTiny = FuzzyLogic::fuzzyTriangle(troopSize, -10, 0, -10);
		double mSmall = FuzzyLogic::fuzzyTrapezoid(troopSize, 2.5, 10, 15, 20);
		double mModerate = FuzzyLogic::fuzzyTrapezoid(troopSize, 15, 20, 25, 30);
		double mLarge = FuzzyLogic::fuzzyGrade(troopSize, 25, 30);
		//troop distance 
		double mClose = FuzzyLogic::fuzzyTriangle(troopDistance, -30, 0, 30);
		double mMedium = FuzzyLogic::fuzzyTrapezoid(troopDistance, 10, 30, 50, 70);
		double mFar = FuzzyLogic::fuzzyGrade(troopDistance, 50, 70);
		//implementing the rules 
		double mLowT = FuzzyLogic::fuzzyOR(FuzzyLogic::fuzzyAND(mMedium, mTiny), FuzzyLogic::fuzzyAND(mMedium, mSmall));
		mLowT = FuzzyLogic::fuzzyOR(mLowT, FuzzyLogic::fuzzyAND(mFar, FuzzyLogic::fuzzyNOT(mLarge)));

		double mMediumT = FuzzyLogic::fuzzyOR(FuzzyLogic::fuzzyAND(mClose, mTiny),FuzzyLogic::fuzzyAND(mMedium,mModerate));
		mMediumT = FuzzyLogic::fuzzyOR(mMediumT, FuzzyLogic::fuzzyAND(mFar, mLarge));

		double mHighT = FuzzyLogic::fuzzyOR(FuzzyLogic::fuzzyAND(mClose, FuzzyLogic::fuzzyNOT(mMedium)), FuzzyLogic::fuzzyAND(mMedium, mLarge));

		//defuzzification
		int nDeploy = (mLowT * 10 + mMediumT * 30 + mHighT * 50) / (mLowT + mMediumT + mHighT);
		if (mLowT > mMediumT)
		{
			if (mLowT > mHighT)
			{
				std::string s = "Threat Level: LOW";
				m_threatLevel.setString(s);
			}
			else
			{
				std::string s = "Threat Level: HIGH";
				m_threatLevel.setString(s);
			}
		}
		else
		{
			if (mHighT > mMediumT)
			{
				std::string s = "Threat Level: HIGH";
				m_threatLevel.setString(s);
			}
			else
			{
				std::string s = "Threat Level: MEDIUM";
				m_threatLevel.setString(s);
			}
		}
		//updating strings
		std::string s = "Ally Size: " + std::to_string(nDeploy);
		m_allySize.setString(s);

		s = "Axis Size: " + std::to_string(troopSize);
		m_axisSize.setString(s);

		s = "Axis Distance: " + std::to_string(troopDistance);
		m_axisDistance.setString(s);
	}
	for (Resistance* ally : m_allies)
	{
		ally->update();
	}
	for (FirstOrder* axis : m_axis)
	{
		axis->update();
	}
}
/// <summary>
/// @brief draw the window for the game.
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_threatLevel);
	m_window.draw(m_axisDistance);
	m_window.draw(m_axisSize);
	m_window.draw(m_allySize);
	m_window.draw(m_reset);
	for (Resistance* ally : m_allies)
	{
		ally->draw(m_window);
	}
	for (FirstOrder* axis : m_axis)
	{
		axis->draw(m_window);
	}
	// Draw sprites etc. here using m_window.draw()...
	// Now display on-screen everthing that has been rendered to the SFML window.
	m_window.display();
}
