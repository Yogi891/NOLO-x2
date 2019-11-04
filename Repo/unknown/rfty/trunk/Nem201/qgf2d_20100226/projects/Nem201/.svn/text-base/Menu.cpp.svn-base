#include "Menu.h"
#include "Resman.h"


Menu::Menu()
:  m_menuBG(NULL)
,  m_menuImage(&Resman::GetInstance().GetImage("Menu"))
{
	m_menuBG = new sf::Sprite(*m_menuImage);
	m_stateType = menu;
	m_Counter = 0;
	m_pCredit = new sf::String();
	m_pCredit->SetPosition(600,320);
}
Menu::~Menu()
{

}
void Menu::Run(float dt)
{
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();

	if(window.GetInput().IsKeyDown(sf::Key::Return))
	{
		if(CreditMgr::GetInstance().HasCredit())
			StateMgr::GetInstance().SwitchState(playerSelect);
	}

	//
	//Creates the text to flash on screen
	//
	if(!CreditMgr::GetInstance().HasCredit())
	{
		m_pCredit->SetText("Insert Coin");
	}
	else
	{
		m_pCredit->SetText("Press Enter to Start!");
	}

	//
	//Renders all objects
	//
	Renderer::GetInstance().AddDrawable(*m_menuBG);

	if(m_Counter < 30)
	{
		Renderer::GetInstance().AddDrawable(*m_pCredit);
	}
	if(m_Counter > 60)
		m_Counter = 0;

	m_Counter++;
}
StateType& Menu::GetType()
{
	return m_stateType;
}
