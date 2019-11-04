#include "Timeattack.h"
#include "BackGround.h"
#include "GameConfig.h"
#include "BasicBullet.h"
#include "Upgrade.h"
#include "Enemy.h"
#include "Collision.h"
#include "GUI.h"
#include <sstream>
#include "CBullet.h"
#include "Test_Bullet.h"
#include "BEnemy.h"

//#pragma comment(lib, "BulletML_v2.lib")

Timeattack::Timeattack(ShipType Ship)
: pBMLS(NULL)
, kgo(false)
, m_enemyCount(30)
{

	m_pGUI = new GUI();
	//
	//inits member data to defaults
	//
	m_Timer = 120;
	m_WeaponLvl = 1;
	m_pPlayer = new Player(Ship);
	m_pBackGround = new BackGround();

	m_pMissTimer = new sf::String();
	m_pMissTimer->SetPosition(800,50);
	m_pMissTimer->SetColor(sf::Color(255,0,0,255));


	m_BBulletSpeed = GameConfig::GetInstance().GetConfigValue("P_BASIC_BULLET_SPEED");

	m_stateType = timeAttack; // State Identifier

	m_WaveTimer = 10;

	//
	//Inits bullets for player
	//
	float Max = GameConfig::GetInstance().GetConfigValue("MAX_BULLETS");
	for(int i = 0; i<= Max; i++)
	{
		BasicBullet* pBullet = new BasicBullet(*this);
		m_pBullets.push_back(pBullet);
	}
	for(int j = 0; j < 10; j++)
	{
		Upgrade* pUpgrade = new Upgrade();
		m_pUpgrades.push_back(pUpgrade);
	}
	m_Score = 0;
	m_Multiplier = 1;


//	for(int k = 0; k <50; k++)
//	{
//		Enemy* pEnemy = new Enemy();
//		m_pEnemies.push_back(pEnemy);
//	}
/*
	pBMLS = new BMLScript("Data/XML/simple.xml");

	testEnemy = new BEnemy(0, 100);
	XMLParser xML;
/*
	pBMLS->SetPlayer(m_pPlayer);
*/

	HackLevel();
}
Timeattack::Timeattack()
{
	m_Timer = 180;
	m_WeaponLvl = 1;
	m_pPlayer = new Player(AllRound);
	m_pBackGround = new BackGround();

	m_stateType = timeAttack; // State Identifier

	//
	//Inits bullets for player
	//
	float Max = GameConfig::GetInstance().GetConfigValue("MAX_BULLETS");
	for(int i = 0; i<= Max; i++)
	{
		BasicBullet* pBullet = new BasicBullet(*this);
		m_pBullets.push_back(pBullet);
	}
}

Timeattack::~Timeattack()
{
	//
	//Deletes bullets
	//
	for(std::vector<BasicBullet*>::iterator iter ; iter != m_pBullets.end();iter++)
	{
		BasicBullet* pBullet = *iter;
		delete pBullet;
	}
}


void Timeattack::Run(float dt)
{

	//
	//Does collision checks for last frame
	//
	Collision::GetInstance().Update(*m_pPlayer,m_pBullets, m_benemies, pBulletPool);



	//
	//Updates the background
	// Done first so everything is ontop of it
	//
	m_pBackGround->Update(dt);

	//
	//Updates player ship
	//
	m_pPlayer->UpdateShip(dt,*this);

	//
	//Updates the timer ad displays it to screen
	//
	m_Timer -= dt;
	if(m_Timer <= 0)
	{
		StateMgr::GetInstance().SwitchState(menu);
	}

	//
	//Shows The time till next missile
	//
	std::ostringstream miss;
	miss << m_pPlayer->GetMissileTimer();
	m_pMissTimer->SetText(miss.str().c_str());

	if(!kgo) 
	{
		UpdateBulletML(dt);
		kgo = true;
	}

	//
	//Updates all bullets and renders them
	//
	UpdateBullets(dt);

	//HACK TO INCREASE/DECREASE BULLET POWER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if(Renderer::GetInstance().GetWindow().GetInput().IsKeyDown(sf::Key::W))
	{
		if(m_WeaponLvl < 6)
			m_WeaponLvl++;
	}
	if(Renderer::GetInstance().GetWindow().GetInput().IsKeyDown(sf::Key::S))
	{
		if(m_WeaponLvl > 1)
			m_WeaponLvl--;
	}
/*	m_WaveTimer -= dt;
	
	if(m_WaveTimer <= 0)
	{
		for(std::vector<Enemy*>::iterator iter = m_pEnemies.begin(); iter != m_pEnemies.end(); iter++)
		{
			Enemy* temp = *iter;
			if(!temp->GetAlive())
			{
				temp->Create(bee,sf::Vector2f(1200,370));
				m_WaveTimer = 1;
				break;
			}
		}
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

	UpdateEnemy(dt);
	//
	//BulletML testing 
	//
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();

/*	if(window.GetInput().IsKeyDown(sf::Key::G))
	{
		if(!pBMLS->IsNowPlaying())
		{
			UpdateBulletML(dt);
			pBMLS->FireScript(dt);
	
		}
	}
*/

	//
	//Updates the GUI
	//
	if(m_Multiplier >= 1)
		m_Multiplier -= (dt/2);
	m_pGUI->Update((float)m_Score,m_Multiplier,m_Timer,m_pPlayer->GetLives(),(m_pPlayer->GetMissileTimer()/10) );

	//
	//Adds ship to renderer last so it is on top of everythign else
	//The player doesnt call its own render to make sure it is on top
	//
	//Renderer::GetInstance().AddDrawable(*m_pMissTimer);
	Renderer::GetInstance().AddDrawable(m_pPlayer->GetDrawable());
}

