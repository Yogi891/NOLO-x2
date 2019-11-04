#include "Protobullet.h"
#include <math.h>
#include "resman.h"
#include "Renderer.h"

ProtoBullet::ProtoBullet(BulletMLState* a_state, double a_xPos, double a_yPos, double a_dir, double a_speed)
: m_xPos(a_xPos),
  m_yPos(a_yPos),
  m_dir(a_dir),
  m_speed(a_speed)
{
	m_bml = new BML_Test(a_state, NULL);

	m_pSprite = new sf::Sprite(Resman::GetInstance().GetImage("PBullet"));
	m_pSprite->Scale(0.5,0.1);
	m_pSprite->SetPosition(a_xPos, a_yPos);
	m_isAlive = false;


	m_pSprite = new sf::Sprite(Resman::GetInstance().GetImage("PBullet"));
	m_pSprite->Scale(0.5,0.1);
	m_pSprite->SetPosition(a_xPos, a_yPos);
	m_isAlive = false;

}

ProtoBullet::ProtoBullet(BulletMLParser* a_parser, double a_xPos, double a_yPos, double a_dir, double a_speed)
: m_xPos(a_xPos),
  m_yPos(a_yPos),
  m_dir(a_dir),
  m_speed(a_speed)
{
	m_bml = new BML_Test(a_parser, NULL);

	m_pSprite = new sf::Sprite(Resman::GetInstance().GetImage("PBullet"));
	m_pSprite->Scale(0.5,0.1);
	m_pSprite->SetPosition(a_xPos, a_yPos);
	m_isAlive = false;
}

ProtoBullet::~ProtoBullet()
{

}


void ProtoBullet::move()
{
	if(m_isAlive)
	{
//		m_bml->run();
	}
	Renderer::GetInstance().AddDrawable(*m_pSprite);
//	m_xPos += m_bml->getBulletSpeed() * sin(m_bml->getBulletDirection());
//	m_yPos -= m_bml->getBulletSpeed() * cos(m_bml->getBulletDirection());
}

void ProtoBullet::draw()
{

}

void ProtoBullet::die()
{
	m_isAlive = false;
}

double ProtoBullet::GetDir() const
{
	return m_dir;
}

double ProtoBullet::GetXPos() const
{
	return m_xPos;
}

double ProtoBullet::GetYPos() const
{
	return m_yPos;
}

double ProtoBullet::GetSpeed() const
{
	return m_speed;
}

bool ProtoBullet::IsAlive() const
{
	return m_isAlive;
}
