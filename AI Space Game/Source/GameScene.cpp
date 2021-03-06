#include "GameScene.h"

GameScene::GameScene() :
	//player pointer maxSpeed and position
	m_player(5840, 6163),
	m_hud(m_player, m_grid) //Our hud (minimap, health, workers collected)
{
	m_followView.setSize(sf::Vector2f(1280, 720));
	m_followView.zoom(1.0f);


	
	//Setup our BG colliders
	for (int i = 0; i < 5; i++) //5 rows
	{
		for (int j = 0; j < 5; j++) //5 Columns
		{
			m_bgColliders.push_back(sf::FloatRect(-3840 + (j * 3840), -2160 + (i * 2160), 3840, 2160));
		}
	}

	//Can have 4 predators alive at once, we create them here and then spawn/kill
	//Make it  more efficient than deleting and creating 
	for (int i = 0; i < 4; i++)
	{
		m_predatorAI.push_back(Predator(m_player.m_position, &m_grid, i));
	}

	loadMap();
}

GameScene::~GameScene()
{
}

void GameScene::loadMap()
{
	//Loop through the map pieces and create our environment (rooms, corridors)
	for (auto& piece : m_levelLoader.data["Map Pieces"])
	{
		auto env = Environment(piece["X"], piece["Y"], piece["Tag"]);
		env.setRotation(piece["Angle"]); //Set the angle
		env.setScale(piece["Scale"][0], piece["Scale"][1]);
		//Create the environment and add it to our vector
		m_mapPieces.push_back(env);
	}

	//Load our doors
	for (auto& door : m_levelLoader.data["Doors"])
	{
		auto d = Door(door["X"], door["Y"], m_player);
		d.setRotation(door["Angle"]);
		m_doors.push_back(d);
	}

	int workers = 0;
	//Load worker Areas
	for (auto& area : m_levelLoader.data["Worker Areas"])
	{
		auto env = Environment(area["X"], area["Y"], "Worker Area");
		m_environment.push_back(env);
		m_workerAI.push_back(Worker(Vector2f(area["X"], area["Y"]), &m_grid));
		workers++;
	}
	for (auto& sweeper : m_levelLoader.data["Sweepers"])
	{
		m_sweeperAI.push_back(Sweeper(m_player.m_position, &m_grid, Vector2f(sweeper["X"], sweeper["Y"]), &m_workerAI));
	}


	m_hud.setMaxWorkers(workers);

	//Create our nests
	for (auto& nest : m_levelLoader.data["Nests"])
	{
		Vector2f pos = Vector2f(nest["X"], nest["Y"]);
		m_nests.push_back(Nest(m_player, m_grid, pos, m_predatorAI));
	}

	//Load our spawn point
	for (auto& spawn : m_levelLoader.data["Spawn Point"])
	{
		m_environment.push_back(Environment(spawn["X"], spawn["Y"], "Spawn Point"));
	}
}

void GameScene::createBoundary(json bounds, Environment & object)
{
	//Loop through the bounds and look for the boundaries tagged with objects tag
	for (auto& bound : bounds[object.tag]["Walls"])
	{
		auto body = new PhysicsBody(Type::Static, Shape::Box, this); //Create the body
		auto size = Vector2f(bound["W"], bound["H"]);
		auto pos = Vector2f(bound["X"], bound["Y"]); //Center the physics body
		pos.x += object.m_position.x;
		pos.y += object.m_position.y;
		if (object.angle != 0)
		{
			sf::Transform tf;//Rotate position around the center of the objects position
			tf.rotate(object.angle, sf::Vector2f(object.m_position.x, object.m_position.y));
			auto posAfter = tf.transformPoint(sf::Vector2f(pos.x, pos.y));
			pos = Vector2f(posAfter.x, posAfter.y);
		}
		body->setBoxParameters(pos, size, 0, false); //Set the parameters of the body
		body->setInitialRotation(object.angle); //Set the initial rotation of the body
		physics::world->addPhysicsBody(*body); //Add body to the physics simulation
	}

	//Loop through the safe Areas for the object
	for (auto& bound : bounds[object.tag]["Safe Areas"])
	{
		auto size = Vector2f(bound["W"], bound["H"]);
		auto pos = Vector2f(bound["X"], bound["Y"]); //Center of the collision box
		pos.x += object.m_position.x;
		pos.y += object.m_position.y;
		CollisionBox safeArea(pos.x, pos.y, size.x, size.y); //Create the collision box

		if (object.angle != 0) //If the object is rotated, rotate our collision box
		{
			sf::Transform tf;//Rotate position around the center of the objects position
			tf.rotate(object.angle, sf::Vector2f(object.m_position.x, object.m_position.y));
			auto posAfter = tf.transformPoint(sf::Vector2f(pos.x, pos.y));
			pos = Vector2f(posAfter.x, posAfter.y); //Set the new position
			safeArea.setSize(pos.x, pos.y, size.x, size.y);
			safeArea.rotate(object.angle);
		}

		//Loop through all of the Big Cells and see where our object is
		for (auto& cells :	m_grid.m_splitGridcells)
		{
			//If the Safe Area intersects with with the grid, go mark the cells it collides with as not a wall
			if (safeArea.rect.getGlobalBounds().intersects(cells.second.rect))
			{
				std::string gridP = std::to_string(cells.second.gridPosition.x) + "," + std::to_string(cells.second.gridPosition.y);

				for (auto& smallCell : m_grid.m_splitCells[gridP])
				{
					if (smallCell->rect.intersects(safeArea.rect.getGlobalBounds()))
					{
						smallCell->isWall = false;
					}
				}
			}
		}
	}
}


