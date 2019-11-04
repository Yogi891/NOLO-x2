#ifndef KF_EULER_HEADER
#define KF_EULER_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_quaternion.h"
#include <ostream>

namespace kf
{
    float wrapValue(float v, float minValue, float maxValue)
    {
        if(v < minValue)
        {
            return fmod(v, kf::PI*2.0f)+kf::PI*2.0f;
        }
        else if(v > maxValue)
        {
            return fmod(v, kf::PI*2.0f);
        }
        return v;
    }

    class Euler
    {
    public:
        Euler():m_yaw(0),m_pitch(0),m_roll(0),m_changed(false) 
        {
        }

        Euler(float y, float p = float(0.0f), float r = float(0.0f)):m_yaw(y),m_pitch(p),m_roll(r) 
        {
            m_changed = true;
        }

        inline float getYaw() 
        {
            return m_yaw;
        }

        inline float getPitch() 
        {
            return m_pitch;
        }

        inline float getRoll() 
        {
            return m_roll;
        }

        inline Euler &yaw(float y) 
        {
            m_yaw += y; 
            if(m_yaw < 0.0f)
            {
                m_yaw = fmod(m_yaw, kf::PI * 2.0f) + kf::PI * 2.0f;
            }
            else if(m_yaw > kf::PI)
            {
                m_yaw = fmod(m_yaw, kf::PI * 2.0f);
            }
            m_changed = true; 
            return *this;
        }

        inline Euler &pitch(float p) 
        {
            m_pitch += p; 
            m_changed = true; 
            return *this;
        }

        inline Euler &roll(float r) 
        {
            m_roll += r; 
            m_changed = true; 
            return *this;
        }

        inline Euler &setYaw(float y) 
        {
            m_yaw = y; 
            m_changed = true; 
            return *this;
        }

        inline Euler &setPitch(float p) 
        {
            m_pitch = p; 
            m_changed = true; 
            return *this;
        }

        inline Euler &setRoll(float r) 
        {
            m_roll = r; 
            m_changed = true; 
            return *this;
        }

        inline kf::Vector3 getForward() 
        {
            return toQuaternion() * kf::Vector3::NEGATIVE_UNIT_Z;
        }

        inline kf::Vector3 getRight() 
        {
            return toQuaternion() * kf::Vector3::UNIT_X;
        }

        inline kf::Vector3 getUp() 
        {
            return toQuaternion() * kf::Vector3::UNIT_Y;
        }

        inline kf::Quaternion toQuaternion() 
        {
            if(m_changed) 
            {
                m_cachedQuaternion = kf::Quaternion(m_yaw, kf::Vector3::NEGATIVE_UNIT_Y) * kf::Quaternion(m_pitch, kf::Vector3::UNIT_X) * kf::Quaternion(m_roll, kf::Vector3::UNIT_Z); 
                m_changed = false;
            }
            return m_cachedQuaternion;
        }

        inline operator kf::Quaternion() 
        {
            return toQuaternion();
        }

        Euler &setDirection(const kf::Vector3 &v)
        {
            kf::Vector3 d(v.normalise());
            m_pitch = float(asin(d.dot(kf::Vector3::UNIT_Y)));
            m_yaw = float(atan2(d.z, d.x)+kf::PI/2.0);
            m_changed = true;
            
            return *this;
        }

        inline float yawToDirection(const float &a)
        {
            float angle = a - m_yaw;
            if(angle>kf::PI)
                angle = -kf::PI*2.0f + angle;
            else if(angle<-kf::PI)
                angle = kf::PI*2.0f + angle;
            return angle;
        }

        inline float yawToDirection(const kf::Vector3 &v)
        {
            return yawToDirection(atan2(v.z, v.x) + kf::PI/2.0f);
        }

        inline float yawToDirection(const Euler &e)
        {
            return yawToDirection(e.m_yaw);
        }

        inline friend std::ostream &operator<<(std::ostream &o, const Euler &e)
        {
            o << "<Y:" << e.m_yaw << ", P:" << e.m_pitch << ", R:" << e.m_roll << ">";
            return o;
        }


        KF_API static const Euler NORTH;
        KF_API static const Euler SOUTH;
        KF_API static const Euler WEST;
        KF_API static const Euler EAST;
        KF_API static const Euler NORTH_WEST;
        KF_API static const Euler NORTH_EAST;
        KF_API static const Euler SOUTH_WEST;
        KF_API static const Euler SOUTH_EAST;

    protected:
        float m_yaw;
        float m_pitch;
        float m_roll;
        kf::Quaternion m_cachedQuaternion;
        bool m_changed;
    };
}

#endif
