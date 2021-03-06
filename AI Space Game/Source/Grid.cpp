#include "Grid.h"

Grid::Grid() :
	m_cellSize(160, 160)
{
	//Load our Text font
	m_font.loadFromFile("./Resources/ArialB.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setFillColor(sf::Color::White);

	//Setup rectangle Shape
	m_rectangle.setSize(sf::Vector2f(m_cellSize.x, m_cellSize.y));
	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineColor(sf::Color::White);
	m_rectangle.setOutlineThickness(5.0f);
	m_rectangle.setOrigin(80, 80); //Center rectangle

	std::string name; //For grid naming

	//Setup the split grid cells
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			name = std::to_string(j) + "," + std::to_string(i);
			auto gPos = sf::Vector2i(j, i);
			auto c = Cell(Vector2f((j * 2880) + 1440, (i * 1620) + 810), gPos);
			c.setRectangle(2880, 1620);
			c.addSplitGridPosition(j, i);
			m_splitGridcells[name] = c;
		}
	}

	//Create Every cell in the map
	for (int i = 0; i < 41; i++) //Rows
	{

		for (int j = 0; j < 72; j++) //Columns
		{
			name = std::to_string(j) + "," + std::to_string(i);
			auto gPos = sf::Vector2i(j, i);
			auto c = Cell(Vector2f((j * 160) + 80, (i * 160) + 80), gPos);
			c.setRectangle(160, 160);

			//If the new cell intersects with any of the split grid positions, add them to the new cells split grid vector
			//This vetcor will be useful for pathfinding as we will not have to traverse the entire grid looking for the correct grid position
			//And we can limit searches to only a portion of the grid rather than all of it
			for (auto& cell : m_splitGridcells)
			{
				if (cell.second.rect.intersects(c.rect))
				{
					c.addSplitGridPosition(cell.second.splitGridPos.at(0));
				}
			}
			m_cells[name] = c; //Create the cell and add it to the map
			m_cellsPtrs.push_back(&m_cells[name]); //Add it to our pointers
		}
	}

	//Add to our split cells
	for (auto& cell : m_splitGridcells)
	{
		//Loop through every small cell
		for (auto& smallCell : m_cells)
		{
			name = std::to_string(cell.second.gridPosition.x) + "," + std::to_string(cell.second.gridPosition.y);
			//If the Cells intersect, add the small cell to the Big Grid Split variable
			if (cell.second.rect.intersects(smallCell.second.rect))
			{
				m_splitCells[name].push_back(&smallCell.second);
			}
		}
	}
}

/**
* Description: Here we pathfind and get a path from a cell to another and return it
*/
std::vector<Vector2f> Grid::BFS(Cell & from, Cell & goal, std::vector<Cell*>& cells)
{
	m_bfsQueue.clear(); //Clear the queue
	//Reset tiles
	for (auto& tile : cells)
	{
		if (tile->isWall == false)
		{
			tile->visited = false;
			tile->cost = 0;
			tile->previous = nullptr;
		}
	}

	from.visited = true; //Set start cell as visited
	m_bfsQueue.push_back(&from); //Add start cell to the queue

	while (!m_bfsQueue.empty() && m_bfsQueue.front() != &goal) //Loop while we have not found the goal and the queue is not empty
	{

		auto gPos = m_bfsQueue.front()->gridPosition; //Get the integer values of the grid position
		auto cPos = gPos;
		auto originalCost = m_bfsQueue.front()->cost; //Get the cost from the previous tile

		//Generate the positions for all adjacent tiles
		std::vector<sf::Vector2i> adj = {
			sf::Vector2i(cPos.x - 1, cPos.y),
			sf::Vector2i(cPos.x + 1, cPos.y),
			sf::Vector2i(cPos.x, cPos.y - 1),
			sf::Vector2i(cPos.x, cPos.y + 1)
		};

		//Loop through all possible adjacent cells
		for (auto& val : adj)
		{
			if (val.x >= 0 && val.x < 72 && val.y >= 0 && val.y < 41)
			{
				auto gridS = convertToString(val); //Convert it to a grid position in string

				//If this cell is not visited and its not a wall, add it to the queue
				if (!m_cells[gridS].isWall && !m_cells[gridS].visited)
				{
					m_cells[gridS].visited = true; //Set visited to true
					m_cells[gridS].cost = originalCost + 1; //Add to the cost
					m_bfsQueue.push_back(&m_cells[gridS]); //Add it to the queue to expand neighbours
					m_cells[gridS].previous = m_bfsQueue.front(); //Set previous Ptr
				}
			}
		}

		m_bfsQueue.pop_front(); //Pop at the end
	}

	std::vector<Vector2f> path;
	Cell* prev = &goal;

	path.push_back(prev->position);
	prev = prev->previous;

	while (nullptr != prev && prev != &from)
	{
		path.push_back(prev->position);
		prev = prev->previous;
	}

	std::reverse(path.begin(), path.end());

	return path; //Return the path
}

/**
* Description: draws the cells in the game
*/
void Grid::draw(sf::RenderWindow & window)
{
	//Loop through the cells
	for (auto& cell : m_cells)
	{
		//Only draw if the cell isnt a wall
		if (cell.second.isWall == false)
		{
			m_rectangle.setPosition(cell.second.position.x, cell.second.position.y);
			window.draw(m_rectangle);
			m_text.setString(std::to_string((cell.second.gridPosition.x)) + "," + std::to_string((cell.second.gridPosition.y)));
			m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2 - 10);
			m_text.setPosition(cell.second.position.x, cell.second.position.y);
			window.draw(m_text);
		}
	}
}

std::string Grid::convertToString(sf::Vector2i pos)
{
	return std::to_string(pos.x) + "," + std::to_string(pos.y);
}

std::string Grid::convertToString(int x, int y)
{
	return std::to_string(x) + "," + std::to_string(y);
}