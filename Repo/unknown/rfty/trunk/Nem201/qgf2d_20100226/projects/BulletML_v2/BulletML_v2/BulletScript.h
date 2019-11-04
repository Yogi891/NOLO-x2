#ifndef _BULLETSCRIPT_H_
#define _BULLETSCRIPT_H_

class BulletScript
{
public:
	BulletScript();
	~BulletScript();

	float m_delay;
	float m_dir;
	float m_dirTime;
	float m_targetDir;
	float m_speed;
	float m_speedTime;
	float m_targetSpeed;
	bool m_isAimed;
	bool m_isSequence;
	bool m_isRelative;
	bool m_isSpeedRelative;
	bool m_isSpeedSequence;

};

#endif