void Timeattack::CreatePBullet(float a_Angle)
{
	float Counter =1;
	float MaxBullets = 0;
	float MaxAngle = 0;

	//
	//Switch statement to work out bullet angles
	//
	switch (m_WeaponLvl)
	{
	case 1:
		{
			MaxBullets = 2;
			MaxAngle = -(a_Angle * ((MaxBullets /2) +0.5f));
			break;
		}
	case 2:
		{
			MaxBullets = 3;
			MaxAngle = -(a_Angle * (MaxBullets /2));
			break;
		}
	case 3:
		{
			MaxBullets = 4;
			MaxAngle = -(a_Angle * ((MaxBullets /2) +0.5f));
			break;
		}
	case 4:
		{
			MaxBullets = 5;
			MaxAngle = -(a_Angle * (MaxBullets /2));
			break;
		}
	case 5:
		{
			MaxBullets = 6;
			MaxAngle = -(a_Angle * ((MaxBullets /2) +0.5f));
			break;
		}
	case 6:
		{
			MaxBullets = 7;
			MaxAngle = -(a_Angle * (MaxBullets /2));
			break;
		}
	default:
		break;
	}



	//
	//loop creating bullets
	//
	for(std::vector<BasicBullet*>::iterator iter = m_pBullets.begin(); iter != m_pBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(!pBullet->IsALive())
		{
			pBullet->Init(m_pPlayer->GetBulletLifeTime(),m_pPlayer->GetDrawable().GetPosition(), normal);
			sf::Vector2f temp(m_BBulletSpeed,0);
			float angle = MaxAngle + (a_Angle*Counter);
			float x = ((cos(angle)*temp.x) - (sin(angle) * temp.y));
			float y = ((sin(angle)*temp.x) + (cos(angle) * temp.y));
			temp.x = x;
			temp.y = y;
			pBullet->SetVelocity(temp);
			Counter++;
			if(Counter > MaxBullets)
				break;
		}
	}
}

void Timeattack::CreateMissile()
{
	float Counter =1;
	//
	//loop creating bullets
	//
	for(std::vector<BasicBullet*>::iterator iter = m_pBullets.begin(); iter != m_pBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(!pBullet->IsALive())
		{
			pBullet->Init(m_pPlayer->GetBulletLifeTime(),m_pPlayer->GetDrawable().GetPosition(), missile, (Counter-1));
			sf::Vector2f temp(m_BBulletSpeed,0);
			pBullet->SetVelocity(temp);
			Counter++;
			if(Counter > m_WeaponLvl)
				break;
		}
	}

}

void Timeattack::CreateBomb()
{
	//
	//loop creating bullets
	//
	for(std::vector<BasicBullet*>::iterator iter = m_pBullets.begin(); iter != m_pBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(!pBullet->IsALive())
		{
			pBullet->Init(m_pPlayer->GetBulletLifeTime(),m_pPlayer->GetDrawable().GetPosition(), bomb);
			break;
		}
	}
	
}



// Test Bullet using BulletML
void Timeattack::CreateTBullet()
{



}

void Timeattack::CreateEBullet()
{
}

void Timeattack::UpdateBullets(float dt)
{
	for(std::vector<BasicBullet*>::iterator iter = m_pBullets.begin(); iter != m_pBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(pBullet->IsALive())
		{
			pBullet->Update(dt);
		}
	}
	pBulletPool.clear();

	for(int i = 0; i < m_enemyCount; ++i)
	{
		pBMLS[i]->ShootBullets(*this, dt);

		for(int j = 0; j < pBMLS[i]->GetNumbBulletsInm_Bullets(); ++j)
		{
			if(pBMLS[i]->GetBullet(j)->IsAlive())
			{
				pBulletPool.push_back(pBMLS[i]->GetBullet(j));
			}
		}
	}
}

void Timeattack::UpdateUpgrades(float dt)
{
	for(std::vector<Upgrade*>::iterator iter = m_pUpgrades.begin(); iter != m_pUpgrades.end(); iter++)
	{
		Upgrade* pUpgrade = *iter;
		if(pUpgrade->Alive())
		{
			pUpgrade->Run(dt);
		}
	}
}

void Timeattack::UpdateBulletML(float dt)
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		pBMLS[i]->FireScript(dt);
	}
}		


void Timeattack::UpdateEnemy(float dt)
{
	for(std::vector<Enemy*>::iterator iter = m_pEnemies.begin(); iter != m_pEnemies.end(); iter++)
	{
		Enemy* temp = *iter;
		if(temp->GetAlive())
		{
			temp->Update(*this, dt);
		}
	}
}

void Timeattack::HackLevel()
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		BMLScript* script = new BMLScript("Data/XML/simple2.xml");

		script->SetPlayer(m_pPlayer);
		script->SetEnemyStart(rand()%680 + 20);
		script->SetStartTime((i * 1 + ((float)rand()/(float)RAND_MAX - 0.5f)) + 2);
		script->RunScript(0);
		m_benemies.push_back(script->GetEnemy());
		pBMLS.push_back(script);
	}
}

void Timeattack::AddScore(int a_Increase)
{
	m_Score += (a_Increase * (int)m_Multiplier);
}

void Timeattack::IncreaseMulti()
{
	if(m_Multiplier <=8)
		m_Multiplier++;
}
