#ifndef _CBULLET_H_
#define _CBULLET_H_

#include "SFML/Graphics.hpp"
#include "BulletScript.h"
#include <queue>

class Timeattack;

class CBullet
{
public:
	CBullet(){}
	virtual ~CBullet(){}



	virtual void Move(Timeattack& state, float dt) = 0;

	virtual sf::Sprite& GetDrawable() = 0;

	virtual bool IsAlive() const = 0;

	virtual void Reset() = 0;

	virtual void KillBullet() = 0;

	virtual void SetDirection(float a_dir) = 0;

	virtual float GetDirection() = 0;

	virtual void SetPosition(sf::Vector2f& a_pos) = 0;

	virtual sf::Vector2f& GetPosition() = 0;

	virtual void SetAimed(bool a_aimed) = 0;

	virtual bool GetAimed() = 0;

	virtual void SetDelay(float a_delay) = 0;

	virtual float GetDelay() = 0;

	virtual bool GetIsShot() = 0;

	virtual void SetIsShot(bool a_isShot) = 0;

	virtual int GetBulletOrder() = 0;

	virtual void SetBulletOrder(bool a_bulletOrder) = 0;

	virtual float GetSpeed() = 0;

	virtual void SetSpeed(float a_speed) = 0;

	virtual float GetDirChange() = 0;

	virtual void SetDirChange(float a_dirChange) = 0;

	virtual int GetDirChangeTime() = 0;

	virtual void SetDirChangeTime(float a_dirChangeTime) = 0;

	std::queue<BulletScript> m_scripts;

protected:
	bool m_IsAlive;
	bool m_aimed;
	float m_delay;
	bool m_isShot;
	int m_bulletOrder;
	sf::Vector2f m_pos;
	float m_speed;
	float m_dirChange;
	int m_dirChangeTime;
	float m_prevSpeed;
	float m_prevDir;

	int m_Score;



};

#endif