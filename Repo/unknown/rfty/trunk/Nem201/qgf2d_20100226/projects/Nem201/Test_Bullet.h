#ifndef _TEST_BULLET_H_
#define _TEST_BULLET_H_

#include "CBullet.h"
#include "SFML/Graphics.hpp"

class Test_Bullet : public CBullet
{
public:
	//////////////////////////////////////////////////////////////////////////////////
	//C'tor
	//////////////////////////////////////////////////////////////////////////////////
	Test_Bullet();
	Test_Bullet(double a_direction, double a_speed);
	Test_Bullet(sf::Vector2f a_pos);

	//////////////////////////////////////////////////////////////////////////////////
	//D'tor
	//////////////////////////////////////////////////////////////////////////////////
	virtual ~Test_Bullet();

	/////////////////////////////////////////////////////////////////////////////////
	//Main loop for bullets
	/////////////////////////////////////////////////////////////////////////////////
	virtual void Update(float dt);

	//////////////////////////////////////////////////////////////////////////////////
	//Creates the bullet
	//Should be loaded from file
	//////////////////////////////////////////////////////////////////////////////////
	virtual void Init();


	virtual void Move(Timeattack& state, float dt);

	sf::Sprite& GetDrawable(){return *m_pSprite;}

	virtual bool IsAlive() const{return m_IsAlive;}

	virtual void Reset();

	virtual void KillBullet();

	virtual void SetDirection(float a_dir) { m_direction = a_dir; }

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
private:
	double m_direction;
	double m_speed;


	sf::Sprite* m_pSprite;
};

#endif