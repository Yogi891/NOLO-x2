#ifndef _GUI_H_
#define _GUI_H_

#include "SFML\Graphics.hpp"

class GUI
{
public:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//C'tor
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GUI();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//D'tor
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~GUI();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Updates the gui :P
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(float a_HighScore = 0, float a_MultiPlier = 0, float a_Time = 0, int a_Lives = 0, float m_Missile = 1);

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Inits all the sprites needed for the gui
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Init();

private:
	//
	//Sprites for the different sections of the GUI
	//
	sf::Sprite* m_pTimer;
	sf::Sprite* m_pScore;
	sf::Sprite* m_pMultiplier;
	sf::Sprite* m_pLife1;
	sf::Sprite* m_pLife2;
	sf::Sprite* m_pMissileTimer;

	sf::String* m_pCurScore;
	sf::String* m_pTime;
	sf::String* m_pLives;
	sf::String* m_pMulti;

	int m_Time;
};

#endif