#include "Player.h"
#include "TextureManager.h"
#include "LevelManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "Util.h"
#include "MathManager.h"
Player::Player(): m_currentAnimationState(PLAYER_IDLE)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/char.txt",
		"../Assets/sprites/chara_hero.png", 
		"char");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("char"));
	
	// set frame width
	setWidth(32);

	// set frame height
	setHeight(32);

	getTransform()->position = glm::vec2(600.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->maxSpeed = 10.0f;
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	m_maxHealth = 100;
	m_health = m_maxHealth;
	m_damage = 20;
	m_buildAnimations();
	m_healthBar = new HealthBar(this);
	m_bAttack = false;
	m_swordWidth = 20;
	m_swordHeight = 32;
}

Player::~Player()
= default;

void Player::draw()
{

	playAnimation();
	m_healthBar->draw();
	
}

void Player::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
	m_swordCollision = getTransform()->position;
	checkLevelCollision(LVLMAN::Instance()->getObstacles());
	if(m_bAttack)
	{
		attack();
		playAnimation();
		m_bAttack = false;
	}
	else if (!m_bAttack) {
		if (getRigidBody()->velocity.x > 0)
		{
			setAnimationState(PLAYER_WALK_RIGHT);
			m_swordCollision = { getTransform()->position.x, getTransform()->position.y };
		}
		else if (getRigidBody()->velocity.x < 0)
		{
			setAnimationState(PLAYER_WALK_LEFT);
		}
		if (getRigidBody()->velocity.y > 0)
		{
			setAnimationState(PLAYER_WALK_FRONT);
		}
		else if (getRigidBody()->velocity.y < 0)
		{
			setAnimationState(PLAYER_WALK_BACK);
		}
	}
	//std::cout << "Player x " << getRigidBody()->velocity.x << " y " << getRigidBody()->velocity.y << "\n";
	playAnimation();
	m_healthBar->update();
	getRigidBody()->velocity = { 0.0f,0.0f };
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state/*, int dir, bool moving*/)
{
	m_currentAnimationState = new_state;
}

void Player::setDirection(ColDirections direction)
{
	m_facing = direction;
}

void Player::setAction(ActionStates action)
{
	m_currentAction = action;
}

void Player::attack()
{
	m_bAttack = true;
	glm::vec2 mousePos = EventManager::Instance().getMousePosition();
	glm::vec2 normal = Util::normalize(mousePos - getTransform()->position);
	//std::cout << normal.x <<"x y "<<normal.y << "\n";
	float angle = MAMA::AngleBetweenPoints(getTransform()->position, mousePos);
	std::cout << angle << "\n";
	if ( angle < 45 && angle > -45) 
	{
		setAnimationState(PLAYER_ATTACK_RIGHT);

	}
	else if ((angle < 180 && angle > 135 && angle > 0) || (angle > -180 && angle < -135 && angle < 0))
	{
		setAnimationState(PLAYER_ATTACK_LEFT);
	}
	else if (angle > -135 && angle < -45)
	{
		setAnimationState(PLAYER_ATTACK_BACK);
	}
	else if (angle > 45 && angle > 0 && angle < 135)
	{
		setAnimationState(PLAYER_ATTACK_FRONT);
	}


}

