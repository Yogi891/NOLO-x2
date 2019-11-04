#include "StateMgr.h"
#include "Renderer.h"
#include "CreditMgr.h"
#include "State.h"
#include "Timeattack.h"
#include "PlayerSelect.h"
#include "Menu.h"

#include "SFML/Graphics.hpp"

#include <iostream>
#include <sstream>


StateMgr* StateMgr::m_pInstance = NULL;

StateMgr::StateMgr()
{
}

StateMgr::~StateMgr()
{
}

StateMgr& StateMgr::GetInstance()
{
	//
	//creates an instance if there isnt one
	//
	if(!m_pInstance)
	{
		m_pInstance = new StateMgr();
	}
	//
	//returns the instance
	//
	return *m_pInstance;
}

void StateMgr::Init()
{

	//
	//inits the renderer
	//
	Renderer::InitRenderer();

	//
	//Hack to fix frame rate
	//
	SwitchState(menu);
	SwitchState(timeAttack);
	SwitchState(menu);


	//
	//Starts off with the menu
	//
	//m_pCurState = new Menu();

	//
	//
	//
	m_FPS = 60;
	m_pFPS = new sf::String();
	m_pFPS->SetColor(sf::Color(255,0,0,255));
}

void StateMgr::ShutDown()
{
	//
	//Deletes member data 1st
	//

	//
	//Deletes the instance
	//
	if (m_pInstance != NULL)
	{
		delete m_pInstance;
	}
}


void StateMgr::Run()
{
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();
	
	while(window.IsOpened())
	{
		//
		//Event to close game window when ever esc is pressed
		//
		sf::Event ev;
        while (window.GetEvent(ev))
        {
			if ((ev.Type == sf::Event::Closed) || ((ev.Type == sf::Event::KeyPressed) && (ev.Key.Code == sf::Key::Escape)))
            {
                window.Close();
                break;
            }
        }
		//
		//Get delta so it can be passed to the state
		//
		float deltaT = window.GetFrameTime();
		float fps = 1/deltaT;
		m_FPS = fps;


		//
		//Call run on top current state
		//
		m_pCurState->Run(deltaT);

		//
		//Checks of credit input
		//
		CreditMgr::GetInstance().Check();

		//
		//adds fps to renderer
		//
		std::ostringstream temp;
		temp << m_FPS;
		m_pFPS->SetText(temp.str().c_str());
		//Renderer::GetInstance().AddDrawable(*m_pFPS);

		//
		//Call render on the renderer
		//

		Renderer::GetInstance().RenderAll();
	}
	
}

void StateMgr::SwitchState(StateType state)
{
	//
	//Main switch creates the state and puts the old one into a vector
	//
	switch (state)
	{
		case menu:
			{
				if(m_pCurState)
				{
					States.push_back(m_pCurState);
				}
				m_pCurState = new Menu();
				break;
			}
		case pause:
			break;
		case playerSelect:
			{
				if(m_pCurState)
				{
					States.push_back(m_pCurState);
				}
				m_pCurState = new PlayerSelect();
				break;
			}
		case timeAttack:
			{
				if(m_pCurState)
				{
					States.push_back(m_pCurState);
				}
				m_pCurState = new Timeattack(m_ChoosenShip);
				break;
			}
		case highScore:
			break;
		default:
				break;
	}

	//
	//Cleans the old vector up
	//
	for(std::vector<State*>::iterator iter = States.end(); iter != States.begin(); iter--)
	{
		States.pop_back();
		if(States.empty())
			break;
	}
}


void StateMgr::SetShipType(ShipType ship)
{
	m_ChoosenShip = ship;
}