#pragma once
#ifndef _BASE_ENEMY_
#define _BASE_ENEMY_
#include "DisplayObject.h"
#include "SDL.h"
class BaseEnemy : public DisplayObject
{

private:

	int m_health;
	int m_speed;
	int m_dectRadius;

	bool m_bhasLOS;
	bool m_binRange;



public:
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	void takeDamage();
	void getNode();

};

#endif // !_BASE_ENEMY_