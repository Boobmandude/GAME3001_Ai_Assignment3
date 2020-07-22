#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;



	// setters
	void setAnimationState(PlayerAnimationState new_state/*, int dir, bool moving*/);
	void takeDamage(int damage);
	int getHealth() { return m_iCurrHealth; }

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;

	int m_iMaxHealth;
	int m_iCurrHealth;

};

#endif /* defined (__PLAYER__) */