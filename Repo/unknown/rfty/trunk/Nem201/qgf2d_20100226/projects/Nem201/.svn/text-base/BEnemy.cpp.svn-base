#include "BEnemy.h"
#include "CBullet.h"
#include "resman.h"


BEnemy::BEnemy(double a_direction, double a_speed)
: m_Health(10)

{
	m_direction = a_direction;
	m_speed = a_speed;
	m_delay = 0.0f;
	m_IsAlive = false;
	m_isShot = false;
	m_pos = sf::Vector2f(1290, 334);
	Resman& resman = Resman::GetInstance();
	sf::Image* m_pImage = &resman.GetImage("TestShip");
	m_pSprite = new sf::Sprite();
	m_pSprite->SetCenter(64,64);
	m_pos = sf::Vector2f(1290, 334);
	m_pSprite->SetPosition(m_pos);
	m_pSprite->SetImage(*m_pImage);
	m_pSprite->SetSubRect(sf::IntRect(0,0,128,128));
	//m_pSprite->Rotate(90);

	m_Circ.Center = m_pSprite->GetPosition();
	m_Circ.Radius = 32;

	m_Score = 10;
}

BEnemy::~BEnemy()
{
}

void BEnemy::Move(Timeattack& state, float dt)
{
/*
	if(!m_scripts.empty())
	{
		m_scripts.front().m_delay -= dt;
	}
	if(m_scripts.front().m_delay <= 0 && m_scripts.size() > 1)
	{
		m_scripts.pop();
	}
*/
//	m_pos.x += m_scripts.front().m_speed * cos(m_scripts.front().m_dir) * dt * 200;
//	m_pos.y -= m_scripts.front().m_speed * sin(m_scripts.front().m_dir) * dt * 200;

	m_pos.x += m_speed * cos(m_direction) * dt * 200;
	m_pos.y -= m_speed * sin(m_direction) * dt * 200;
	if(m_pos.x < 0 || m_pos.x > 1295 || m_pos.y < 0 || m_pos.y > 720 || m_Health < 0) 
	{
		m_IsAlive = false;
		state.AddScore(m_Score);
		state.IncreaseMulti();
		m_isShot = false;

	}
	else 
	{
		m_pSprite->SetPosition(m_pos);
	}
	m_Circ.Center = m_pos;
}
sf::Sprite& BEnemy::GetDrawable()
{
	return *m_pSprite;
}
bool BEnemy::IsAlive() const
{
	return m_IsAlive;
}
void BEnemy::Reset()
{
	m_pos.x = 1290;
	m_pos.y = 334;
	while(!m_scripts.empty())
	{
		m_scripts.pop();
	}
	m_IsAlive = true;
}
void BEnemy::KillBullet()
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_IsAlive = false;
}
void BEnemy::SetDirection(float a_dir)
{
	m_direction = a_dir;
}

void BEnemy::SetAimed(bool a_aimed)
{
	m_aimed = a_aimed;
}

bool BEnemy::GetAimed()
{
//	return m_scripts.front().m_isAimed;
	return m_aimed;
}

sf::Vector2f& BEnemy::GetPosition()
{
	return m_pos;
}

void BEnemy::SetDelay(float a_delay)
{
//	m_delay = a_delay;
	m_scripts.front().m_delay = a_delay;
}

float BEnemy::GetDelay()
{
	return m_scripts.front().m_delay;
//	return m_delay;
}

float BEnemy::GetDirection()
{
//	return m_scripts.front().m_dir;
	return m_direction;
}

void BEnemy::SetPosition(sf::Vector2f& a_pos)
{
	m_pos = a_pos;
}

bool BEnemy::GetIsShot()
{
	return m_isShot;
}

void BEnemy::SetIsShot(bool a_isShot)
{
	m_isShot = a_isShot;
}

int BEnemy::GetBulletOrder()
{
	return m_bulletOrder;
}

void BEnemy::SetBulletOrder(bool a_bulletOrder)
{
	m_bulletOrder = a_bulletOrder;
}

float BEnemy::GetSpeed()
{
	return m_speed;
}

void BEnemy::SetSpeed(float a_speed)
{
	m_speed = a_speed;
}


float BEnemy::GetDirChange()
{
	return m_dirChange;
}

void BEnemy::SetDirChange(float a_dirChange)
{
	m_dirChange = a_dirChange;
}

int BEnemy::GetDirChangeTime()
{
	return m_dirChangeTime;
}

void BEnemy::SetDirChangeTime(float a_dirChangeTime)
{
	m_dirChangeTime = a_dirChangeTime;
}