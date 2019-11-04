#ifndef _BENEMY_H_
#define _BENEMY_H_

#include "CBullet.h"
#include "Timeattack.h"

struct CollPlayer
{
	sf::Vector2f Center;
	float Radius;	
};

class BEnemy : public CBullet
{
public:
	BEnemy(double a_direction, double a_speed);
	~BEnemy();



	virtual void Move(Timeattack& state, float dt);

	virtual sf::Sprite& GetDrawable();

	virtual bool IsAlive() const;

	virtual void Reset();

	virtual void KillBullet();

	virtual void SetDirection(float a_dir);

	virtual float GetDirection();
	
	virtual sf::Vector2f& GetPosition();

	virtual void SetPosition(sf::Vector2f& a_pos);

	virtual void SetAimed(bool a_aimed);

	virtual bool GetAimed();

	virtual void SetDelay(float a_delay);

	virtual float GetDelay();

	virtual bool GetIsShot();

	virtual void SetIsShot(bool a_isShot);

	virtual int GetBulletOrder();

	virtual void SetBulletOrder(bool a_bulletOrder);

	virtual float GetSpeed();

	virtual void SetSpeed(float a_speed);

	virtual float GetDirChange();

	virtual void SetDirChange(float a_dirChange);

	virtual int GetDirChangeTime();

	virtual void SetDirChangeTime(float a_dirChangeTime);

	CollPlayer& GetCirc(){return m_Circ;}

	void LowerHealth(float a_lowerBy){ m_Health -= a_lowerBy;}
private:
	double m_direction;
	double m_speed;

	CollPlayer m_Circ;

	float m_Health;

	sf::Sprite* m_pSprite;

};

#endif