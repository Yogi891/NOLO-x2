#ifndef KF_RAY_HEADER
#define KF_RAY_HEADER

#include "kf/kf_vector3.h"
#include <ostream>

namespace kf
{
   template<typename VT>
   class RayT
   {
   public:
      typedef VT type;

      inline RayT()
      {
         m_length = 0;
      }
      inline RayT(const VT &start): m_start(start)
      {
         m_length = 0;
      }
      inline RayT(const VT &start, const VT &delta): m_start(start), m_delta(delta)
      {
         m_length = delta.length();
      }

      inline friend std::ostream &operator<<(std::ostream &o, const RayT &r)
      {
         o << "[" << r.m_start << ":" << r.m_delta + r.m_start << "]";
         return o;
      }

      inline typename VT::type length()
      {
         return m_length;
      }

      inline void length(typename VT::type value)
      {
         if(m_length!=0)
         {
            m_delta *= value / m_length;
            m_length = m_delta.length();
         }
      }

      inline VT start()
      {
         return m_start;
      }
      inline void start(const VT &v)
      {
         m_start = v;
      }
      inline VT end()
      {
         return m_start+m_delta;
      }
      inline void end(const VT &v)
      {
         m_delta = v-m_start;
         m_length = m_delta.length();
      }
      inline VT delta()
      {
         return m_delta;
      }
      inline void delta(const VT &v)
      {
         m_delta = v;
         m_length = m_delta.length();
      }
      inline VT interpolate(const typename VT::type &value)
      {
         return m_start + m_delta * value;
      }


protected:
      VT m_start;
      VT m_delta;
      typename VT::type m_length;
   };

   typedef RayT<Vector3>  Ray;
}

#endif

