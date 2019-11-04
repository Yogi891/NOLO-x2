#include "BasicBullet.h"
#include "Timeattack.h"
#include "Renderer.h"
#include "Circle.h"

BasicBullet::BasicBullet(Timeattack& a_state)
	:m_State(a_state)
{
	//
	//Creats a in active bullet must have init called for it to function
	//
	m_pSprite = new sf::Sprite();
	m_IsAlive = false;
	m_LifeTime = 0;
	m_Dmg = 0;
	m_WaitTime = 0.0f;
	m_pCirc = new Circle();
	m_type = normal;
}

BasicBullet::~BasicBullet()
{
}

void BasicBullet::Update(float dt)
{
	//
	//Culls bullet if it is off screen
	//
	if(m_pSprite->GetPosition().x > 1240)
	{
		m_IsAlive = false;
		m_pSprite->SetScale(1,1);
		m_pSprite->SetBlendMode(sf::Blend::None);
	}

	//
	//lowers time to live then culls if bullet is dead
	//
	m_LifeTime -= dt;
	if(m_LifeTime < 0)
	{
		m_IsAlive = false;
		m_pSprite->SetScale(1,1);
		m_pSprite->SetBlendMode(sf::Blend::None);
		return;
	}

	//
	//Checks to see if bullets wait time is over
	//
	if(m_WaitTime <= 0)
	{
		//
		//Moves bullet according to it velocity
		//
		m_pSprite->Move(m_Velocity*dt);
		Renderer::GetInstance().AddDrawable(*m_pSprite);
	}
	else if (m_WaitTime > 0)
	{
		m_pSprite->SetPosition(m_State.GetPlayer().GetDrawable().GetPosition());
		m_WaitTime -= dt;
	}
	if(m_type == bomb)
	{
		m_pCirc->Radius += 16;
		float rad = m_pCirc->Radius/10;
		m_pSprite->SetScale(rad,rad);
	}
}

void BasicBullet::Init(float lifeTime,sf::Vector2f pos, bulletType a_type, float waitTime)
{
	//
	//Sets the bullet alive and loc
	//
	m_type = a_type;
	switch (a_type)
	{
	case normal:
		{
			m_LifeTime = lifeTime;
			m_pSprite->SetPosition(pos);
			m_IsAlive = true;
			m_Dmg = 1;
			m_WaitTime = 0.0f;
			m_pCirc->Center = pos;
			m_pSprite->SetImage(Resman::GetInstance().GetImage("PBullet"));
			m_pSprite->SetBlendMode(sf::Blend::Alpha);
			m_pSprite->Scale(2,2);
			break;
		}
	case missile:
		{
			m_LifeTime = lifeTime;
			m_pSprite->SetPosition(pos);
			m_IsAlive = true;
			m_Dmg = 10;
			m_WaitTime = (waitTime/5);
			m_pCirc->Center = pos;
			m_pSprite->SetImage(Resman::GetInstance().GetImage("PMissile"));
			m_pSprite->SetBlendMode(sf::Blend::Alpha);
			break;
		}
	case bomb:
		{
			m_LifeTime = lifeTime;
			m_pSprite->SetPosition(pos);
			m_IsAlive = true;
			m_Dmg = 9001;
			m_WaitTime = (0);
			m_Velocity = sf::Vector2f(0,0);
			m_pSprite->SetImage(Resman::GetInstance().GetImage("PBullet"));
			m_pCirc->Center = pos;
			m_pCirc->Radius = (float)m_pSprite->GetImage()->GetWidth()/2;
			m_pSprite->SetBlendMode(sf::Blend::Add);
			m_pSprite->Scale(0.5,0.5);
			break;
		}
	}
	m_pSprite->SetCenter((float)m_pSprite->GetImage()->GetWidth()/2,(float)m_pSprite->GetImage()->GetHeight()/2);
	
}

void BasicBullet::SetVelocity(sf::Vector2f vel)
{
	m_Velocity = vel;
}

void BasicBullet::SetAlive(bool a_Alive)
{
	m_IsAlive = a_Alive;
	m_pSprite->SetScale(1,1);
	m_pSprite->SetBlendMode(sf::Blend::None);
}