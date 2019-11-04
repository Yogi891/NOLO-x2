#ifndef _PROTOBULLET_H_
#define _PROTOBULLET_H_

#include "BML_Test.h"
#include "SFML/Graphics.hpp"

class ProtoBullet
{
public:
	ProtoBullet(BulletMLState* a_state, double a_xPos, double a_yPos, double a_dir, double a_speed);
	ProtoBullet(BulletMLParser* a_parser, double a_xPos, double a_yPos, double a_dir, double a_speed);
	~ProtoBullet();

	void move();
	void draw();
	void die();

	double GetDir() const;
	double GetXPos() const;
	double GetYPos() const;
	double GetSpeed() const;
	bool IsAlive() const;
<<<<<<< .mine

	void SetSpeed(double a_speed) { m_speed = a_speed; }
	void SetDirection(double a_dir) { m_dir = a_dir; }
	void SetCommand(BML_Test* a_BML) { m_bml = a_BML; }

	sf::Sprite& GetDrawable(){return *m_pSprite;};
=======

	void SetSpeed(double a_speed) { m_speed = a_speed; }
	void SetDirection(double a_dir) { m_dir = a_dir; }
	void SetCommand(BML_Test* a_BML) { m_bml = a_BML; }
	int GetTurn() {return m_turn;}
	void SetTurn(int a_turn) {m_turn = a_turn;}

	sf::Sprite& GetDrawable(){return *m_pSprite;};
>>>>>>> .r42
private:
    BML_Test* m_bml;
    bool m_isAlive;
	double m_xPos;
	double m_yPos;
	double m_dir;
	double m_speed;
<<<<<<< .mine

	sf::Sprite* m_pSprite;
=======
	int m_turn;
	sf::Sprite* m_pSprite;
>>>>>>> .r42
};

#endif