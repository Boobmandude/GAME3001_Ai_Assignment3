#include "Plane.h"
#include "TextureManager.h"
#include "LevelManager.h"
#include "Util.h"
#include "CollisionManager.h"
Plane::Plane(GameObject* target)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);
	buildClockwisPath();
	getTransform()->position = m_path[0]->getTransform()->position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->maxSpeed = 5.0f;
	setType(PLANE);
	m_detectionRadius = 100;
	m_targetDetected = false;
	m_buildAnimations();
	m_targetPathNodeIndex = 1;
	m_patrolMode = false;
	m_pTarget = target;
	m_hasLOS = false;
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"),
		x, y, 0.5f, m_angle, 255, true);
}

void Plane::update()
{
	/*setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);*/
	checkRadiusDetection();
	moveToTarget();
}

void Plane::clean()
{
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}


void Plane::buildClockwisPath()
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

	for (auto i = 2; i < Config::ROW_NUM-1; i++)
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

void Plane::m_displayPath()
{
	for (auto node : m_path)
	{
		//std::cout << "(" << node->x << ", " << node->y << ")\n";
		
	}
}

std::vector<PathNode*>& Plane::getPath()
{
	return m_path;
}

void Plane::moveToTarget()
{
	if (m_patrolMode) 
	{
		m_pTargetPathNode = m_path[m_targetPathNodeIndex];
		auto targetVector = Util::normalize( m_pTargetPathNode->getTransform()->position - this->getTransform()->position );

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

void Plane::setAngle(float angle)
{
	m_angle = angle;
}

void Plane::togglePatrol()
{
	m_patrolMode = !m_patrolMode;
}

void Plane::checkRadiusDetection()
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

int Plane::getRadius()
{
	return m_detectionRadius;
}

void Plane::checkLOS()
{
	//if(CollisionManager::LOSCheck(this,m_pTarget,))
}
