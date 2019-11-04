#ifndef _BULLMAN_H_
#define _BULLMAN_H_

#include <vector>



class BullMan
{
public:

	~BullMan();

	static BullMan& GetInstance();

private:
	BullMan();

	int m_turnCounter;

};

#endif