void GameScene::update(double dt)
{
	//Update the doors on the map
	for (auto& object : m_doors)
	{
		object.update(dt);
	}

	//Set the views position to follow the player (player will be centered)
	m_followView.setCenter(m_player.m_position.x, m_player.m_position.y);
	m_viewRect = sf::FloatRect(m_player.m_position.x - 640, m_player.m_position.y - 360, 1280, 720);

	//Update minimap
	m_hud.update(dt);

	//Update nests
	for (auto& nest : m_nests)
	{
		nest.update(dt, m_nests);
	}

	//Update predators
	for (auto& pred : m_predatorAI)
	{
		pred.flock(&m_predatorAI, pred.m_id);
		pred.update(dt);
	}

	//Update Player
	m_player.update(dt);

	//Update workers
	for (auto& worker : m_workerAI)
	{
		worker.update(dt);

		//If the circles collide (worker and player) pick them up
		if (Collisions::CircleVsCircle(worker.rangeCollider(), m_player.m_rangeCollider))
		{
			//If the worker is not currently captured by a sweeper bot, set it as captured by the player
			if (!worker.captured())
			{
				worker.captureWorker(true, m_player.m_position);
				m_player.workersCollected++; //Add to the workers collected
				m_player.addDelHealth(25); //Add health to the player
			}
		}
	}
	//Update sweeper bots
	for (auto& sweep : m_sweeperAI)
	{
		sweep.update(dt);
	}
	//Remove player captured workers from the vector
	m_workerAI.erase(std::remove_if(m_workerAI.begin(), m_workerAI.end(), removeCapturedWorker()), m_workerAI.end());


}

void GameScene::draw(sf::RenderWindow & window, float a)
{
	//Set the windows view
	window.setView(m_followView);

	//Draw our bg sprite, everything else will be drawn over this
	for (auto& bg : m_bgColliders)
	{
		if (bg.intersects(m_viewRect))
		{
			m_bgSprite.setPosition(bg.left, bg.top);
			window.draw(m_bgSprite);
		}
	}

	//Draw the map
	window.draw(m_fullMapSprite);

	//Draw our Doors
	for (auto& object : m_doors)
	{
		//If the object is in view, then draw it
		if (object.collider().intersects(m_viewRect))
		{
			object.draw(window);
		}
	}

	//Draw environment
	for (auto& object : m_environment)
	{
		//If the object is in view, then draw it
		if (object.collider().intersects(m_viewRect))
		{
			object.draw(window);
		}
	}

	//Draw workers
	for (auto& worker : m_workerAI)
	{
		if(worker.collider().intersects(m_viewRect))
			worker.draw(window);
	}

	//Draw nests
	for (auto& nest : m_nests)
	{
		if(nest.collider().intersects(m_viewRect))
			nest.draw(window);
	}

	//Draw predators
	for (auto& pred : m_predatorAI)
	{
		pred.draw(window);
	}

	//Draw predators
	for (auto& sweep : m_sweeperAI)
	{
		sweep.render(window);
	}

	//Draw the player
	m_player.draw(window, a);


	//The Grid
	if(m_drawGrid)
		m_grid.draw(window);

	//Draw our physics colliders for debugging
	if (m_drawPhysics)
		physics::world->draw(window);

	drawMinimap(window); //Draw the mini map
}

void GameScene::drawMinimap(sf::RenderWindow & window)
{
	m_hud.draw(m_fullMapSprite);

	//Draw environment
	for (auto& object : m_environment)
	{
		//If the object is in view, then draw it
		if (object.collider().intersects(m_hud.getViewDetector()))
		{
			m_hud.draw(object.m_sprite);
		}
	}

	m_hud.draw(m_player.m_sprite);
	m_hud.display(window);
}

void GameScene::handleInput(InputHandler & input)
{
	m_player.handleInput(input);

	m_hud.handleInput(input);

	//Keybindings for turning Grid and Collision boxes On/OFF
	if (input.isButtonPressed("Shift"))
		m_drawGrid = !m_drawGrid;
	if (input.isButtonPressed("Tab"))
		m_drawPhysics = !m_drawPhysics;
}

void GameScene::setTexture(ResourceManager & resources)
{	
	m_player.setAudioRef(resources);
	resources.playAudio("GameMusic", "Music", true);

	m_player.setTexture(resources);

	m_bgSprite.setTexture(resources.getTexture("Starfield BG"));

	for (auto& object : m_doors)
	{
		object.setTexture(resources);
	}

	m_fullMapSprite.setTexture(resources.getTexture("Full Map"));

	//Get the boundaries information from the Json data
	json bounds = m_levelLoader.data["Boundaries"];

	//Set our environment textures
	for (auto& object : m_environment)
	{
		//Set the texture of the object
		object.setTexture(resources, object.tag);
	}

	//Set our map piece textures and create our Boundaries for each piece
	for (auto& object : m_mapPieces)
	{
		//Set the texture of the object
		object.setTexture(resources, object.tag);

		//Create the boundaries for the object
		createBoundary(bounds, object);
	}

	//Set workers textures
	for (auto& worker : m_workerAI)
	{
		worker.setTexture(resources);
	}

	//Set texture for predators
	for (auto& pred : m_predatorAI)
	{
		pred.setTexture(resources);
	}


	//Set textures for the nests
	for (auto& nest : m_nests)
	{
		nest.setTexture(resources);
	}

	m_hud.setTexture(resources);

	//Set texture for sweepers
	for (auto& sweep : m_sweeperAI)
	{
		sweep.setTexture(resources);
	}

}
