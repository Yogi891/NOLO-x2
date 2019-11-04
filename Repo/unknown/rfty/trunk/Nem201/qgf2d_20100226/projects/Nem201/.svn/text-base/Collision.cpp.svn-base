#include "Collision.h"
#include "Player.h"
#include "BasicBullet.h"
#include "Enemy.h"
#include "BEnemy.h"
#include "Test_Bullet.h"
#include "Circle.h"



//
//Singleton instance pre define
//
Collision* Collision::m_pInstance = NULL;


Collision::Collision()
{
}

Collision::~Collision()
{
}


Collision& Collision::GetInstance()
{
	//
	//creates an instance if one doesnt exist
	//
	if(!m_pInstance)
	{
		m_pInstance = new Collision();
	}

	//
	//returns the singleton instance
	//
	return *m_pInstance;
}

void Collision::Update(Player& a_Player, std::vector<BasicBullet*> a_PlayerBullets,  std::vector<Enemy*> a_Enemies)
{
	//
	//run checks for player v enemy bullets 
	//

	//
	//check each enemy agaist each player bullet
	//
	for(std::vector<BasicBullet*>::iterator iter = a_PlayerBullets.begin(); iter != a_PlayerBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(pBullet->IsALive())
		{
			for(std::vector<Enemy*>::iterator it = a_Enemies.begin(); it != a_Enemies.end(); it++)
			{
				Enemy* pEnemy = * it;

				if(pEnemy->GetAlive())
				{
					//
					//clac mag between the 2
					//
					sf::Vector2f temp (pBullet->GetDrawable().GetPosition() - pEnemy->GetCirc().Center); 
					float dist = sqrt((temp.x *temp.x) + (temp.y *temp.y));

					if(pBullet->GetType() != bomb)
					{
						if(dist < pEnemy->GetCirc().Radius)
						{
							pEnemy->LowerHealth(pBullet->GetDmg());
							pBullet->SetAlive(false);
						}
					}
					else if(pBullet->GetType() == bomb)
					{
						if(dist < pBullet->GetCirc().Radius)
						{
							pEnemy->LowerHealth(pBullet->GetDmg());
							pBullet->SetAlive(false);
						}
					}
				}
			}
		}
	}

	//
	//if enemy died spawn a upgrade in their loc
	//

}

void Collision::Update(Player& a_Player, std::vector<BasicBullet*> a_PlayerBullets, std::vector<BEnemy*> a_BEnemies, std::vector<Test_Bullet*> a_enBul)
{

	for(std::vector<Test_Bullet*>::iterator iter = a_enBul.begin(); iter != a_enBul.end(); iter++)
	{
		Test_Bullet* pTBullet = *iter;
		if(pTBullet->IsAlive())
		{

			sf::Vector2f temp (pTBullet->GetPosition() - a_Player.GetCirc().Center); 
			float dist = sqrt((temp.x *temp.x) + (temp.y *temp.y));
			if(dist < a_Player.GetCirc().Radius)
			{
				std::cout << "DEATH!!!\n";
				//  Player Dies Here
			}
	
		
		}
	}


	for(std::vector<BasicBullet*>::iterator iter = a_PlayerBullets.begin(); iter != a_PlayerBullets.end(); iter++)
	{
		BasicBullet* pBullet = *iter;
		if(pBullet->IsALive())
		{
			for(std::vector<BEnemy*>::iterator it = a_BEnemies.begin(); it != a_BEnemies.end(); it++)
			{
				BEnemy* pEnemy = *it;

				if(pEnemy->IsAlive())
				{
					//
					//clac mag between the 2
					//
					sf::Vector2f temp (pBullet->GetDrawable().GetPosition() - pEnemy->GetCirc().Center); 
					float dist = sqrt((temp.x *temp.x) + (temp.y *temp.y));
					if(pBullet->GetType() != bomb)
					{
						if(dist < pEnemy->GetCirc().Radius)
						{
							pEnemy->LowerHealth(pBullet->GetDmg());
							pBullet->SetAlive(false);
						}
					}
					else if(pBullet->GetType() == bomb)
					{
						if(dist < pBullet->GetCirc().Radius)
						{
							pEnemy->LowerHealth(pBullet->GetDmg());
							pBullet->SetAlive(false);
						}
					}
				}
			}
		}
	}


}