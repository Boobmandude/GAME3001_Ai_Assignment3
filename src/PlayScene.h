#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "BaseEnemy.h"
#include "Player.h"
#include "Button.h"
#include "Obstacle.h"
#include "DebugKeys.h"
#include "Label.h"
#include <sstream>
#include <string>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	glm::vec2 m_mousePosition;

	BaseEnemy* m_pEnemy;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	bool m_playerFacingDown;
	bool m_playerMoving;
	Obstacle* m_pObstacle;

	bool m_bDebugKeys[NUM_OF_DEBUG_KEYS];

	bool m_bDebugMode;
	bool m_bPatrolMode;

	Label* m_pTimer;
	Label* m_pEnemyCounter;
	int m_totalEnemies;

	Uint32 startTime;
	std::string time;
};

#endif /* defined (__PLAY_SCENE__) */