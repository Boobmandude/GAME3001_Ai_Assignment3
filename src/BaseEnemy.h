#pragma once
#ifndef _BASE_ENEMY_
#define _BASE_ENEMY_
#include "Sprite.h"
#include "SDL.h"
#include "Pathing.h"
#include "HealthBar.h"
#include "ActionStates.h"
class BaseEnemy : public Sprite
{
	
public:
	BaseEnemy(GameObject* target);
	~BaseEnemy();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void m_buildAnimations();
	void getNode();
	void buildClockwisPath();
	void m_displayPath();
	std::vector<PathNode*>& getPath();
	void moveToTarget();
	void setAngle(float angle);
	void togglePatrol();

	void checkRadiusDetection();
	int getRadius();

	void checkLOS();
private:
	bool m_patrolMode;
	int m_targetPathNodeIndex;
	PathNode* m_pTargetPathNode;
	std::vector<PathNode*> m_path;
	float m_angle;
	int m_detectionRadius;
	bool m_targetDetected;
	GameObject* m_pTarget;
	bool m_hasLOS;
	HealthBar* m_healthBar;
};

#endif // !_BASE_ENEMY_