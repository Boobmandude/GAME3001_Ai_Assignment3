#include "GameObject.h"
#include "CollisionManager.h"
GameObject::GameObject():
	m_width(0), m_height(0), m_type(NONE)
{
}

GameObject::~GameObject()
= default;

Transform* GameObject::getTransform() 
{
	return &m_transform;
}

RigidBody* GameObject::getRigidBody() 
{
	return &m_rigidBody;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

int GameObject::getPosX() const
{
	return m_posX;
}

int GameObject::getPosY() const
{
	return m_posY;
}

int GameObject::getHealth()
{
	return m_health;
}

int GameObject::getMaxHealth()
{
	return m_maxHealth;
}

void GameObject::takeDamage(int damage)
{
	m_health -= damage;
	std::cout << "Dealt " << damage << " damage\n" << m_health <<"/"<< m_maxHealth << "\n";
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setPosX(int posX)
{
	m_posX = posX;
}

void GameObject::setPosY(int posY)
{
	m_posY = posY;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}

bool GameObject::checkLevelCollision(std::vector<GameObject*> listObstacles)
{

	bool collision = false;
	for (auto o : listObstacles)
	{
			if (CollisionManager::AABBCheckColliding(this, o))
			{
				collision = true;
				if (o->getType() == OBSTACLE)
				{
					std::cout << "Hitting Obstacle\n";
				}
			}
			
	
		
			/*if (m_iNextDamageCounter == 60)
			{
				if (CollisionManager::AABBCheck(this, o))
				{
					this->getLife() += -o->getDamage();
					m_iNextDamageCounter = 0;
				}
			}*/

		
	}
	return collision;
}
