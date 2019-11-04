#ifndef KF_MATRIX3_HEADER
#define KF_MATRIX3_HEADER

#include "kf/kf.h"
#include "kf/kf_vector3.h"

namespace kf
{
   template<typename T>
   class Matrix3T
   {
   public:
      enum {rows = 3,columns = 3};

      T m[rows][columns];

      Matrix3T()
      {
      }

      Matrix3T(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
      {
         m[0][0] = m11;
         m[0][1] = m12;
         m[0][2] = m13;
         m[1][0] = m21;
         m[1][1] = m22;
         m[1][2] = m23;
         m[2][0] = m31;
         m[2][1] = m32;
         m[2][2] = m33;
      }

      Matrix3T operator*(const Matrix3T &mat)
      {
         return Matrix3T(m[0][0]*mat.m[0][0] + m[0][1]*mat.m[1][0] + m[0][2]*mat.m[2][0],
                        m[0][0]*mat.m[0][1] + m[0][1]*mat.m[1][1] + m[0][2]*mat.m[2][1],
                        m[0][0]*mat.m[0][2] + m[0][1]*mat.m[1][2] + m[0][2]*mat.m[2][2],
                        m[1][0]*mat.m[0][0] + m[1][1]*mat.m[1][0] + m[1][2]*mat.m[2][0],
                        m[1][0]*mat.m[0][1] + m[1][1]*mat.m[1][1] + m[1][2]*mat.m[2][1],
                        m[1][0]*mat.m[0][2] + m[1][1]*mat.m[1][2] + m[1][2]*mat.m[2][2],
                        m[2][0]*mat.m[0][0] + m[2][1]*mat.m[1][0] + m[2][2]*mat.m[2][0],
                        m[2][0]*mat.m[0][1] + m[2][1]*mat.m[1][1] + m[2][2]*mat.m[2][1],
                        m[2][0]*mat.m[0][2] + m[2][1]*mat.m[1][2] + m[2][2]*mat.m[2][2]);
      }
      Matrix3T operator+(const Matrix3T &mat) const
      {
         return Matrix3T(m[0][0]+mat.m[0][0], m[0][1]+mat.m[0][1], m[0][2]+mat.m[0][2],
						 m[1][0]+mat.m[1][0], m[1][1]+mat.m[1][1], m[1][2]+mat.m[1][2],
						 m[2][0]+mat.m[2][0], m[2][1]+mat.m[2][1], m[2][2]+mat.m[2][2]);
      }
      Matrix3T operator-(const Matrix3T &mat) const
      {
         return Matrix3T(m[0][0]-mat.m[0][0], m[0][1]-mat.m[0][1], m[0][2]-mat.m[0][2],
						 m[1][0]-mat.m[1][0], m[1][1]-mat.m[1][1], m[1][2]-mat.m[1][2],
						 m[2][0]-mat.m[2][0], m[2][1]-mat.m[2][1], m[2][2]-mat.m[2][2]);
      }
      kf::Vector3T<T> operator * ( const kf::Vector3T<T> &v ) const
        {
            return kf::Vector3T<T>(( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z ), 
                                   ( m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z ), 
                                   ( m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z ));
        }

      Matrix3T transpose()
      {
         return Matrix3T(m[0][0],m[1][0],m[2][0],m[0][1],m[1][1],m[2][1],m[0][2],m[1][2],m[2][2]);
      }
	  kf::Vector3T<T> row(kf::dword i) const
	  {
		  return kf::Vector3T<T>(m[i][0], m[i][1], m[i][2]);
	  }
	  kf::Vector3T<T> column(kf::dword i) const
	  {
		  return kf::Vector3T<T>(m[0][i], m[1][i], m[2][i]);
	  }
	  void row(kf::dword i, kf::Vector3T<T> v)
	  {
		  m[i][0] = v.x;
        m[i][1] = v.y;
        m[i][2] = v.z;
	  }
	  void column(kf::dword i, kf::Vector3T<T> v)
	  {
		  m[0][i] = v.x;
        m[1][i] = v.y;
        m[2][i] = v.z;
	  }
	  T *operator[](kf::dword i)
	  {
		  return m[i];
	  }
	  const T *operator[](kf::dword i) const
	  {
		  return m[i];
	  }
	  T &operator()(kf::dword j,kf::dword i)
	  {
		  return m[j][i];
	  }
	  const T &operator()(kf::dword j,kf::dword i) const
	  {
		  return m[j][i];
	  }
     kf::Vector3 xaxis()
     {
        return kf::Vector3(m[0][0],m[1][0],m[2][0]);
     }
     void xaxis(const kf::Vector3 &v)
     {
        m[0][0] = v.x;
        m[1][0] = v.y;
        m[2][0] = v.z;
     }
     kf::Vector3 yaxis()
     {
        return kf::Vector3(m[0][1],m[1][1],m[2][1]);
     }
     void yaxis(const kf::Vector3 &v)
     {
        m[0][1] = v.x;
        m[1][1] = v.y;
        m[2][1] = v.z;
     }
     kf::Vector3 zaxis()
     {
        return kf::Vector3(m[0][2],m[1][2],m[2][2]);
     }
     void zaxis(const kf::Vector3 &v)
     {
        m[0][2] = v.x;
        m[1][2] = v.y;
        m[2][2] = v.z;
     }

      KF_API static const Matrix3T<T> ZERO;
      KF_API static const Matrix3T<T> IDENTITY;
   };

   typedef Matrix3T<float> Matrix3;
}
#endif
