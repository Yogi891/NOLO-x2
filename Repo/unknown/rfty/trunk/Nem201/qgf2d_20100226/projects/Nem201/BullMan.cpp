#include "BullMan.h"


BullMan::BullMan()
: m_turnCounter(0)
{

}
BullMan::~BullMan()
{

}

BullMan& BullMan::GetInstance()
{
	static BullMan bullman;
	return bullman;
}
