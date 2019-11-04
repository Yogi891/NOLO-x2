#include "Player.h"
#include "Renderer.h"
#include "Resman.h"
#include "GameConfig.h"
#include <fstream>
#include "Timeattack.h"


Player::Player(ShipType Ship)
{
	//
	//Loads Ship
	//
	LoadShip(Ship);

	m_DTCounter = 0.0f;
	m_MissileCounter = 0.0f;
	m_MissileRate  = 10.0f;
	m_BombCounter = 0.0f;
	m_BombRate = 1.0f;

	m_Circ.Center = m_ShipPos;
	m_Circ.Radius = 32;
	m_NumLives = 2;	
}

Player::~Player()
{
	delete m_pShipImage;
	delete m_pShipSprite;
}

void Player::UpdateShip(float dt, Timeattack& state)
{
	//
	//Grabs the window to obtain input
	//
	sf::RenderWindow& window = Renderer::GetInstance().GetWindow();

	//
	//Updates ships location
	//
	if(window.GetInput().IsKeyDown(sf::Key::Left))
	{
		m_ShipPos.x -= m_ShipVel.x * dt;
		if(m_ShipPos.x - m_pShipSprite->GetCenter().x < 0)
			m_ShipPos.x = 0 + m_pShipSprite->GetCenter().x;
	}
	if(window.GetInput().IsKeyDown(sf::Key::Right))
	{
		m_ShipPos.x += m_ShipVel.x * dt;
		if(m_ShipPos.x + (m_pShipSprite->GetSize().x - m_pShipSprite->GetCenter().x) > 1280)
			m_ShipPos.x = 1280 -(m_pShipSprite->GetSize().x - m_pShipSprite->GetCenter().x);
	}
	if(window.GetInput().IsKeyDown(sf::Key::Up))
	{
		m_ShipPos.y -= m_ShipVel.y * dt;
		if(m_ShipPos.y - m_pShipSprite->GetCenter().y < 0)
			m_ShipPos.y = 0 + m_pShipSprite->GetCenter().y;
	}
	if(window.GetInput().IsKeyDown(sf::Key::Down))
	{
		m_ShipPos.y += m_ShipVel.y * dt;
		if(m_ShipPos.y + (m_pShipSprite->GetSize().y - m_pShipSprite->GetCenter().y) > 720)
			m_ShipPos.y = 720 - (m_pShipSprite->GetSize().y - m_pShipSprite->GetCenter().y);
	}
	m_pShipSprite->SetPosition(m_ShipPos);

	m_Circ.Center = m_ShipPos;

	//
	//Shoots bullets per frame according to fire rate
	//

	m_DTCounter++;

	while(m_DTCounter >= m_FireRate)
	{
		if(window.GetInput().IsKeyDown(sf::Key::LControl))
		{
			state.CreatePBullet(m_Angle);
		}
		m_DTCounter -= m_FireRate;
	}

	m_MissileCounter += dt;
	if(m_MissileCounter >= m_MissileRate)
	{
		if(window.GetInput().IsKeyDown(sf::Key::Z))
		{
			state.CreateMissile();
			m_MissileCounter = 0;
		}		
	}

	m_BombCounter += dt;
	if(m_BombCounter >= m_BombRate)
	{
		if(window.GetInput().IsKeyDown(sf::Key::C))
		{
			state.CreateBomb();
			m_BombCounter =0;
		}
	}


	// Hack in a Reload Game Configurations button
	// Will put in more appropriate place later
	// Make any changes in the CFG, save, then press 'U' during run time
	// to update the game configurations
	if(window.GetInput().IsKeyDown(sf::Key::U))
	{
		GameConfig& gameConfig = GameConfig::GetInstance();
		gameConfig.LoadConfigs();
		LoadShip(AllRound);
	}
}

void Player::LoadShip(ShipType Ship)
{
	//
	//Loads ResMan
	//
	Resman& resman = Resman::GetInstance();
	
	//
	//Loads config mgr
	//
	GameConfig& gameConfig = GameConfig::GetInstance();

	//
	//Switch for file to load ship from
	//
	switch(Ship)
	{
	case AllRound:
		{
			//
			//Loads and set up ship sprite
			//
			m_pShipImage = new sf::Image(resman.GetImage("AllRoundShip"));
			m_pShipSprite = new sf::Sprite();
			m_pShipSprite->SetImage(*m_pShipImage);
			m_pShipSprite->SetCenter(93,55);

			//
			// Loads Ship data from config file
			//
			m_ShipPos = sf::Vector2f(gameConfig.GetConfigValue("R_START_X_POS"), gameConfig.GetConfigValue("R_START_Y_POS"));
			m_ShipVel = sf::Vector2f(gameConfig.GetConfigValue("R_X_VEL"),gameConfig.GetConfigValue("R_Y_VEL"));
			m_BulletLT = gameConfig.GetConfigValue("R_BULLET_LIFE");
			m_FireRate = gameConfig.GetConfigValue("R_FIRE_RATE");
			m_Angle = gameConfig.GetConfigValue("R_ANGLE");
			break;
		}
	case Attack:
		{
			//
			//Loads and set up ship sprite
			//
			m_pShipImage = new sf::Image(resman.GetImage("AttackShip"));
			m_pShipSprite = new sf::Sprite();
			m_pShipSprite->SetImage(*m_pShipImage);
			m_pShipSprite->SetCenter(93,55);

			//
			// Loads Ship data from config file
			//			
			m_ShipPos = sf::Vector2f(gameConfig.GetConfigValue("A_START_X_POS"), gameConfig.GetConfigValue("A_START_Y_POS"));
			m_ShipVel = sf::Vector2f(gameConfig.GetConfigValue("A_X_VEL"),gameConfig.GetConfigValue("A_Y_VEL"));
			m_BulletLT = gameConfig.GetConfigValue("A_BULLET_LIFE");
			m_FireRate = gameConfig.GetConfigValue("A_FIRE_RATE");
			m_Angle = gameConfig.GetConfigValue("A_ANGLE");
			break;
		}
	case Defence:
		{
			//
			//Loads and set up ship sprite
			//
			m_pShipImage = new sf::Image(resman.GetImage("DefenceShip"));
			m_pShipSprite = new sf::Sprite();
			m_pShipSprite->SetImage(*m_pShipImage);
			m_pShipSprite->SetCenter(93,55);

			//
			// Loads Ship data from config file
			//	
			m_ShipPos = sf::Vector2f(gameConfig.GetConfigValue("D_START_X_POS"), gameConfig.GetConfigValue("D_START_Y_POS"));
			m_ShipVel = sf::Vector2f(gameConfig.GetConfigValue("D_X_VEL"),gameConfig.GetConfigValue("D_Y_VEL"));
			m_BulletLT = gameConfig.GetConfigValue("D_BULLET_LIFE");
			m_FireRate = gameConfig.GetConfigValue("D_FIRE_RATE");
			m_Angle = gameConfig.GetConfigValue("D_ANGLE");
			break;
		}
	}


}
