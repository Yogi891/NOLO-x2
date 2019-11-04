#include "Enemy.h"
#include "Resman.h"
#include "Renderer.h"
#include "Timeattack.h"

Enemy::Enemy()
{
	m_IsAlive = false;
	m_pSprite = new sf::Sprite();
	m_Health = 0;
	m_Score =0;
}

Enemy::~Enemy()
{
	delete m_pSprite;
}


void Enemy::Create(type a_Type, sf::Vector2f a_Pos)
{
	m_IsAlive = true;
	
	switch(a_Type)
	{
	case bee:
		{
			m_Health = 10;
			m_pSprite->SetImage(Resman::GetInstance().GetImage("TestShip"));
			m_pSprite->SetPosition(a_Pos);
			m_pSprite->SetSubRect(sf::IntRect(91,53,128,106));
			m_pSprite->Rotate(90);
			m_Circ.Center = m_pSprite->GetPosition();
			m_Circ.Radius = 32;
			m_Score =10;
			break;
		}
	case wasp:
		{
			m_Health = 10;
			m_pSprite->SetImage(Resman::GetInstance().GetImage("TestShip"));
			m_pSprite->SetPosition(a_Pos);
			m_pSprite->SetSubRect(sf::IntRect(91,53,128,106));
			m_pSprite->Rotate(90);
			m_Circ.Center = m_pSprite->GetPosition();
			m_Circ.Radius = 32;
			m_Score =15;
			break;
		}
	case bettle:
		{
			m_Health = 10;
			m_pSprite->SetImage(Resman::GetInstance().GetImage("TestShip"));
			m_pSprite->SetPosition(a_Pos);
			m_pSprite->SetSubRect(sf::IntRect(91,53,128,106));
			m_pSprite->Rotate(90);
			m_Circ.Center = m_pSprite->GetPosition();
			m_Circ.Radius = 32;
			m_Score =20;
			break;
		}
	}
}

void Enemy::Update(Timeattack& state, float dt)
{
	sf::Vector2f pos = m_pSprite->GetPosition();
	pos.x -= 200 * dt;
	m_pSprite->SetPosition(pos);
	m_Circ.Center = m_pSprite->GetPosition();
	Renderer::GetInstance().AddDrawable(*m_pSprite);
	if(m_Health <= 0)
	{
		m_IsAlive = false;
		state.AddScore(m_Score);
		state.IncreaseMulti();
	}

}