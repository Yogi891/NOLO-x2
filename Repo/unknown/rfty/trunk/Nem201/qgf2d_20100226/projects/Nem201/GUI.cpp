#include "GUI.h"
#include "Resman.h"
#include "Renderer.h"
#include <sstream>


GUI::GUI()
{
	m_pTimer = new sf::Sprite();
	m_pScore = new sf::Sprite();
	m_pMultiplier = new sf::Sprite();
	m_pLife1 = new sf::Sprite();
	m_pLife2 = new sf::Sprite();
	m_pMissileTimer = new sf::Sprite();

	m_pCurScore = new sf::String();
	m_pTime = new sf::String();
	m_pLives = new sf::String();
	m_pMulti = new sf::String();

	m_Time = 120;

	Init();
}

GUI::~GUI()
{
}

void GUI::Update(float a_HighScore, float a_MultiPlier, float a_Time, int a_Lives,  float m_Missile)
{
	//
	//Adds sprites to renderer
	//
	Renderer::GetInstance().AddDrawable(*m_pScore);
	Renderer::GetInstance().AddDrawable(*m_pTimer);
	Renderer::GetInstance().AddDrawable(*m_pMultiplier);

	if(m_Missile >= 1)
		m_Missile = 1;
	m_pMissileTimer->Scale(m_Missile,1);
	Renderer::GetInstance().AddDrawable(*m_pMissileTimer);

	//
	//Adds the lives sprites according to how many lives the player 
	//
	if(a_Lives >= 1)
		Renderer::GetInstance().AddDrawable(*m_pLife1);

	if(a_Lives == 2)
		Renderer::GetInstance().AddDrawable(*m_pLife2);
	
	//
	//Adds the text to the renderer
	//
	Renderer::GetInstance().AddDrawable(*m_pLives);
	Renderer::GetInstance().AddDrawable(*m_pCurScore);
	Renderer::GetInstance().AddDrawable(*m_pMulti);

	//
	//Updates the timer
	//
	std::ostringstream temp;
	int time =(int) (m_Time - a_Time);
	temp << time;
	m_pTime->SetText(temp.str().c_str());
	Renderer::GetInstance().AddDrawable(*m_pTime);

	std::ostringstream score;
	score << a_HighScore;
	m_pCurScore->SetText(score.str().c_str());

	std::ostringstream multi;
	multi << "X: " << (int)a_MultiPlier;
	m_pMulti->SetText(multi.str().c_str());

}


void GUI::Init()
{
	//
	//loads all the sprites images and set thier location
	//
	m_pScore->SetImage(Resman::GetInstance().GetImage("GUI"));
	m_pScore->SetSubRect(sf::IntRect(0,0,128,126));
	m_pScore->Scale(2,2);
	m_pScore->SetPosition(0,-110);

	m_pTimer->SetImage(Resman::GetInstance().GetImage("GUI"));
	m_pTimer->SetSubRect(sf::IntRect(128,0,256,128));
	m_pTimer->Scale(1,1);
	m_pTimer->SetPosition(576,-40);

	m_pMultiplier->SetImage(Resman::GetInstance().GetImage("GUI"));
	m_pMultiplier->SetSubRect(sf::IntRect(384,0,512,128));
	m_pMultiplier->Scale(2,2);
	m_pMultiplier->SetPosition(1024,-110);

	m_pLife1->SetImage(Resman::GetInstance().GetImage("GUI"));
	m_pLife1->SetSubRect(sf::IntRect(256,0,384,128));
	m_pLife1->Scale(0.5f,0.5f);
	m_pLife1->SetPosition(80,656);

	m_pLife2->SetImage(Resman::GetInstance().GetImage("GUI"));
	m_pLife2->SetSubRect(sf::IntRect(256,0,384,128));
	m_pLife2->Scale(0.5f,0.5f);
	m_pLife2->SetPosition(128,656);

	m_pMissileTimer->SetImage(Resman::GetInstance().GetImage("Upgrade"));
	m_pMissileTimer->SetSubRect(sf::IntRect(1280,0,1408,128));
	m_pMissileTimer->SetPosition(1116,640);

	//
	//Sets defualt sting texts
	//
	m_pLives->SetText("Lives:");
	m_pLives->SetPosition(0,672);
	m_pLives->SetColor(sf::Color(255,0,0,255));
	
	m_pTime->SetText("0");
	m_pTime->SetCenter(16,16);
	m_pTime->SetPosition(624,32);

	m_pCurScore->SetText("0");
	m_pCurScore->SetPosition(65,10);

	m_pMulti->SetText("X");
	m_pMulti->SetPosition(1175,5);
}