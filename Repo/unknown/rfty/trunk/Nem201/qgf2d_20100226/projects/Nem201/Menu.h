/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Just a simple menu state
// Author: Daemon Walters
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MENU_H_
#define _MENU_H_

#include "State.h"

class Menu : public State
{
public:
	Menu();
	virtual ~Menu();
	virtual void Run(float dt);
	virtual StateType& GetType();
	
private:
	sf::Sprite* m_menuBG;
	sf::Image* m_menuImage;

	sf::String* m_pCredit;
	int m_Counter;
};

#endif