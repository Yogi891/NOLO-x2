#include "Test_Bullet.h"
#include "resman.h"
#include "CBullet.h"
#include "Timeattack.h"

Test_Bullet::Test_Bullet()
{
	m_delay = 0.0f;
	m_IsAlive = false;
	m_aimed = true;
	m_isShot = false;
	m_speed = 1.0f;
	m_pos = sf::Vector2f(0, 0);
	Resman& resman = Resman::GetInstance();
	sf::Image* m_pImage = &resman.GetImage("Bullet");
	m_pSprite = new sf::Sprite();

	m_pSprite->SetCenter(4,4);
	m_pos = sf::Vector2f(1290, 334);
	m_pSprite->SetPosition(m_pos);
	m_pSprite->Scale(2,2);
	m_pSprite->SetImage(*m_pImage);
}

// It seems BulletML doesn't want the position of the bullet
Test_Bullet::Test_Bullet(double a_direction, double a_speed)

{
	m_aimed = true;
	m_direction = a_direction;
	m_speed = a_speed;

	m_IsAlive = false;

	Resman& resman = Resman::GetInstance();
	sf::Image* m_pImage = &resman.GetImage("Bullet");
	m_pSprite = new sf::Sprite();

	m_pSprite->SetCenter(4,4);
	m_pos = sf::Vector2f(1290, 334);
	m_pSprite->SetPosition(m_pos);
	m_pSprite->SetImage(*m_pImage);

}

//
// BulletML doesn't use vectors, therefore it won't be initialized with them.
//


Test_Bullet::Test_Bullet(sf::Vector2f a_pos)
{
	m_pos = a_pos;
	m_IsAlive = true;

	Resman& resman = Resman::GetInstance();

	sf::Image* m_pImage = &resman.GetImage("Bullet");
	m_pSprite = new sf::Sprite();
	m_pSprite->SetPosition(m_pos);
	m_pSprite->SetCenter(4,4);
	m_pSprite->SetImage(*m_pImage);


}


Test_Bullet::~Test_Bullet()
{
	delete m_pSprite;
}


void Test_Bullet::Update(float dt)
{
	m_pos.y -= 200 * dt;
	if(m_pos.y < 0) m_IsAlive = false;
	else m_pSprite->SetPosition(m_pos);
}

void Test_Bullet::Init()
{
}
void Test_Bullet::Move(Timeattack& state, float dt)
{
/*
	if(!m_scripts.empty())
	{
		if(m_scripts.front().m_isRelative)
		{
			m_scripts.front().m_dir += m_prevDir/m_scripts.front().m_dirTime;
		}
		else if(m_scripts.front().m_isSequence)
		{
			m_scripts.front().m_dir += m_prevDir;

		}
	}
	if(m_scripts.front().m_delay <= 0 && m_scripts.size() > 1)
	{
		m_prevDir = m_scripts.front().m_dir;
		m_prevSpeed =  m_scripts.front().m_speed;
		m_scripts.pop();
	}
*/

//	m_pos.x += m_scripts.front().m_speed * cos(m_scripts.front().m_dir) * dt * 200;
//	m_pos.y -= m_scripts.front().m_speed * sin(m_scripts.front().m_dir) * dt * 200;

	m_pos.x += m_speed * cos(m_direction) * dt * 200;
	m_pos.y -= m_speed * sin(m_direction) * dt * 200;
	if(m_pos.x < 0 || m_pos.x > 1295 || m_pos.y < 0 || m_pos.y > 720) 
	{
		m_IsAlive = false;
		m_isShot = false;
		m_scripts.pop();
	}
	else 
	{
		m_pSprite->SetPosition(m_pos);
	}
}

void Test_Bullet::Reset()
{
	m_pos.x = 0;
	m_pos.y = 0;
	while(!m_scripts.empty())
	{
		m_scripts.pop();
	}
	m_IsAlive = true;
}

void Test_Bullet::KillBullet()
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_IsAlive = false;
}

void Test_Bullet::SetAimed(bool a_aimed)
{
	m_aimed = a_aimed;
}

bool Test_Bullet::GetAimed()
{
//	return m_scripts.front().m_isAimed;
	return m_aimed;
}	

sf::Vector2f& Test_Bullet::GetPosition()
{
	return m_pos;
}

void Test_Bullet::SetDelay(float a_delay)
{
//	m_delay = a_delay;
	m_scripts.front().m_delay = a_delay;
}

float Test_Bullet::GetDelay()
{
	return m_scripts.front().m_delay;
//	return m_delay;
}

float Test_Bullet::GetDirection()
{
//	return m_scripts.front().m_dir;
	return m_direction;
}

void Test_Bullet::SetPosition(sf::Vector2f& a_pos)
{
	m_pos = a_pos;
}

bool Test_Bullet::GetIsShot()
{
	return m_isShot;
}

void Test_Bullet::SetIsShot(bool a_isShot)
{
	m_isShot = a_isShot;
}

int Test_Bullet::GetBulletOrder()
{
	return m_bulletOrder;
}

void Test_Bullet::SetBulletOrder(bool a_bulletOrder)
{
	m_bulletOrder = a_bulletOrder;
}

float Test_Bullet::GetSpeed()
{
	return m_speed;
}

void Test_Bullet::SetSpeed(float a_speed)
{
	m_speed = a_speed;
}

float Test_Bullet::GetDirChange()
{
	return m_dirChange;
}

void Test_Bullet::SetDirChange(float a_dirChange)
{
	m_dirChange = a_dirChange;
}

int Test_Bullet::GetDirChangeTime()
{
	return m_dirChangeTime;
}

void Test_Bullet::SetDirChangeTime(float a_dirChangeTime)
{
	m_dirChangeTime = a_dirChangeTime;
}