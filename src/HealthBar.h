#pragma once
#ifndef _HEALTH_BAR_
#define _HEALTH_BAR_

#include "GameObject.h"
#include "SDL.h"
class HealthBar : public GameObject 
{
public:
	virtual void update();
	virtual void draw();
	virtual void clean();

	HealthBar(GameObject* obj);
	~HealthBar();

private:
	float m_life;
	GameObject* m_gameObject;
	float m_barSize;
};

#endif // !_HEALTH_BAR_
