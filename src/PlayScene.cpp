#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include "LevelManager.h"


PlayScene::PlayScene()
{
	PlayScene::start();
	
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	LVLMAN::Instance()->render(m_bDebugMode);
	//std::cout << (SDL_GetTicks() / 1000) << "\n";
	drawDisplayList();
	if (m_bDebugMode) 
	{
		Util::DrawLine(m_pPlayer->getTransform()->position, m_pEnemy->getTransform()->position, {1,0,0,1});

		m_pPlayer->debugDraw();

		Util::DrawCircle(m_pEnemy->getTransform()->position, m_pEnemy->getRadius(), { 0,1,0,1 }, SYMMETRICAL);

	}
	for (auto node : m_pEnemy->getPath()) 
	{
		Util::DrawRect({ node->getTransform()->position.x - Config::TILE_SIZE * 0.5, node->getTransform()->position.y - Config::TILE_SIZE*0.5 }, Config::TILE_SIZE, Config::TILE_SIZE, { 0,1,0,1 });
	}
	
	m_pEnemyCounter->setText("Enemies Remaining: " + std::to_string(m_totalEnemies));
	m_pEnemyCounter->draw();
	m_pTimer->draw();
}

void PlayScene::update()
{
	//startTime = SDL_GetTicks();
	time = std::to_string((SDL_GetTicks() - startTime)/1000);
	for (auto i = 0; i < getList().size(); i++) 
	{
		int counter = 0;
		if (getList()[i]->getType() == ENEMY) 
		{
			counter++;
			m_totalEnemies = counter;
		}
	}
	updateDisplayList();
	m_pTimer->setText(time);
	CollisionManager::LOSCheck(m_pPlayer, m_pEnemy, LVLMAN::Instance()->getObstacles());
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	m_playerMoving = false;
	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				//m_pPlayer->setAnimationState(PLAYER_WALK_RIGHT);
				m_playerFacingRight = true;

				m_pPlayer->getRigidBody()->velocity = glm::vec2(3.0f, 0.0f);
				m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
				m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				//m_pPlayer->setAnimationState(PLAYER_WALK_LEFT);
				m_playerFacingRight = false;

				m_pPlayer->getRigidBody()->velocity = glm::vec2(-3.0f, 0.0f);
				m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
				m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
			}
			else
			{
				if (m_playerFacingRight)
				{
				//	m_pPlayer->setAnimationState(PLAYER_IDLE);
				}
				else
				{
					//m_pPlayer->setAnimationState(PLAYER_IDLE);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_playerFacingDown = false;
			m_playerMoving = true;
			m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -3.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			//m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_playerFacingDown = true;
			m_playerMoving = true;
			m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 3.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			//m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;

		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_playerFacingRight = false;
			m_playerMoving = true;
			m_pPlayer->getRigidBody()->velocity = glm::vec2(-3.0f, 0.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			//m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_playerFacingRight = true;
			m_playerMoving = true;
			m_pPlayer->getRigidBody()->velocity = glm::vec2(3.0f, 0.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			//m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else if(!m_playerMoving)
		{
			
			
			m_pPlayer->setAnimationState(PLAYER_IDLE);
			
		}

		if (EventManager::Instance().getMouseButton(0))
		{
			m_pPlayer->attack();
			//m_pPlayer->setAnimationState(PLAYER_ATTACK_RIGHT);
		}
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}



	if (!m_bDebugKeys[H_KEY])
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
		{
			m_bDebugMode = !m_bDebugMode;
			m_bDebugKeys[H_KEY] = true;
			if (m_bDebugMode)
			{
				std::cout << "Debug On\n";
			}
			else if(!m_bDebugMode)
			{
				std::cout << "Debug off\n";
			}
			
		}
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H)) 
	{
		m_bDebugKeys[H_KEY] = false;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P)) 
	{
		m_pEnemy->togglePatrol();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_B)) 
	{
		m_pPlayer->takeDamage(10);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	LVLMAN::Instance()->loadTiles("../Assets/sprites/Level1_Tiles.png", "tiles", "../Assets/sprites/TileData.txt");
	LVLMAN::Instance()->loadLevel("../Assets/data/Level1.txt");

	m_bDebugMode = false;
	// Plane Sprite
	

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	m_pEnemy = new BaseEnemy(m_pPlayer);
	addChild(m_pEnemy);

	// Obstacle Texture
	m_pObstacle = new Obstacle();
	addChild(m_pObstacle);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pEnemyCounter = new Label("Enemies Remaining: ", "Consolas", 40, white, glm::vec2(400.0f, 500.0f));
	
	m_pTimer = new Label("", "Consolas", 80, white, glm::vec2(400.0f, 40.0f));
	
}
