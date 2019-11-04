#ifndef _BULLET_H_
#define _BULLET_H_

#include "SFML/Graphics.hpp"
#include "resman.h"

class Bullet
{
public:
	//////////////////////////////////////////////////////////////////////////////////
	//C'tor
	//////////////////////////////////////////////////////////////////////////////////
	Bullet(){};

	//////////////////////////////////////////////////////////////////////////////////
	//D'tor
	//////////////////////////////////////////////////////////////////////////////////
	virtual ~Bullet(){};

	/////////////////////////////////////////////////////////////////////////////////
	//Main loop for bullets
	/////////////////////////////////////////////////////////////////////////////////
	virtual void Update(float dt) = 0;

	//////////////////////////////////////////////////////////////////////////////////
	//Creates the bullet
	//Requires lifetime and spawn location, passed in by class that owns the bullet
	//////////////////////////////////////////////////////////////////////////////////
	virtual void Init(float lifeTime,sf::Vector2f pos) = 0;

protected:

	//
	//Sprite for the bullet
	//
	sf::Sprite* m_pSprite;

	//
	//Stores life time in seconds
	//
	float m_LifeTime;

	//
	//Stores if a bullet is alive or not
	//
	bool m_IsAlive;

};


#endif