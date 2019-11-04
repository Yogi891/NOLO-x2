#include "BML_Test.h"
#include "Protobullet.h"
#include "BullMan.h"


// Radian Helper functions

double DegreesToRadians(double angle)
{
	return angle * 3.14/180;
}
double RadiansToDegrees(double angle)
{
	return angle * 180/3.14;
}

BML_Test::BML_Test(BulletMLParser* a_bp, BullMan* a_bullman)
: BulletMLRunner(a_bp)
<<<<<<< .mine

=======
, m_bullet(NULL)


>>>>>>> .r42
{
}

BML_Test::BML_Test(BulletMLState* a_state, BullMan* a_bullman)
: BulletMLRunner(a_state)
<<<<<<< .mine

=======
, m_bullet(NULL)

>>>>>>> .r42
{
}

DECLSPEC double BML_Test::getBulletDirection()
{
	return m_direction;
}


DECLSPEC double BML_Test::getAimDirection()
{
	return 0.5;
}


DECLSPEC double BML_Test::getBulletSpeed()
{
	return m_speed*1000;
}


DECLSPEC double BML_Test::getDefaultSpeed()
{
	return 1.0;
}


DECLSPEC double BML_Test::getRank()
{
	return 0.5;
}


DECLSPEC void BML_Test::createSimpleBullet(double direction, double speed)
{
	BullMan& bullman = BullMan::GetInstance();
	//add normal bullet
//	ProtoBullet* p_PB = new ProtoBullet(state, 20, 20, direction, speed);
//	if(p_PB && !m_isPaused)
//	{
//		p_PB->SetSpeed(speed*1000);
//		p_PB->SetDirection(direction);
//	}
//	bullman.GetBullets().push_back(p_PB);
}


DECLSPEC void BML_Test::createBullet(BulletMLState* state, double direction, double speed)
{
<<<<<<< .mine
	//add active bullet
	BullMan& bullman = BullMan::GetInstance();

	ProtoBullet* p_PB = new ProtoBullet(state, 20, 20, direction, speed);
//	if(p_PB)
//	{
//		p_PB->SetCommand(new BML_Test(state, m_bullman));
//		p_PB->SetSpeed(speed*1000);
//		p_PB->SetDirection(direction);
//	}
	bullman.GetBullets().push_back(p_PB);
=======
	//add active bullet
	BullMan& bullman = BullMan::GetInstance();

	ProtoBullet* p_PB = new ProtoBullet(state, 20, 20, direction, speed);
	bullman.GetBullets().push_back(p_PB);
	p_PB->SetTurn(bullman.NewTurn());
	p_PB->SetCommand(new BML_Test(state));
//	if(p_PB)
//	{
//		p_PB->SetCommand(new BML_Test(state, m_bullman));
//		p_PB->SetSpeed(speed*1000);
//		p_PB->SetDirection(direction);
//	}

>>>>>>> .r42
}


DECLSPEC int BML_Test::getTurn()
{
	if(!m_bullet) return 0;
	else return m_bullet->GetTurn();
}


DECLSPEC void BML_Test::doVanish()
{

}
