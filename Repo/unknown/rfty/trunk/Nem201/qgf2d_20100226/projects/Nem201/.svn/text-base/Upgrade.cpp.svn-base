#include "Upgrade.h"
#include "CircleCol.h"
#include "Resman.h"
#include "GameConfig.h"

Upgrade::Upgrade()
{
	m_pSprite = new sf::Sprite(Resman::GetInstance().GetImage("Upgrade"));
	m_Vel.x = GameConfig::GetInstance().GetConfigValue("UPGRADE_X_VEL");
	m_Vel.y = GameConfig::GetInstance().GetConfigValue("UPGRADE_Y_VEL");
	m_IsAlive = false;

}

Upgrade::~Upgrade()
{
	delete m_pSprite;
}


void Upgrade::Run(float dt)
{
	m_pSprite->Move(m_Vel * dt);
}

void Upgrade::Init(sf::Vector2f pos)
{
	m_pSprite->SetPosition(pos);
	m_IsAlive = true;
}