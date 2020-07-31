#pragma once
#ifndef __ENTITY__
#define __ENTITY__
#include "Sprite.h"
#include "PlayerAnimationState.h"
#include "HealthBar.h"
class Enity : public Sprite{ 
public:
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setAnimationState();
	void playAnimation();
	
	void attack();
	glm::vec2* getWeaponPos();
	int getWeaponWidth();
	int getWeaponHeight();

	void debugDraw();
protected:

	int m_health;
	int m_maxHealth;
	int m_damage;
	int m_speed;

	glm::vec2 m_weaponPos;
private:
	virtual void m_buildAnimation()
};

#endif /* defined (__ENTITY__) */
