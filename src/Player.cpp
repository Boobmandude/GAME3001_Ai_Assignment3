#include "Player.h"
#include "TextureManager.h"
#include "LevelManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "Util.h"
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
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	
	// draw the player according to animation state
	switch(m_currentAnimationState)
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
			x, y, 0.25f, 0, 255, true,SDL_FLIP_HORIZONTAL);	
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

	m_healthBar->draw();
	
}

void Player::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
	checkLevelCollision(LVLMAN::Instance()->getObstacles());
	m_healthBar->update();
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
	glm::vec2 mousePos = EventManager::Instance().getMousePosition();
	glm::vec2 normal = Util::normalize(mousePos - getTransform()->position);
	std::cout << normal.x <<"x y "<<normal.y << "\n";
	if (mousePos.x > getTransform()->position.x) 
	{
		setAnimationState(PLAYER_ATTACK_RIGHT);
	}
	else if (mousePos.x < getTransform()->position.x) 
	{
		setAnimationState(PLAYER_ATTACK_LEFT);
	}	
	
	if (mousePos.y > getTransform()->position.y) 
	{
		setAnimationState(PLAYER_ATTACK_FRONT);
	}
	else if (mousePos.y < getTransform()->position.y) 
	{
		setAnimationState(PLAYER_ATTACK_BACK);
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
