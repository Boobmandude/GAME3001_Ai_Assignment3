#include "BaseEnemy.h"
#include "TextureManager.h"
#include "LevelManager.h"
#include "Util.h"
#include "CollisionManager.h"
BaseEnemy::BaseEnemy(GameObject* target)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/orc.txt",
		"../Assets/sprites/chara_orc.png",
		"orc");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("orc"));

	// set frame width
	setWidth(32);

	// set frame height
	setHeight(32);
	buildClockwisPath();
	getTransform()->position = m_path[0]->getTransform()->position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->maxSpeed = 5.0f;
	setType(ENEMY);
	m_detectionRadius = 100;
	m_targetDetected = false;
	m_buildAnimations();
	m_targetPathNodeIndex = 1;
	m_patrolMode = false;
	m_pTarget = target;
	m_hasLOS = false;
	m_maxHealth = 100;
	m_health = m_maxHealth;
	m_healthBar = new HealthBar(this);
}

BaseEnemy::~BaseEnemy()
= default;

void BaseEnemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation("orc", getAnimation("walk"),x, y, 0.5f, m_angle, 255, true);
	m_healthBar->draw();
}

void BaseEnemy::update()
{
	/*setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);*/
	checkRadiusDetection();
	moveToTarget();
	m_healthBar->update();
}

void BaseEnemy::clean()
{
}

void BaseEnemy::m_buildAnimations()
{
	Animation orcIdleAnimation = Animation();

	orcIdleAnimation.name = "idle";
	orcIdleAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-idle-0"));
	orcIdleAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-idle-1"));
	orcIdleAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-idle-2"));
	orcIdleAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-idle-1"));

	setAnimation(orcIdleAnimation);

	Animation orcWalkAnimation = Animation();

	orcWalkAnimation.name = "walk";
	orcWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-walk-0"));
	orcWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-walk-1"));
	orcWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-walk-2"));
	orcWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-walk-3"));

	setAnimation(orcWalkAnimation);

	Animation orcWalkFrontAnimation = Animation();

	orcWalkFrontAnimation.name = "walkFront";
	orcWalkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-front-0"));
	orcWalkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-front-1"));
	orcWalkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-front-2"));
	orcWalkFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-front-3"));


	setAnimation(orcWalkFrontAnimation);

	Animation orcWalkBackAnimation = Animation();

	orcWalkBackAnimation.name = "walkBack";
	orcWalkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-back-0"));
	orcWalkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-back-1"));
	orcWalkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-back-2"));
	orcWalkBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-back-3"));


	setAnimation(orcWalkBackAnimation);

	Animation orcAttackFrontAnimation = Animation();

	orcAttackFrontAnimation.name = "attackFront";
	orcAttackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackf-0"));
	orcAttackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackf-1"));
	orcAttackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackf-2"));
	orcAttackFrontAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackf-3"));

	setAnimation(orcAttackFrontAnimation);

	Animation orcAttackAnimation = Animation();

	orcAttackAnimation.name = "attack";
	orcAttackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attack-0"));
	orcAttackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attack-1"));
	orcAttackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attack-2"));
	orcAttackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attack-3"));


	setAnimation(orcAttackAnimation);

	Animation orcAttackBackAnimation = Animation();

	orcAttackBackAnimation.name = "attackBack";
	orcAttackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackb-0"));
	orcAttackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackb-1"));
	orcAttackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackb-2"));
	orcAttackBackAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-attackb-3"));

	setAnimation(orcAttackBackAnimation);

	Animation orcHitAnimation = Animation();

	orcHitAnimation.name = "hit";
	orcHitAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-hit-0"));
	orcHitAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-hit-1"));

	setAnimation(orcHitAnimation);

	Animation orcDeadAnimation = Animation();

	orcDeadAnimation.name = "dead";
	orcDeadAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-dead-0"));
	orcDeadAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-dead-1"));
	orcDeadAnimation.frames.push_back(getSpriteSheet()->getFrame("orc-dead-2"));

	setAnimation(orcDeadAnimation);
}


void BaseEnemy::buildClockwisPath()
{
	/*m_path.push_back(LVLMAN::Instance()->getLevel()[1][1]->m_node);
	m_path.push_back(LVLMAN::Instance()->getLevel()[30][1]->m_node);
	m_path.push_back(LVLMAN::Instance()->getLevel()[1][22]->m_node);
	m_path.push_back(LVLMAN::Instance()->getLevel()[30][22]->m_node);*/

	//m_path.push_back(LVLMAN::Instance()->m_levelNodes[32]);

	/*for (auto i = 33; i < Config::COL_NUM*2-1; i++)
	{
		m_path.push_back(LVLMAN::Instance()->getLevelNodes()[i]);
	}*/

	for (auto i = 2; i < Config::ROW_NUM - 1; i++)
	{
		m_path.push_back(LVLMAN::Instance()->getLevelNodes()[i * Config::COL_NUM + Config::COL_NUM - 2]);
	}

	/*for (auto i = 33; i < Config::COL_NUM*2-2; i++)
	{
		m_path.push_back(LVLMAN::Instance()->getLevelNodes()[Config::COL_NUM * Config::ROW_NUM - 2 - i]);
	}*/

	/*for (auto i = Config::ROW_NUM - 2; i > 0; i--)
	{
		m_path.push_back(LVLMAN::Instance()->getLevelNodes()[i * Config::COL_NUM + 1]);
	}*/
}

void BaseEnemy::m_displayPath()
{
	for (auto node : m_path)
	{
		//std::cout << "(" << node->x << ", " << node->y << ")\n";

	}
}

std::vector<PathNode*>& BaseEnemy::getPath()
{
	return m_path;
}

void BaseEnemy::moveToTarget()
{
	if (m_patrolMode)
	{
		m_pTargetPathNode = m_path[m_targetPathNodeIndex];
		glm::vec2 targetVector = Util::normalize(m_pTargetPathNode->getTransform()->position - this->getTransform()->position);

		if (targetVector.x = 1)
		{
			m_angle = 90.0f;
		}
		else if (targetVector.x = -1)
		{
			m_angle = -90.0f;
		}
		if (targetVector.y = 1)
		{
			m_angle = 180.0f;
		}
		else if (targetVector.y = -1)
		{
			m_angle = 0;
		}

		getRigidBody()->velocity = targetVector;
		getTransform()->position += getRigidBody()->velocity * getRigidBody()->maxSpeed;

		if (getTransform()->position == m_pTargetPathNode->getTransform()->position)
		{
			m_targetPathNodeIndex++;
			if (m_targetPathNodeIndex > m_path.size() - 1)
			{
				m_targetPathNodeIndex = 0;
			}
		}
	}
}

void BaseEnemy::setAngle(float angle)
{
	m_angle = angle;
}

void BaseEnemy::togglePatrol()
{
	m_patrolMode = !m_patrolMode;
}

void BaseEnemy::checkRadiusDetection()
{
	if (CollisionManager::circleAABBCheck(this, m_pTarget, m_detectionRadius))
	{
		std::cout << "Player Detected\n";
		m_targetDetected = true;
	}
	else
	{
		m_targetDetected = false;
	}
}

int BaseEnemy::getRadius()
{
	return m_detectionRadius;
}

void BaseEnemy::checkLOS()
{
	//if(CollisionManager::LOSCheck(this,m_pTarget,))
}