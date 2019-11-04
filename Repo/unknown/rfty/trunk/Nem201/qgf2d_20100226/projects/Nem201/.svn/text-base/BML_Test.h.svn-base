#ifndef _BML_TEST_H_
#define _BML_TEST_H_


#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlrunner.h"

<<<<<<< .mine
class BullMan;
=======
class BullMan;
class ProtoBullet;
>>>>>>> .r42

class BML_Test : public BulletMLRunner
{
public:

	BML_Test(BulletMLParser* a_bp, BullMan* a_bullman); //: BulletMLRunner(a_bp), m_bullet(a_b)
//	{
//	}
	



	BML_Test(BulletMLState* a_state, BullMan* a_bullman); //: BulletMLRunner(a_state), m_bullet(a_b)
//	{
//	}

	DECLSPEC virtual double getBulletDirection();

	DECLSPEC virtual double getAimDirection();

	DECLSPEC virtual double getBulletSpeed();

	DECLSPEC virtual double getDefaultSpeed();

	DECLSPEC virtual double getRank();

	DECLSPEC virtual void createSimpleBullet(double direction, double speed);

	DECLSPEC virtual void createBullet(BulletMLState* state, double direction, double speed);

	DECLSPEC virtual int getTurn();

	DECLSPEC virtual void doVanish();


private:
<<<<<<< .mine
	double m_posX;
	double m_posY;
	double m_speed;
	double m_direction;
	bool m_vanish;

	bool m_isPaused;
=======
	double m_posX;
	double m_posY;
	double m_speed;
	double m_direction;
	bool m_vanish;
	ProtoBullet* m_bullet;
>>>>>>> .r42
	bool m_isPaused;

};

#endif