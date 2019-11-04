#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "SFML/Graphics.hpp"
#include "CircleCol.h"

class Timeattack;

enum type
{
	bee,
	wasp,
	bettle,
};

class Enemy
{
public:
	/////////////////////////////////////////////////////////////////////////////////////////
	//C'tor
	/////////////////////////////////////////////////////////////////////////////////////////
	Enemy();

	/////////////////////////////////////////////////////////////////////////////////////////
	//D'tor
	/////////////////////////////////////////////////////////////////////////////////////////
	~Enemy();

	/////////////////////////////////////////////////////////////////////////////////////////
	//Creates a new enemy of type passed in, sets it pos to the vector passed in
	/////////////////////////////////////////////////////////////////////////////////////////
	void Create(type a_Type, sf::Vector2f a_Pos);

	/////////////////////////////////////////////////////////////////////////////////////////
	//Updates the enemy
	/////////////////////////////////////////////////////////////////////////////////////////
	void Update(Timeattack& state, float dt);

	/////////////////////////////////////////////////////////////////////////////////////////
	//Returns if it is alive
	/////////////////////////////////////////////////////////////////////////////////////////
	bool GetAlive(){return m_IsAlive;}

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////////////////////////////////////
	CircleCol& GetCirc(){return m_Circ;}

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////////////////////////////////////
	void SetAlive(bool a_Alive){m_IsAlive = a_Alive;}

	/////////////////////////////////////////////////////////////////////////////////////////
	//Lowers the enemies health by amount passed in
	/////////////////////////////////////////////////////////////////////////////////////////
	void LowerHealth(float a_lowerBy){ m_Health -= a_lowerBy;}

	////////////////////////////////////////////////////////////////////////////////////////
	//Returns the score of the enemy
	/////////////////////////////////////////////////////////////////////////////////////////
	int GetScore(){return m_Score;}

private:

	//
	//the enemy sprite
	//
	sf::Sprite* m_pSprite;

	//
	//Stores the state of the enemy
	//
	bool m_IsAlive;

	//
	//Stores the enemies collision area
	//
	CircleCol m_Circ;

	//
	//Stores the enemies health
	//
	float m_Health;

	//
	//Stroes how many points this enemy is worth
	//
	int m_Score;

};

#endif