#ifndef _STATE_H_
#define _STATE_H_
#include "StateMgr.h"
#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "Resman.h"
#include "CreditMgr.h"

//
//Different state types
//
enum StateType          
{						 
	menu,				 
	pause,				
	highScore,			
	timeAttack,
	playerSelect
};

class State
{
public:
	/////////////////////////////////////////////////////////////////////////////////
	//C'tor
	/////////////////////////////////////////////////////////////////////////////////
	State();

	/////////////////////////////////////////////////////////////////////////////////
	//Virtual D'tor
	/////////////////////////////////////////////////////////////////////////////////
	virtual ~State();

	/////////////////////////////////////////////////////////////////////////////////
	//Is the main call for a state
	/////////////////////////////////////////////////////////////////////////////////
	virtual void Run(float dt) = 0;

	/////////////////////////////////////////////////////////////////////////////////
	//Returns what type the state is
	/////////////////////////////////////////////////////////////////////////////////
	virtual StateType& GetType() = 0;

protected:

	//
	//Sortes the states type
	//
	StateType m_stateType;
};


#endif