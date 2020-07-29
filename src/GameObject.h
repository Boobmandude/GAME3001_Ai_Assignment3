#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
#include <string>
#include <vector>
// enums
#include "GameObjectType.h"

enum ColDirections {
	NOCOLLISION = 0,
	EAST,
	WEST,
	NORTH,
	SOUTH,
	NUMOFSIDES
};

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	Transform* getTransform();

	// getters and setters for physics properties
	RigidBody* getRigidBody();
	
	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	int getHealth();
	int getMaxHealth();
	void takeDamage(int damage);

	void setWidth(int new_width);
	void setHeight(int new_height);
	void setPosX(int new_posX);
	void setPosY(int new_posY);
	GameObjectType getType() const;
	void setType(GameObjectType new_type);
	bool checkLevelCollision(std::vector<GameObject*> listObstacles);
	//virtual int& getHealth();
	//virtual int& getDamage();

	ColDirections m_boundHit = NOCOLLISION;
private:
	// transform component
	Transform m_transform;
	
	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;
	int m_posX;
	int m_posY;
	GameObjectType m_type;

protected:
	int m_health;
	int m_maxHealth;
	int m_damage;
	int m_speed;
};

#endif /* defined (__GAME_OBJECT__) */