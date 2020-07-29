#include "LevelManager.h"
#include "TextureManager.h"
//#include "MathManager.h"
#include "Util.h"
#include "PlayScene.h"
#include <fstream>

LevelManager* LevelManager::s_pInstance = nullptr;

LevelManager::LevelManager() = default;
LevelManager::~LevelManager() = default;


void LevelManager::update(float scroll, bool x)
{

	for (auto i : m_obstacles)
	{
		/*if (i->getType() == DESTRUCTIBLE)
		{
			i->update();

		}*/

	}
	//for (int row = 0; row < Config::ROW_NUM; row++)
	//{
	//	for (int col = 0; col < Config::COL_NUM; col++)
	//	{
	//		if (x)
	//		{
	//			m_level[row][col]->getTransform()->position.x += scroll;
	//		}
	//		else
	//		{
	//			m_level[row][col]->getTransform()->position.y += scroll;
	//		}
	//	}
	//}
	//if (x) 
	//{
	//	m_sumDX += scroll;
	//}
	//else
	//{
	//	m_sumDY += scroll;
	//}
}

void LevelManager::clean()
{
	//Cleaning as Alex would say "Wrangle your Dangle"
	clearLevel();
	clearTiles();
}

void LevelManager::render(bool debug)
{
	//Draw out the tiles
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			m_level[row][col]->draw();

			if (debug)
			{
				if (m_level[row][col]->m_node->isOpen())
				{
					Util::DrawRect({ m_level[row][col]->getPosX(), m_level[row][col]->getPosY() }, m_level[row][col]->getWidth(), m_level[row][col]->getHeight(), { 0.0f,0.0f,1.0f,1.0f });
				}
				else
				{
					Util::DrawRect({ m_level[row][col]->getPosX(), m_level[row][col]->getPosY() }, m_level[row][col]->getWidth(), m_level[row][col]->getHeight(), { 1.0f,0.0f,0.0f,1.0f });
				}
			}
		}
	}

	//for (auto i : m_obstacles)
	//{
	//	if (i->getType() == TILE)
	//	{
	//		i->draw();

	//	}
	//	if (debug)
	//	{
	//		if (i->getType() == TILE)
	//		{
	//			Util::DrawRect({ i->getPosX() /*- i->getWidth()*/, i->getPosY() /*- i->getHeight() */ }, i->getWidth() - 10, i->getHeight() - 10, { 1.0f,1.0f,1.0f,1.0f });
	//		}
	//		else {
	//			Util::DrawRect({ i->getPosX(), i->getPosY() }, i->getWidth(), i->getHeight(), { 1.0f,1.0f,1.0f,1.0f });
	//		}
	//	}
	//}


}

void LevelManager::loadTiles(std::string spritePath, std::string texture_Name, std::string tileDataPath)
{

	TextureManager::Instance()->load(spritePath, texture_Name);
	std::ifstream inFile(tileDataPath);
	if (inFile.is_open())
	{
		//create map of Tile Prototypes(what we copy to make the level)
		char key;
		int x, y;
		bool o, h;

		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> o >> h;
			std::cout << "tile x " << x << " tile y " << y << "\n";
			m_tiles.emplace(key, new Tile("tiles", x, y, o, h));
		}

	}
	inFile.close();
}

void LevelManager::loadLevel(std::string levelDataPath) //Passes the scene display list to add obstacles and hazard tiles
{
	std::ifstream inFile(levelDataPath);
	if (inFile.is_open())
	{
		//build level from tiles
		char key;
		for (int row = 0; row < Config::ROW_NUM; row++)
		{
			for (int col = 0; col < Config::COL_NUM; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone();
				m_level[row][col]->getTransform()->position.x = (int)(col * Config::TILE_SIZE);
				m_level[row][col]->getTransform()->position.y = (int)(row * Config::TILE_SIZE);

				m_level[row][col]->m_node = new PathNode((int)(m_level[row][col]->getTransform()->position.x + 16), (int)(m_level[row][col]->getTransform()->position.y + 16));

				m_level[row][col]->setPosX(m_level[row][col]->getTransform()->position.x);
				m_level[row][col]->setPosY(m_level[row][col]->getTransform()->position.y);
				if (m_level[row][col]->getX() == 4 && m_level[row][col]->getY() == 1) //if the index nums match up to where the door tile is on the texture make the tile a door game object
				{
					//m_level[row][col]->setType(SPIKES);
				}
				if (m_level[row][col]->isObstacle()) 
				{
					m_level[row][col]->setType(OBSTACLE);
				}
				if (m_level[row][col]->isObstacle() || m_level[row][col]->isHazard()) //If tile is an obstacle add it to the obstacle list
				{
					
					m_obstacles.push_back(m_level[row][col]);
					m_level[row][col]->m_node->toggleNode();
				}
				m_levelNodes.push_back(m_level[row][col]->m_node);
			}
		}
	}
	inFile.close();

}


void LevelManager::clearTiles()
{
	for (int t = 0; t < m_tiles.size(); t++)
	{
		delete m_tiles[t];
		m_tiles[t] = nullptr;
	}
	m_tiles.clear();
}

void LevelManager::clearLevel()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			delete m_level[row][col];
			m_level[row][col] = nullptr;
		}
	}
	m_obstacles.clear();
}

void LevelManager::printNodes()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			if (m_level[row][col]->m_node != nullptr)
			{
				//std::cout << "Node at x: " << m_level[row][col]->m_node->x << " y: " << m_level[row][col]->m_node->y << "\n";
			}

		}
	}
}

std::vector<PathNode*>& LevelManager::getLevelNodes()
{
	return m_levelNodes;
}
