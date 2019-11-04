#include "Renderer.h"


#include <iostream>

//
//Singleton instance pre define
//
Renderer* Renderer::m_pInstance = NULL;

Renderer::Renderer()
{
	m_pWindow = new sf::RenderWindow (sf::VideoMode(1280, 720, 32), "Game Name");
	m_pWindow->SetFramerateLimit(60);
}

Renderer::~Renderer()
{
}

Renderer& Renderer::GetInstance()
{
	//
	//creates an instance if one doesnt exist
	//
	if(!m_pInstance)
	{
		m_pInstance = new Renderer();
	}

	//
	//returns the singleton instance
	//
	return *m_pInstance;
}

void Renderer::InitRenderer()
{
	//
	//only inits the renderer if an instance hasnt already been created
	//
	if(m_pInstance == NULL)
	{
		m_pInstance = new Renderer();

		//
		//creats all other member data
		//	
		
	}
	
	
}

void Renderer::ShutDown()
{
	//
	//Deletes member data
	//


	//
	//deletes the singleton instance
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
	}
}



bool Renderer::AddDrawable(sf::Drawable& temp)
{
	m_pToDraw.push_back(&temp);
	return false;
}


void Renderer::RenderAll()
{
	//
	//Clears the screen of old images
	//
	m_pWindow->Clear();

	//
	//Goes through everything that needs to be drawn this frame
	//
	for(std::vector<sf::Drawable*>::iterator iter = m_pToDraw.begin(); iter != m_pToDraw.end(); iter++)
	{
		m_pWindow->Draw(**iter);
	}

	//
	//Displays all to screen
	//
	m_pWindow->Display();

	//
	//Clears vector after all things have been drawn
	//
	m_pToDraw.clear();
}
