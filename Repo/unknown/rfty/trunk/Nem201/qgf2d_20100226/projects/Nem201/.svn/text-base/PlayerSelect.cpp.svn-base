#include "PlayerSelect.h"


PlayerSelect::PlayerSelect()
{
	m_pBGSprite = new sf::Sprite(Resman::GetInstance().GetImage("PSBG"));
}

PlayerSelect::~PlayerSelect()
{
}

void PlayerSelect::Run(float dt)
{
	//
	//Grabs the window to obtain input
	//
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();

	if(window.GetInput().IsKeyDown(sf::Key::Num1))
	{
		StateMgr::GetInstance().SetShipType(AllRound);
		StateMgr::GetInstance().SwitchState(timeAttack);
	}
	if(window.GetInput().IsKeyDown(sf::Key::Num2))
	{
		StateMgr::GetInstance().SetShipType(Attack);
		StateMgr::GetInstance().SwitchState(timeAttack);
	}
	if(window.GetInput().IsKeyDown(sf::Key::Num3))
	{
		StateMgr::GetInstance().SetShipType(Defence);
		StateMgr::GetInstance().SwitchState(timeAttack);
	}

	//
	//Renders all sprites
	//
	Renderer::GetInstance().AddDrawable(*m_pBGSprite);
}
