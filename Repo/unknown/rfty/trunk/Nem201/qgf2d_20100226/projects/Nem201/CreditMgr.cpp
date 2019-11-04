#include "CreditMgr.h"
#include "Renderer.h"
#include <iostream>

CreditMgr* CreditMgr::m_pInstance = NULL;

CreditMgr::CreditMgr()
{
	m_Credit = 0;
}

CreditMgr::~CreditMgr()
{
}


CreditMgr& CreditMgr::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new CreditMgr();
	}
	return *m_pInstance;
}

void CreditMgr::AddCredit()
{
	if(m_Credit < 9)
		m_Credit += 1;
}

void CreditMgr::LowerCredit()
{
	if(m_Credit > 0)
		m_Credit -= 1;
}

bool CreditMgr::HasCredit()
{
	if(m_Credit > 0)
		return true;
	return false;
}

void CreditMgr::Check()
{
	//
	//Grabs the window to obtain input
	//
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();

	//
	//Updates the credits
	//
	if(window.GetInput().IsKeyDown(sf::Key::Space))
	{
		AddCredit();
	}
}