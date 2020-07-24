#include "Player.h"
#include "TextureManager.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/link.txt",
		"../Assets/sprites/link.png", 
		"link");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("link"));
	
	// set frame width
	setWidth(20);

	// set frame height
	setHeight(24);

	getTransform()->position = glm::vec2(600.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->maxSpeed = 10.0f;
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
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
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("link", getAnimation("idleRight"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("link", getAnimation("idleLeft"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_FRONT:
		TextureManager::Instance()->playAnimation("link", getAnimation("idleFront"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_BACK:
		TextureManager::Instance()->playAnimation("link", getAnimation("idleBack"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("link", getAnimation("runRight"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("link", getAnimation("runLeft"),
			x, y, 0.25f, 0, 255, true);
		break;	
	case PLAYER_RUN_FRONT:
		TextureManager::Instance()->playAnimation("link", getAnimation("runFront"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_BACK:
		TextureManager::Instance()->playAnimation("link", getAnimation("runBack"),
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}
	
}

void Player::update()
{
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state/*, int dir, bool moving*/)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{

	Animation idleRightAnimation = Animation();

	idleRightAnimation.name = "idleRight";
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-0"));
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-0"));
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-0"));
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-0"));

	setAnimation(idleRightAnimation);
	
	Animation idleLeftAnimation = Animation();

	idleLeftAnimation.name = "idleLeft";
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-0"));
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-0"));
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-0"));
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-0"));

	setAnimation(idleLeftAnimation);

	Animation idleFrontAnimation = Animation();

	idleFrontAnimation.name = "idleFront";
	idleFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-0"));
	idleFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-0"));
	idleFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-0"));
	idleFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-0"));

	setAnimation(idleFrontAnimation);	
	
	Animation idleBackAnimation = Animation();

	idleBackAnimation.name = "idleBack";
	idleBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-0"));
	idleBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-0"));
	idleBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-0"));
	idleBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-0"));

	setAnimation(idleBackAnimation);	
	
	

	Animation runRightAnimation = Animation();

	runRightAnimation.name = "runRight";
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-0"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-1"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-2"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-3"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-4"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-right-5"));

	setAnimation(runRightAnimation);	
	
	Animation runLeftAnimation = Animation();

	runLeftAnimation.name = "runLeft";
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-0"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-1"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-2"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-3"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-4"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-left-5"));

	setAnimation(runLeftAnimation);
	
	Animation runFrontAnimation = Animation();

	runFrontAnimation.name = "runFront";
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-0"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-1"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-2"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-3"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-4"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-5"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-6"));
	runFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-front-7"));

	setAnimation(runFrontAnimation);
	
	Animation runBackAnimation = Animation();

	runBackAnimation.name = "runBack";
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-0"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-1"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-2"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-3"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-4"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-5"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-6"));
	runBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-back-7"));

	setAnimation(runBackAnimation);

	Animation bowRightAnimation = Animation();

	bowRightAnimation.name = "bowLeft";
	bowRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowr-0"));
	bowRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowr-1"));
	bowRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowr-2"));

	setAnimation(bowRightAnimation);
	
	Animation bowLeftAnimation = Animation();

	bowLeftAnimation.name = "bowLeft";
	bowLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowl-0"));
	bowLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowl-1"));
	bowLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowl-2"));
	
	setAnimation(bowLeftAnimation);

	Animation bowFrontAnimation = Animation();

	bowFrontAnimation.name = "bowFront";
	bowFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowf-0"));
	bowFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowf-1"));
	bowFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowf-2"));

	setAnimation(bowFrontAnimation);

	Animation bowBackAnimation = Animation();

	bowBackAnimation.name = "bowBack";
	bowBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowb-0"));
	bowBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowb-1"));
	bowBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-bowb-2"));

	setAnimation(bowBackAnimation);

	Animation attackFrontAnimation = Animation();

	attackFrontAnimation.name = "attackFront";
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-0"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-1"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-2"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-3"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-4"));
	attackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackf-5"));

	setAnimation(attackFrontAnimation);

	Animation attackLeftAnimation = Animation();

	attackLeftAnimation.name = "attackLeft";
	attackLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackl-0"));
	attackLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackl-1"));
	attackLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackl-2"));
	attackLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackl-3"));
	attackLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackl-4"));

	setAnimation(attackLeftAnimation);

	Animation attackRightAnimation = Animation();

	attackRightAnimation.name = "attackRight";
	attackRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackr-0"));
	attackRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackr-1"));
	attackRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackr-2"));
	attackRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackr-3"));
	attackRightAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackr-4"));

	setAnimation(attackRightAnimation);

	Animation attackBackAnimation = Animation();

	attackBackAnimation.name = "attackBack";
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackb-0"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackb-1"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackb-2"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackb-3"));
	attackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("link-attackb-4"));

	setAnimation(attackBackAnimation);
	
}
