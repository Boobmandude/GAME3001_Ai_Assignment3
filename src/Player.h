#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"
#include "HealthBar.h"
#include "Directions.h"
#include "ActionStates.h"
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
	void setDirection(ColDirections direction);
	void setAction(ActionStates action);
	void attack();
	//int& getHealth();

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	ActionStates m_currentAction;
	HealthBar* m_healthBar;
	ColDirections m_facing;
	ColDirections m_attackDir;
	glm::vec2 m_mousePos;
};

#endif /* defined (__PLAYER__) */