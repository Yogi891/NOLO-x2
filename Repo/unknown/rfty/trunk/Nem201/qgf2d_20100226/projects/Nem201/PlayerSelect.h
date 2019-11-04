#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

#include "State.h"
#include "Player.h"

class PlayerSelect : public State
{
public:
	/////////////////////////////////////////////////////////////////////////////////////////
	//State inheriated functions
	/////////////////////////////////////////////////////////////////////////////////////////
	PlayerSelect();
	virtual ~PlayerSelect();
	virtual void Run(float dt);
	virtual StateType& GetType(){return m_stateType;};

protected:

private:
	//
	//Stores the type of ship choosen
	//
	ShipType m_Ship;

	//
	//Stores the BG
	//
	sf::Sprite* m_pBGSprite;

};

#endif