void Player::playAnimation()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_IDLE:
		TextureManager::Instance()->playAnimation("char", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_WALK_RIGHT:
		TextureManager::Instance()->playAnimation("char", getAnimation("walk"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_WALK_LEFT:
		TextureManager::Instance()->playAnimation("char", getAnimation("walk"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_WALK_FRONT:
		TextureManager::Instance()->playAnimation("char", getAnimation("walkFront"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_WALK_BACK:
		TextureManager::Instance()->playAnimation("char", getAnimation("walkBack"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_ATTACK_RIGHT:
		TextureManager::Instance()->playAnimation("char", getAnimation("attack"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_ATTACK_LEFT:
		TextureManager::Instance()->playAnimation("char", getAnimation("attack"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ATTACK_FRONT:
		TextureManager::Instance()->playAnimation("char", getAnimation("attackFront"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_ATTACK_BACK:
		TextureManager::Instance()->playAnimation("char", getAnimation("attackBack"),
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}
}

glm::vec2 Player::getWeaponPos()
{
	return m_swordCollision;
}

int Player::getSwordHeight()
{
	return m_swordHeight;
}

int Player::getSwordWidth()
{
	return m_swordWidth;
}

void Player::debugDraw()
{
	Util::DrawRect(getTransform()->position - glm::vec2(getWidth() * 0.5f,getHeight() * 0.5f), getWidth(),getHeight(), { 0,1,0,1 });

	
	switch (m_currentAnimationState)
	{

	case PLAYER_ATTACK_RIGHT:
		Util::DrawRect((getWeaponPos() + glm::vec2{ 8,-16 }), getSwordWidth(), getSwordHeight(), { 0,1,0,1 });
		break;
	case PLAYER_ATTACK_LEFT:
		Util::DrawRect((getWeaponPos() - glm::vec2{ 30,16 }), getSwordWidth(), getSwordHeight(), { 0,1,0,1 });
		break;
	case PLAYER_ATTACK_FRONT:
		Util::DrawRect((getWeaponPos() + glm::vec2{ -16,8 }), getSwordHeight(), getSwordWidth(), { 0,1,0,1 });
		break;
	case PLAYER_ATTACK_BACK:
		Util::DrawRect((getWeaponPos() - glm::vec2{ 16,30 }), getSwordHeight(), getSwordWidth(), { 0,1,0,1 });
		break;
	default:
		break;
	}
}

void Player::m_buildAnimations()
{

	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("char-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("char-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("char-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("char-idle-1"));

	setAnimation(idleAnimation);
		
	Animation walkAnimation = Animation();

	walkAnimation.name = "walk";
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("char-walk-0"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("char-walk-1"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("char-walk-2"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("char-walk-3"));

	setAnimation(walkAnimation);	
	
	Animation walkFrontAnimation = Animation();

	walkFrontAnimation.name = "walkFront";
	walkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-front-0"));
	walkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-front-1"));
	walkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-front-2"));
	walkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-front-3"));


	setAnimation(walkFrontAnimation);
	
	Animation walkBackAnimation = Animation();

	walkBackAnimation.name = "walkBack";
	walkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-back-0"));
	walkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-back-1"));
	walkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-back-2"));
	walkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-back-3"));


	setAnimation(walkBackAnimation);

	Animation rangeReadyAnimation = Animation();

	rangeReadyAnimation.name = "rangeReady";
	rangeReadyAnimation.frames.push_back(getSpriteSheet()->getFrame("char-rangeready-0"));
	rangeReadyAnimation.frames.push_back(getSpriteSheet()->getFrame("char-rangeready-1"));


	setAnimation(rangeReadyAnimation);
	
	Animation rangeAnimation = Animation();

	rangeAnimation.name = "range";
	rangeAnimation.frames.push_back(getSpriteSheet()->getFrame("char-range-0"));
	rangeAnimation.frames.push_back(getSpriteSheet()->getFrame("char-range-1"));

	
	setAnimation(rangeAnimation);

	Animation rangeUpAnimation = Animation();

	rangeUpAnimation.name = "rangeUp";
	rangeUpAnimation.frames.push_back(getSpriteSheet()->getFrame("char-rangeu-0"));
	rangeUpAnimation.frames.push_back(getSpriteSheet()->getFrame("char-rangeu-1"));

	setAnimation(rangeUpAnimation);

	Animation rangeDownAnimation = Animation();

	rangeDownAnimation.name = "rangeDown";
	rangeDownAnimation.frames.push_back(getSpriteSheet()->getFrame("char-ranged-0"));
	rangeDownAnimation.frames.push_back(getSpriteSheet()->getFrame("char-ranged-1"));


	setAnimation(rangeDownAnimation);

	Animation attackFrontAnimation = Animation();

	attackFrontAnimation.name = "attackFront";
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackf-0"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackf-1"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackf-2"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackf-3"));

	setAnimation(attackFrontAnimation);

	Animation attackAnimation = Animation();

	attackAnimation.name = "attack";
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attack-0"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attack-1"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attack-2"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attack-3"));


	setAnimation(attackAnimation);

	Animation attackBackAnimation = Animation();

	attackBackAnimation.name = "attackBack";
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackb-0"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackb-1"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackb-2"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("char-attackb-3"));

	setAnimation(attackBackAnimation);
	
	Animation hitAnimation = Animation();

	hitAnimation.name = "hit";
	hitAnimation.frames.push_back(getSpriteSheet()->getFrame("char-hit-0"));
	hitAnimation.frames.push_back(getSpriteSheet()->getFrame("char-hit-1"));
	hitAnimation.frames.push_back(getSpriteSheet()->getFrame("char-hit-2"));
	hitAnimation.frames.push_back(getSpriteSheet()->getFrame("char-hit-3"));

	setAnimation(hitAnimation);	
	
	Animation deadAnimation = Animation();

	deadAnimation.name = "dead";
	deadAnimation.frames.push_back(getSpriteSheet()->getFrame("char-dead-0"));
	deadAnimation.frames.push_back(getSpriteSheet()->getFrame("char-dead-1"));
	deadAnimation.frames.push_back(getSpriteSheet()->getFrame("char-dead-2"));

	setAnimation(deadAnimation);
}
