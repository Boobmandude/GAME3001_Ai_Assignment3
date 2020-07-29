#pragma once
#ifndef _PATHING_
#define _PATHING_
#include <SDL.h>
#include <vector>
#include "GameObject.h"
class PathNode : public GameObject
{

private:
	double m_cost;
	bool m_openNode;

public:
	PathNode(float x, float y);
	~PathNode();

	virtual void update()override;
	virtual void clean()override;
	virtual void draw()override;
	double getCost() { return m_cost; }
	void setCost(double cost) { m_cost = cost; }
	void toggleNode() { m_openNode = !m_openNode; }
	bool isOpen() { return m_openNode; }
};

#endif // !_PATHING_
