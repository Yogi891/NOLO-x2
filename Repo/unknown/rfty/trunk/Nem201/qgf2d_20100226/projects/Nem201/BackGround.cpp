#include "BackGround.h"
#include "Renderer.h"
#include "Resman.h"
#include <sstream>
#include "GameConfig.h"

BackGround::BackGround()
{
	//
	//Loads all the background sprites in the vector
	//
	float BGSEG = GameConfig::GetInstance().GetConfigValue("NUM_BG_SEG");
	for(int i = 1; i <= BGSEG; i++)
	{
		std::string alias = "BG";
		std::ostringstream name;
		name << alias << i;
		sf::Sprite* tempBG = new sf::Sprite(Resman::GetInstance().GetImage(name.str().c_str()));
		tempBG->SetCenter(0,0);
		tempBG->SetPosition(1275.0f*(i-1),0);
		m_pBgSprites.push_back(tempBG);
	}

	//
	//Loads all the sprties for the foreground
	//
	float FGSEG = GameConfig::GetInstance().GetConfigValue("NUM_FG_SEG");
	for(int i = 1; i <= FGSEG; i++)
	{
		std::string alias = "FG";
		std::ostringstream name;
		name << alias << i;
		sf::Sprite* tempFG = new sf::Sprite(Resman::GetInstance().GetImage(name.str().c_str()));
		tempFG->SetCenter(0,0);
		tempFG->SetPosition(1279.0f*(i-1),0);
		m_pFgSprites.push_back(tempFG);
	}
	
	//
	//Loads scroll speed for BG and FG
	//
	BGVel = -GameConfig::GetInstance().GetConfigValue("BG_SCROLL_RATE");
	FGVel = -GameConfig::GetInstance().GetConfigValue("FG_SCROLL_RATE");
}

BackGround::~BackGround()
{
	//
	//Cleans the background and foreground images up
	//
}


void BackGround::Update(float dt)
{
	//
	//Creates a new background sprite and foreground sprite if needed
	//

	//
	//Moves BG and FG
	//
	for(std::vector<sf::Sprite*>::iterator iter = m_pBgSprites.begin(); iter != m_pBgSprites.end(); iter++)
	{
		sf::Sprite* temp = *iter;
		if(temp->GetPosition().x > -1400)
			temp->Move(BGVel*dt,0);
	}
	for(std::vector<sf::Sprite*>::iterator iter = m_pFgSprites.begin(); iter != m_pFgSprites.end(); iter++)
	{
		sf::Sprite* temp = *iter;
		if(temp->GetPosition().x > -1400)
			temp->Move(FGVel*dt,0);
	}

	//
	//Renders the BG first
	//As only 3 should ever be at most rendered have added a counter
	//This lowers the number of checks
	//

	float Counter = 0;


	for(std::vector<sf::Sprite*>::iterator iter = m_pBgSprites.begin(); iter != m_pBgSprites.end(); iter++)
	{
		sf::Sprite* temp = *iter;
		if(temp->GetPosition().x < 1300 && temp->GetPosition().x > -1300)
		{
			Renderer::GetInstance().AddDrawable(*temp);
			Counter++;
			if(Counter>2)
				break;
		}
	}

	//
	//Renders FG second so it is on top
	//


	Counter = 0;

	for(std::vector<sf::Sprite*>::iterator iter = m_pFgSprites.begin(); iter != m_pFgSprites.end(); iter++)
	{
		sf::Sprite* temp = *iter;
		if(temp->GetPosition().x < 1300 && temp->GetPosition().x > -1300)
		{
			Renderer::GetInstance().AddDrawable(*temp);
			Counter++;
			if(Counter>2)
				break;
		}
	}
}