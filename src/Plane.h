#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"
#include "Pathing.h"
class Plane final : public Sprite
{
public:
	Plane(GameObject* target);
	~Plane();

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
};

#endif /* defined (__PLANE__) */
