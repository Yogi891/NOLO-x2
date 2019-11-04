#ifndef _BMLSCRIPT_H_
#define _BMLSCRIPT_H_

#include <vector>
#include "CBullet.h"
#include "XMLParser.h"
#include <string>
#include <iostream>
#include "Player.h"
#include <cmath>
#include "Test_Bullet.h"
#include "BEnemy.h"
#include <stack>
#include "Timeattack.h"

class BEnemy;
class BMLScript
{
public:
	BMLScript(std::string a_bMLFile);
	~BMLScript();

	void ShootBullets(Timeattack& state, float dt);
	
	// Will look for the Top Action Tag for the entry point
	// This will be optimized later
	void RunScript(float dt);

	int RunFire(int curNum);

	tagType CheckNextTag(int curNum);

	void FindFire(int curNum);

	void FindBullet(int curNum);

	int RunBullet(int curNum);

	void SearchForRefBullet(std::string a_label);

	int RunAction(int curNum);

	int RunChangeDirection(int curNum);

	int RunChangeSpeed(int curNum);

	float GetContent(int curNum);

	void SetPlayer(Player* a_pPlayer);

	bool RunWait(int curNum);

	int RunRepeat(int curNum);

	bool IsNowPlaying();

	void FireScript(float dt);

	float MakeCalculations(std::string a_content);

	float Operation(char a_oper, float a_lhs, float a_rhs);

	float RandomNumber();

	void SetEnemyStart(float yPos);

	void SetStartTime(float a_startTime);

	// HAXX!
	BEnemy* GetEnemy();

	Test_Bullet* GetBullet(int a_num);

	size_t GetNumbBulletsInm_Bullets()const {return m_bullets.size();}

private:
	std::vector<CBullet*> m_bullets;
	std::vector<CBullet*> m_playingBullets;
	
	CBullet* m_bEnemy;
	CBullet** m_shots;

	float m_scriptLength;

	XMLParser* pXML;
	float m_dt;
	float m_delay;
	Player* m_pPlayer;

	int m_bulletAmount;

	std::vector<Test_Bullet*> m_testB;

	std::stack<std::string> m_tags;	

	bool m_isPlaying;
	bool m_isScriptAlive;

	BulletScript m_currentScript;

	float m_yPos; 
	float m_startTime;
};

#endif