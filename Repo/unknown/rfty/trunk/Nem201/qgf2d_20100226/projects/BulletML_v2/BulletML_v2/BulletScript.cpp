#include "BulletScript.h"

BulletScript::BulletScript()
: m_delay(0)
, m_dir(3.1415)
, m_dirTime(0)
, m_speed(1)
, m_speedTime(0)
, m_isAimed(true)
, m_isSequence(false)
, m_isRelative(false)
, m_isSpeedRelative(false)
, m_isSpeedSequence(false)
{
}

BulletScript::~BulletScript()
{
}
