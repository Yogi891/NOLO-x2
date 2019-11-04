#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <iostream>
#include "SFML/Graphics.hpp"

class BackGround
{
public:
	/////////////////////////////////////////////////////////////////////////////////////////
	//C' tor
	/////////////////////////////////////////////////////////////////////////////////////////
	BackGround();

	/////////////////////////////////////////////////////////////////////////////////////////
	//D'tor
	/////////////////////////////////////////////////////////////////////////////////////////
	~BackGround();

	/////////////////////////////////////////////////////////////////////////////////////////
	//Moves the bg and fg and loads new ones and dels old ones
	/////////////////////////////////////////////////////////////////////////////////////////
	void Update(float dt);

protected:

private:
	//
	//Holds all the background images
	//
	std::vector<sf::Sprite*> m_pBgSprites;

	//
	//Holds all the foreground images
	//
	std::vector<sf::Sprite*> m_pFgSprites;

	//
	//Scroll speeds
	//
	float BGVel;
	float FGVel;

};


#endif