#pragma once
#ifndef _PATHING_
#define _PATHING_
#include <SDL.h>
#include <vector>

class PathNode : public SDL_Point
{

private:
	double m_cost;
	bool m_openNode;

public:
	PathNode(int x, int y);
	~PathNode();

	void update();

	SDL_Point getPt() { return { x,y }; }
	double getCost() { return m_cost; }
	void setCost(double cost) { m_cost = cost; }
	void toggleNode() { m_openNode = !m_openNode; }
	bool isOpen() { return m_openNode; }
};

#endif // !_PATHING_
